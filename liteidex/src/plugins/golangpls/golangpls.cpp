#include "GolangPls.h"
#include "qjson/include/QJson/Parser"
#include "qjson/include/QJson/Serializer"
#include <QEventLoop>
#include <QThread>
#include "golangastapi/golangastapi.h"

GolangPls::GolangPls(LiteApi::IApplication* app, QObject* parent)
	: QObject(parent)
{
	m_liteApp = app;
	m_nRequestId = 0;
	m_nVersion = 0;
	m_completer = nullptr;
	m_plsDir = "";
	m_bInited = false;
	__init();
}

GolangPls::~GolangPls()
{
}

void GolangPls::__init()
{
	m_process = new Process(this);
	m_goplsPath = LiteApi::getGoPls(m_liteApp);
	m_golangAst = LiteApi::findExtensionObject<LiteApi::IGolangAst*>(m_liteApp, "LiteApi.IGolangAst");

	__loadPkgList();

	__regCall(LSPMethod::WindowShowMessage, std::bind(&GolangPls::__onWindowShowMessage, this, std::placeholders::_1, std::placeholders::_2 ));
    __regCall(LSPMethod::WindowLogMessage, std::bind(&GolangPls::__onWindowLogMessage, this, std::placeholders::_1, std::placeholders::_2 ));
	__regCall(LSPMethod::TextDocumentPublishDiagnostics, std::bind(&GolangPls::__onTextDocumentPublishDiagnostics, this, std::placeholders::_1, std::placeholders::_2));


	connect(m_process, &Process::started, this, &GolangPls::__onStarted);
	connect(m_process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(__onFinished(int, QProcess::ExitStatus)));
	connect(m_process, &Process::readyReadStandardOutput, this, &GolangPls::__onReadyReadStandardOutput);
	connect(m_process, &Process::readyReadStandardError, this, &GolangPls::__onReadyReadStandardError);

	connect(m_liteApp->editorManager(), &LiteApi::IEditorManager::currentEditorChanged, this, &GolangPls::__onCurrentEditorChanged);
	connect(m_liteApp->editorManager(), &LiteApi::IEditorManager::editorCreated, this, &GolangPls::__onEditorCreated);
	connect(m_liteApp->editorManager(), &LiteApi::IEditorManager::editorAboutToClose, this, &GolangPls::__onEditorAboutToClose);
	connect(m_liteApp->fileManager(), &LiteApi::IFileManager::folderOpened, this, &GolangPls::__onFolderOpened);
	connect(m_liteApp->fileManager(), &LiteApi::IFileManager::folderClosed, this, &GolangPls::__onFolderClosed);
}

void GolangPls::__loadPkgList()
{
	QString path = m_liteApp->resourcePath() + ("/packages/go/pkglist");
	QFile file(path);
	if (file.open(QFile::ReadOnly)) {
		QByteArray data = file.readAll();
		QString ar = QString::fromUtf8(data);
		ar.replace("\r\n", "\n");
		foreach(QString line, ar.split("\n")) {
			line = line.trimmed();
			if (line.isEmpty()) {
				continue;
			}
			QStringList pathList = line.split("/");
			m_pkgListMap.insert(pathList.last(), line);
			m_importList.append(line);
		}
	}
	m_importList.removeDuplicates();
	m_importList << "github.com/"
		<< "golang.org/x/";
	m_allImportList = m_importList;
}

void GolangPls::__start(const QString& folder)
{
	if (!m_plsDir.isEmpty())
		__stop(m_plsDir);

	//QThread::msleep(1000);

	m_plsDir = folder;

	QStringList args;
	args << "-rpc.trace";
	m_process->startEx(m_goplsPath, args);
	__initLSP(folder);
}

void GolangPls::__stop(const QString& folder)
{
	if (m_plsDir != folder)
		return;

	m_bInited = false;
	m_waitOpenEdits.clear();
	qDebug() << "stop pls ---- 1";
	m_process->stopAndWait(100, 2000);
	qDebug() << "stop pls ---- 2";
	qDebug() << "stop pls ---- 3" << m_process->isRunning();

	//disconnect(m_process, nullptr, this, nullptr);
}

int GolangPls::__nextId()
{
	m_nRequestId++;
	return m_nRequestId;
}

int GolangPls::__nextVersion()
{
	m_nVersion++;
    return m_nVersion;
}

void GolangPls::__regCall(QString method, LspCall lspCall)
{
	m_methodCallMap[method] = lspCall;
}

void GolangPls::__request(QVariantMap msg)
{
	QJson::Serializer s;
	QByteArray body = s.serialize(msg);
	QByteArray header = QString::asprintf("Content-Length: %d\r\n\r\n", QString(body).length()).toUtf8();
	QByteArray data = header + body;

	qDebug() << "request:" << data;
	m_process->write(data);
}

