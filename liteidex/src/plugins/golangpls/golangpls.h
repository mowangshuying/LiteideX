#pragma once

#include <QObject>
#include "liteapi/liteapi.h"
#include "liteenvapi/liteenvapi.h"
#include "processex/processex.h"
#include "liteeditorapi/liteeditorapi.h"
#include <functional>
#include <QDateTime>
#include <QMap>

namespace LSPMethod {
	const QString Initialize = "initialize";
	const QString Initialized = "initialized";
	const QString Shutdown = "shutdown";
	const QString Exit = "exit";

	const QString TextDocumentDidOpen = "textDocument/didOpen";
	const QString TextDocumentDidChange = "textDocument/didChange";
	const QString TextDocumentDidClose = "textDocument/didClose";
	const QString TextDocumentDidSave = "textDocument/didSave";

	const QString TextDocumentCompletion = "textDocument/completion";
	const QString TextDocumentDefinition = "textDocument/definition";
	const QString TextDocumentHover = "textDocument/hover";
	const QString TextDocumentDiagnostic = "textDocument/diagnostic";
	const QString TextDocumentDocumentSymbol = "textDocument/documentSymbol";
	const QString TextDocumentReferences = "textDocument/references";
	const QString TextDocumentRename = "textDocument/rename";
	
	const QString WindowShowMessage = "window/showMessage";
	const QString WindowLogMessage = "window/logMessage";

	const QString WorkspaceGoplsGetPackage = "workspace/gopls/get_package";
	const QString WorkspaceGoplsTidy = "workspace/gopls/tidy";
};

class GolangPls  : public QObject
{
	Q_OBJECT
public:
	using LspCall = std::function<void(GolangPls*, QVariantMap)>;
	class LspCallData {
	public:
		LspCallData()
		{
			_lspCall = nullptr;
			_dt = 0;
		}

		LspCall _lspCall;
		qint64  _dt;
	};
public:
	GolangPls(LiteApi::IApplication* app, QObject* parent = nullptr);
	~GolangPls();

	void __init();

	void __start();

	void __stop();

	int __nextId();
	int __nextVersion();

	void __regCall(QString method, LspCall lspCall);

	void __request(QVariantMap msg);
	void __requestLSP(QString method, QVariantMap params, int id);
	void __requestLSP(QString method,  QVariantMap params, LspCall lspCall = nullptr);

	void _notify(QString method, QVariantMap params);

	
	void __onMsg(QString method, QVariantMap msg);

	void __onMsg(int msgId, QVariantMap msg);


	void __initLSP();

	void __setCompleter(LiteApi::ICompleter* completer);

	void __completion(QString filePath, int line, int column);
	QVector<QByteArray> parseLspData(QByteArray& rawData);

	void __didOpen(QString filepath, QString content, int version);
	void __didClose(QString filepath);
	void __didChange(QString filepath, QString content, int version);

public slots:
	void __onStarted();

	void __onFinished(int code, QProcess::ExitStatus status);

	void __onCurrentEditorChanged(LiteApi::IEditor* editor);
	void __onEditorCreated(LiteApi::IEditor* editor);
	void __onEditorAboutToClose(LiteApi::IEditor* editor);

	void __onPrefixChanged(QTextCursor cur,QString pre,bool force);

	void __onWordCompleted(QString, QString, QString);

	void __onReadyReadStandardOutput();
	void __onReadyReadStandardError();
protected:
	Process* m_process;
	int m_nRequestId;
	int m_nVersion;
	QString m_goplsPath;
	LiteApi::IApplication* m_liteApp;
	LiteApi::ITextEditor* m_editor;
	QFileInfo m_fileInfo;

	LiteApi::ICompleter* m_completer;
	QByteArray ___lspBuffer;

	QMap<QString, LspCall> m_methodCallMap;
	QMap<int, LspCallData> m_requestCallMap;
};

