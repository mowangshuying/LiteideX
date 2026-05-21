#include "GolangPls.h"
#include "qjson/include/QJson/Parser"
#include "qjson/include/QJson/Serializer"
#include <QEventLoop>

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
	connect(m_liteApp->editorManager(), &LiteApi::IEditorManager::currentEditorChanged, this, &GolangPls::__onCurrentEditorChanged);
}

void GolangPls::__start()
{
	QStringList args;
	//QString gopls = LiteApi::getGoPls(m_liteApp);
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

void GolangPls::__send(QVariantMap msg)
{
	QJson::Serializer s;
	QByteArray body = s.serialize(msg);
	QByteArray header = QString::asprintf("Content-Length:%d\r\n\r\n", QString(body).length()).toUtf8();

	QByteArray data = header + body;

	m_process->write(data);
}

void GolangPls::__sendLSP(QString method, QVariantMap params)
{
	QVariantMap msg;
	msg["jsonrpc"] = "2.0";
	msg["id"] = __nextId();
	msg["method"] = method;
	msg["params"] = params;
	__send(msg);
}

QByteArray GolangPls::__sendLSPBlocking(QString method, QVariantMap params, int nTimeOutMs)
{
	QEventLoop loop;
	connect(m_process, &Process::readyReadStandardOutput, &loop, &QEventLoop::quit);
	connect(m_process, &Process::readyReadStandardError, &loop, &QEventLoop::quit);

	__sendLSP(method, params);
	int nRet = loop.exec(QEventLoop::ExcludeUserInputEvents);
	if (nRet == -1)
	{
		return QByteArray();
	}

	QByteArray output = m_process->readAllStandardOutput();
	if (output.isEmpty())
	{
		output = m_process->readAllStandardError();
	}
	return output;
}

void GolangPls::__initLSP()
{
	QVariantMap varmap;
	varmap["processId"] = m_process->processId();
	
	QVariantMap clientInfo;
	clientInfo["name"] = "gopls-plugin";
	clientInfo["version"] = "1.0.0";
	varmap["clientInfo"] = clientInfo;
	varmap["rootUri"] = "file://E:/code/___Go";

	QByteArray resp = __sendLSPBlocking(LSPMethod::Initialize, varmap);
	__sendLSP(LSPMethod::Initialized, QVariantMap());
}

void GolangPls::__setCompleter(LiteApi::ICompleter* completer)
{
	if (m_completer != nullptr)
		disconnect(m_completer, 0, this, 0);

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
	QByteArray resp = __sendLSPBlocking("textDocument/completion", params);
	//qDebug() << "-----%%%%%-----\n" << resp << "-----%%%%%-----\n";
	qDebug() << "-----%%%%%-----\n";
	
	QJson::Parser parser;
    QVariantMap result = parser.parse (resp);

	qDebug() << "-----%%%%%-----\n";
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

void GolangPls::__onPrefixChanged(QTextCursor cur, QString pre, bool force)
{
	qDebug() << "__onPrefixChanged ----------\n";
	QString txt = cur.document()->toPlainText();
	txt.replace("\r\n", "\n");
	//QByteArray data =  txt.left(cur.position()).toUtf8();

	// row and col
	int row = cur.blockNumber();      // ÐÐºÅ
	int col = cur.columnNumber();     // ÁÐºÅ
	__completion(m_fileInfo.filePath(), row, col);
}

void GolangPls::__onWordCompleted(QString, QString, QString)
{

}