void GolangPls::__requestLSP(QString method, QVariantMap params, int id)
{
	QVariantMap msg;
	msg["jsonrpc"] = "2.0";
	msg["id"] = id;
	msg["method"] = method;
	msg["params"] = params;
	__request(msg);
}

void GolangPls::__requestLSP(QString method, QVariantMap params, LspCall lspCall)
{
	int id = __nextId();
	__requestLSP(method, params, id);
	if (lspCall != nullptr)
	{
		LspCallData call;
		call._dt = QDateTime::currentMSecsSinceEpoch();
		call._lspCall = lspCall;
		m_requestCallMap[id] = call;
	}
}

void GolangPls::_notify(QString method, QVariantMap params)
{
	QVariantMap msg;
	msg["jsonrpc"] = "2.0";
	msg["method"] = method;
	if (!params.isEmpty())
	{
		msg["params"] = params;
	}
	__request(msg);
}

void GolangPls::__onMsg(QString method, QVariantMap msg)
{
	auto itr = m_methodCallMap.find(method);
	if (itr != m_methodCallMap.end())
	{
		auto call = (*itr);
		call(this, msg);
	}
}

void GolangPls::__onMsg(int msgId, QVariantMap msg)
{
	auto itr = m_requestCallMap.find(msgId);
	if (itr != m_requestCallMap.end())
	{
		(*itr)._lspCall(this, msg);
		m_requestCallMap.erase(itr);
	}
}

void GolangPls::__onWindowShowMessage(GolangPls* pls, QVariantMap msg)
{
	//QString log = QString::asprintf("window/showMessage: %s", msg["params"].toMap()["message"].toString().toUtf8().data());
	//m_liteApp->appendLog("GolangPls", log);
	QString message = msg["params"].toMap()["message"].toString();
	// remove the last \n
    //message = message.trimmed();
	// remove 2026/05/23 13:10:52 background imports cache refresh starting
	// remove timestamp
    message = message.remove(QRegExp("^\\d{4}/\\d{2}/\\d{2} \\d{2}:\\d{2}:\\d{2} "));
	message = message.trimmed();
    m_liteApp->appendLog("GolangPls.WindowShowMessage", message);
}

void GolangPls::__onWindowLogMessage(GolangPls* pls, QVariantMap msg)
{
	//QString log = QString::asprintf("window/logMessage: %s", msg["params"].toMap()["message"].toString().toUtf8().data());
//m_liteApp->appendLog("GolangPls", log);
	QString message = msg["params"].toMap()["message"].toString();
	// remove the last \n
	//message = message.trimmed();
	// remove 2026/05/23 13:10:52 background imports cache refresh starting
	// remove timestamp
	message = message.remove(QRegExp("^\\d{4}/\\d{2}/\\d{2} \\d{2}:\\d{2}:\\d{2} "));
	message = message.trimmed();
	m_liteApp->appendLog("GolangPls.WindowLogMessage", message);
}

void GolangPls::__onTextDocumentPublishDiagnostics(GolangPls* pls, QVariantMap msg)
{	
	//QJson::Serializer s;
	//QVariantList diagnostics = msg["params"].toMap()["diagnostics"].toList();
	//QString message = s.serialize(diagnostics);
    //m_liteApp->appendLog("GolangPls", message);

}

void GolangPls::__initLSP(const QString& workFolder)
{
	QVariantMap _map;
	_map["processId"] = m_process->processId();
	
	QVariantMap clientInfo;
	clientInfo["name"] = "gopls-plugin";
	clientInfo["version"] = "1.0.0";
	_map["clientInfo"] = clientInfo;
	_map["rootUri"] = "file:///" + workFolder;
	__requestLSP(LSPMethod::Initialize, _map, [=](GolangPls* pls, QVariantMap __map) {
		m_bInited  = true;
		pls->_notify(LSPMethod::Initialized, QVariantMap());
		m_liteApp->appendLog("GolangPls", "init lsp ok");
		for (int i = 0; i < m_waitOpenEdits.size(); i++)
		{
			__onEditorCreated(m_waitOpenEdits[i]);
		}
		m_waitOpenEdits.clear();
		});
}

void GolangPls::__setCompleter(LiteApi::ICompleter* completer)
{
    m_completer = completer;
	if (m_completer != nullptr)
	{
		m_completer->setSearchSeparator(false);
		m_completer->setExternalMode(true);
		connect(m_completer, SIGNAL(prefixChanged(QTextCursor, QString, bool)), this, SLOT(__onPrefixChanged(QTextCursor, QString, bool)));
		connect(m_completer, SIGNAL(wordCompleted(QString, QString, QString)), this, SLOT(__onWordCompleted(QString, QString, QString)));
	}
}

