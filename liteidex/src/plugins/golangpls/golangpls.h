#pragma once

#include <QObject>
#include "liteapi/liteapi.h"
#include "liteenvapi/liteenvapi.h"
#include "processex/processex.h"
#include "liteeditorapi/liteeditorapi.h"
//#include "qjson/include/QJson/Parser"
//#include "qjson/include/QJson/Serializer"

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

	const QString WorkspaceGoplsGetPackage = "workspace/gopls/get_package";
	const QString WorkspaceGoplsTidy = "workspace/gopls/tidy";
};

class GolangPls  : public QObject
{
	Q_OBJECT

public:
	GolangPls(LiteApi::IApplication* app, QObject* parent = nullptr);
	~GolangPls();

	void __init();

	void __start();

	void __stop();

	int __nextId();

	void __send(QVariantMap msg);

	void __sendLSP(QString method, QVariantMap params);
	QByteArray __sendLSPBlocking(QString method, QVariantMap params, int nTimeOutMs = 3000);

	void __initLSP();

	void __setCompleter(LiteApi::ICompleter* completer);

	void __completion(QString filePath, int line, int column);

public slots:
	void __onStarted();

	void __onFinished(int code, QProcess::ExitStatus status);

	void __onCurrentEditorChanged(LiteApi::IEditor* editor);

	void __onPrefixChanged(QTextCursor cur,QString pre,bool force);

	void __onWordCompleted(QString, QString, QString);
protected:
	Process* m_process;
	int m_nRequestId;
	QString m_goplsPath;
	LiteApi::IApplication* m_liteApp;
	LiteApi::IEditor* m_editor;
	QFileInfo m_fileInfo;

	LiteApi::ICompleter* m_completer;
};

