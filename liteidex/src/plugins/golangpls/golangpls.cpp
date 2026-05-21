#include "GolangPls.h"
#include "qjson/include/QJson/Parser"
#include "qjson/include/QJson/Serializer"
#include <QEventLoop>
#include <QThread>

GolangPls::GolangPls(LiteApi::IApplication* app, QObject* parent)
	: QObject(parent)
{
	m_liteApp = app;
	m_nRequestId = 0;
	m_completer = nullptr;
	__init();
}

GolangPls::~GolangPls()
{
}

void GolangPls::__init()
{
	m_process = new Process(this);
	m_goplsPath = LiteApi::getGoPls(m_liteApp);
	connect(m_process, &Process::started, this, &GolangPls::__onStarted);
	connect(m_process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(__onFinished(int, QProcess::ExitStatus)));
	connect(m_process, &Process::readyReadStandardOutput, this, &GolangPls::__onReadyReadStandardOutput);
	connect(m_process, &Process::readyReadStandardError, this, &GolangPls::__onReadyReadStandardError);

	connect(m_liteApp->editorManager(), &LiteApi::IEditorManager::currentEditorChanged, this, &GolangPls::__onCurrentEditorChanged);
	connect(m_liteApp->editorManager(), &LiteApi::IEditorManager::editorCreated, this, &GolangPls::__onEditorCreated);
}

void GolangPls::__start()
{
	QStringList args;
	m_process->startEx(m_goplsPath, args);
	__initLSP();
}

void GolangPls::__stop()
{
	m_process->stop(3000);
}

int GolangPls::__nextId()
{
	m_nRequestId++;
	return m_nRequestId;
}

void GolangPls::__regCall(QString method, LspCall lspCall)
{
	m_methodCallMap[method] = lspCall;
}

void GolangPls::__request(QVariantMap msg)
{
	QJson::Serializer s;
	QByteArray body = s.serialize(msg);
	QByteArray header = QString::asprintf("Content-Length:%d\r\n\r\n", QString(body).length()).toUtf8();
	QByteArray data = header + body;
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

void GolangPls::__initLSP()
{
	QVariantMap _map;
	_map["processId"] = m_process->processId();
	
	QVariantMap clientInfo;
	clientInfo["name"] = "gopls-plugin";
	clientInfo["version"] = "1.0.0";
	_map["clientInfo"] = clientInfo;
	_map["rootUri"] = "file://D:/2.WorkSpace/third_party/___Go";
	__requestLSP(LSPMethod::Initialize, _map, [=](GolangPls* pls, QVariantMap __map) {
		pls->__requestLSP(LSPMethod::Initialized, QVariantMap());
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
			for (int i = 0; i < __items.size(); i++)
			{
				QVariantMap __item = __items[i].toMap();
				//xItem["label"].toString();
				qDebug() << "label:" << __item["label"].toString() << "kind:" << __item["kind"].toString() << "detail:" << __item["detail"].toString();
			}

	});

	//qDebug() << "-----%%%%%-----\n" << resp << "-----%%%%%-----\n";
	//qDebug() << "-----%%%%%-----\n";
	
	//QString s = QString::fromUtf8(resp);
	//s.remove(s.indexOf("{"));

	//QByteArray sb = s.toUtf8();

	//QVector<QByteArray> sbs = parseLspData(resp);
	//for (int i = 0; i < sbs.size(); i++)
	//{
	//	QJson::Parser parser;
	//	QVariantMap xResp = parser.parse(sbs[i]).toMap();
	//	if (!xResp.contains("result"))
	//	{
	//		qDebug() << "can't find result.";
	//		//return;

	//		if (xResp["method"] == "window/logMessage" || xResp["method"] == "windows/showMessage")
	//		{
	//			qDebug() << xResp["params"].toMap()["message"].toString();
	//		}

	//		continue;
	//	}

	//	QVariantMap xResult = xResp["result"].toMap();
	//	if (!xResult.contains("items"))
	//	{
	//		qDebug() << "can't find items";
	//		continue;
	//	}

	//	QVariantList xItems = xResult["items"].toList();
	//	for (int i = 0; i < xItems.size(); i++)
	//	{
	//		QVariantMap xItem = xItems[i].toMap();
	//		//xItem["label"].toString();
	//		qDebug() << "label:" << xItem["label"].toString() << "kind:" << xItem["kind"].toString() << "detail:" << xItem["detail"].toString();
	//	}
	//}

	//resp["result"].toList();


	//qDebug() << "-----%%%%%-----\n";
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
	QVariantMap params;
	QVariantMap textDocument;
	textDocument["uri"] = "file://" + filepath;
	textDocument["languageId"] = "go";
	textDocument["version"] = version;
	textDocument["text"] = content;
	params["textDocument"] = textDocument;
	__requestLSP(LSPMethod::TextDocumentDidOpen, params);
}

void GolangPls::__didChange(QString filepath, QString content, int version)
{
	QVariantMap params;
	QVariantMap textDocument;
	textDocument["uri"] = "file://" + filepath;
	textDocument["version"] = version;
	params["textDocument"] = textDocument;

	QVariantList contentChanges;
	QVariantMap text;
	text["text"] = content;
	contentChanges.append(text);
	params["contentChanges"] = contentChanges;
	__requestLSP(LSPMethod::TextDocumentDidChange, params);
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
		__setCompleter(completer);
	}
	else if (editor->mimeType() == "browser/goplay") {
		LiteApi::IEditor* pedit = LiteApi::findExtensionObject<LiteApi::IEditor*>(m_liteApp->extension(), "LiteApi.Goplay.IEditor");
		if (pedit && pedit->mimeType() == "text/x-gosrc") {
			editor = pedit;
			LiteApi::ICompleter* completer = LiteApi::findExtensionObject<LiteApi::ICompleter*>(editor, "LiteApi.ICompleter");
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
	QString filePath = editor->filePath();
	__didOpen(filePath, LiteApi::getLiteEditor(editor)->document()->toPlainText(), 1);
}

void GolangPls::__onEditorAboutToClose(LiteApi::IEditor* editor)
{
}

void GolangPls::__onPrefixChanged(QTextCursor cur, QString pre, bool force)
{
	qDebug() << "__onPrefixChanged ----------\n";
	QString txt = m_editor->document()->toPlainText();

	//static int version = 0;
	__didChange(m_fileInfo.path(), txt, __nextId());

	qDebug() << " -------- txt ----------";
	qDebug() << txt;

	// row and col
	int row = cur.blockNumber();      
	int col = cur.columnNumber();        
	qDebug() << "row:" << row << "col:" << col;
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
	//int i = 0;
}