void GolangPls::__completion(QString filePath, int line, int column)
{
	QVariantMap params;
	QVariantMap textDocument;
	textDocument["uri"] = "file://" + filePath;
	params["textDocument"] = textDocument;

	QVariantMap position;
    position["line"] = line;
    position["character"] = column;
	params["position"] = position;
	__requestLSP("textDocument/completion", params, [=](GolangPls* pls, QVariantMap __map) {

			if (!__map.contains("result"))
			{
				return;
			}

			QVariantMap __result = __map["result"].toMap();
			if (!__result.contains("items"))
			{
				qDebug() << "can't find items";
				return;
			}

			QVariantList __items = __result["items"].toList();
			int n = 0;

			QStandardItem* root = m_completer->findRoot(m_preWord);
			for (int i = 0; i < __items.size(); i++)
			{
				QVariantMap __item = __items[i].toMap();
				//xItem["label"].toString();
				qDebug() << "label:" << __item["label"].toString() << "kind:" << __item["kind"].toString() << "detail:" << __item["detail"].toString();

				LiteApi::ASTTAG_ENUM tag = LiteApi::TagNone;
				int kind = __item["kind"].toString().toInt();
				QString sKind = "";

				QString word = __item["label"].toString();
				QString info = __item["detail"].toString();
				//	1 = Text
				//	2 = Method
				//	3 = Function      
				//	4 = Constructor
				//	5 = Field
				//	6 = Variable
				//	7 = Class
				//	8 = Interface
				//	9 = Module
				//	10 = Property
				//	11 = Unit
				//	12 = Value
				//	13 = Enum
				//	14 = Keyword
				//	15 = Snippet
				//	16 = Color
				//	17 = File
				//	18 = Reference
				//	19 = Folder
				//	20 = EnumMember
				//	21 = Constant
				//	22 = Struct
				//	23 = Event
				//	24 = Operator
				//	25 = TypeParameter
				switch (kind)
				{
				//case 1:
					//break;
				case 2:
					tag = LiteApi::TagFunc;
					sKind = "Method";
					break;
				case 3:
					tag = LiteApi::TagFunc;
					sKind = "Function";
					break;
				case 6:
					tag = LiteApi::TagValue;
					sKind = "Variable";
					break;
				case 8:
					tag = LiteApi::TagInterface;
					sKind = "Interface";
					break;
				case 21:
					tag = LiteApi::TagConst;
					sKind = "Constant";
					break;
				case 22:
					tag = LiteApi::TagStruct;
                    sKind = "Struct";
					break;
				default:
					tag = LiteApi::TagType;
					break;
				}
				
				QIcon icon = m_golangAst->iconFromTagEnum(tag, true);
				m_completer->appendChildItem(root, word, sKind, info, icon, true);
				n++;
			}

			if (n >= 1) {
				m_completer->updateCompleterModel();
				m_completer->showPopup();
			}

	});
}

QVector<QByteArray> GolangPls::parseLspData(QByteArray& rawData)
{
	QVector<QByteArray> _bytes;

	while (!rawData.isEmpty()) {
		int headerEnd = rawData.indexOf("\r\n\r\n");
		if (headerEnd == -1) {
			break;
		}

		QByteArray header = rawData.left(headerEnd);
		if (!header.startsWith("Content-Length:")) {
			rawData.clear();
			break;
		}

		int contentLength = -1;
		for (const QByteArray& line : header.split('\n')) {
			if (line.startsWith("Content-Length:")) {
				contentLength = line.mid(16).trimmed().toInt();
				break;
			}
		}

		if (contentLength == -1) {
			rawData.clear();
			break;
		}

		int totalLength = headerEnd + 4 + contentLength;
		if (rawData.size() < totalLength) {
			break;
		}

		QByteArray jsonBody = rawData.mid(headerEnd + 4, contentLength);
		_bytes.push_back(jsonBody);
		rawData.remove(0, totalLength);
	}

	return _bytes;
}

void GolangPls::__didOpen(QString filepath, QString content, int version)
{
	/// chieck filepath is in m_plsDir
    if (!filepath.startsWith(m_plsDir))
	{
		QString message = filepath + "is not in " + m_plsDir;
		m_liteApp->appendLog("GolangPls", message, true);
		return;
	}

	QVariantMap params;
	QVariantMap textDocument;
	textDocument["uri"] = "file:///" + filepath;
	textDocument["languageId"] = "go";
	textDocument["version"] = version;
	textDocument["text"] = content;
	params["textDocument"] = textDocument;
	_notify(LSPMethod::TextDocumentDidOpen, params);
}

void GolangPls::__didClose(QString filepath)
{
	QVariantMap params;
	QVariantMap textDocument;
	textDocument["uri"] = "file:///" + filepath;
	params["textDocument"] = textDocument;
    _notify(LSPMethod::TextDocumentDidClose, params);
}

