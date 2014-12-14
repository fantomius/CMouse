#pragma once

#include <QtCore\qobject.h>
#include <InitializerWidget.h>
#include <SendFileWidget.h>
#include <Server.h>
#include <Client.h>

class CMainProccess : public QObject {
Q_OBJECT
public:
	CMainProccess();

signals:
	void SaveFileSelected( QString filePath );

private slots:
	void onInititalized( int port );
	void onTransferFile( QString host, quint32 port, QString fileName );
	void onPrepareFileTransfer( QString fileName );

private:
	CInitializerWidget initializerWidget;
	CSendFileWidget sendFileWidget;

	CMouseServer* server;
	CMouseClient* client;
};