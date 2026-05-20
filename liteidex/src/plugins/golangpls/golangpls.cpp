#include "GolangPls.h"
#include "qjson/include/QJson/Parser"
#include "qjson/include/QJson/Serializer"
#include <QEventLoop>

GolangPls::GolangPls(LiteApi::IApplication* app, QObject* parent)
	: QObject(parent)
{
	m_liteApp = app;
	m_nRequestId = 0;
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
	//connect(m_process, &Process::readyReadStandardOutput, this, [=]() {
	//	QByteArray output = m_process->readAllStandardOutput();
	//	qDebug() << "output£º" << output;
	//	});

	//connect(m_process, &Process::readyReadStandardError, this, [=]() {
	//	QByteArray output = m_process->readAllStandardError();
	//	qDebug() << "output£º" << output;
	//	});
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
	varmap["rootUri"] = "file://D:/2.WorkSpace/third_party/___Go";

	QByteArray resp = __sendLSPBlocking(LSPMethod::Initialize, varmap);
	//qDebug() << "resp:" << resp;

	//QByteArray readall = m_process->readAll();

}