void GolangPls::__didChange(QString filepath, QString content, int version)
{
	QVariantMap params;
	QVariantMap textDocument;
	textDocument["uri"] = "file:///" + filepath;
	textDocument["version"] = version;
	params["textDocument"] = textDocument;

	QVariantList contentChanges;
	QVariantMap text;
	text["text"] = content;
	contentChanges.append(text);
	params["contentChanges"] = contentChanges;
	_notify(LSPMethod::TextDocumentDidChange, params);
}


//public slots:
void GolangPls::__onStarted()
{
	qDebug() << __FUNCTION__;
}

void GolangPls::__onFinished(int code, QProcess::ExitStatus status)
{
	qDebug() << __FUNCTION__;
}

void GolangPls::__onCurrentEditorChanged(LiteApi::IEditor* editor)
{
	m_editor= LiteApi::getTextEditor(editor);
	if (m_editor == nullptr)
		return;

	if (editor->mimeType() == "text/x-gosrc") {
		LiteApi::ICompleter* completer = LiteApi::findExtensionObject<LiteApi::ICompleter*>(editor, "LiteApi.ICompleter");
		completer->setImportList(m_importList);
		__setCompleter(completer);
	}
	else if (editor->mimeType() == "browser/goplay") {
		LiteApi::IEditor* pedit = LiteApi::findExtensionObject<LiteApi::IEditor*>(m_liteApp->extension(), "LiteApi.Goplay.IEditor");
		if (pedit && pedit->mimeType() == "text/x-gosrc") {
			editor = pedit;
			LiteApi::ICompleter* completer = LiteApi::findExtensionObject<LiteApi::ICompleter*>(editor, "LiteApi.ICompleter");
			completer->setImportList(m_importList);
			__setCompleter(completer);
		}
	}
	else {
		__setCompleter(nullptr);
		return;
	}

	QString filePath = editor->filePath();
	if (filePath.isEmpty())
		return;

	m_fileInfo.setFile(filePath);
}

void GolangPls::__onEditorCreated(LiteApi::IEditor* editor)
{
	m_editor = LiteApi::getTextEditor(editor);
	if (m_editor == nullptr)
		return;

	if (editor->mimeType() != "text/x-gosrc")
	{
		return;
	}

	if (!m_bInited && !m_waitOpenEdits.contains(editor))
	{
		m_waitOpenEdits.append(editor);
		return;
	}

	QString filePath = editor->filePath();
	__didOpen(filePath, LiteApi::getLiteEditor(editor)->document()->toPlainText(), __nextVersion());
}

void GolangPls::__onEditorAboutToClose(LiteApi::IEditor* editor)
{
	QString filePath = editor->filePath();
    __didClose(filePath);
}

void GolangPls::__onFolderOpened(const QString& folder)
{
	__start(folder);
}

void GolangPls::__onFolderClosed(const QString& folder)
{
	__stop(folder);
}

void GolangPls::__onPrefixChanged(QTextCursor cur, QString pre, bool force)
{
	int offset = -1;
	if (pre.endsWith('.')) {
		m_preWord = pre;
		offset = 0;
	}
	else if (pre.length() == m_completer->prefixMin()) {
		m_preWord.clear();
	}
	else {
		if (!force) {
			return;
		}
		m_preWord.clear();
		int index = pre.lastIndexOf(".");
		if (index != -1) {
			m_preWord = pre.left(index);
		}
	}

	if (!m_preWord.isEmpty()) {
		m_completer->clearItemChilds(m_preWord);
	}

	QString txt = m_editor->document()->toPlainText();
	__didChange(m_fileInfo.filePath(), txt, __nextVersion());
	
	int row = cur.blockNumber();      
	int col = cur.columnNumber();        
	__completion(m_fileInfo.filePath(), row, col);
}

void GolangPls::__onWordCompleted(QString, QString, QString)
{

}

void GolangPls::__onReadyReadStandardOutput()
{
	QByteArray output = m_process->readAllStandardOutput();
	if (output.isEmpty())
	{
		return;
	}

    qDebug() << "-----%%%%% &&&&& %%%%%-----\n" << QString::fromUtf8(output);

	___lspBuffer.append(output);
	QVector<QByteArray> bytes =  parseLspData(___lspBuffer);
	for (int i = 0; i < bytes.size(); i++)
	{
		QJson::Parser __p;
		QVariantMap __map = __p.parse(bytes[i]).toMap();
		if (__map.isEmpty())
		{
			continue;
		}

		if (__map.contains("id"))
		{
			int id = __map["id"].toInt();
			__onMsg(id, __map);
			continue;
		}

		if (__map.contains("method"))
		{
			QString __method = __map["method"].toString();
			__onMsg(__method, __map);
			continue;
		}
	}
}

void GolangPls::__onReadyReadStandardError()
{
	
}

