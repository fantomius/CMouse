#pragma once

#include <QtCore\qstring.h>
#include <QtCore\qobject.h>

class QTcpServer;
class QTcpSocket;

class CMouseServer : public QObject {
	Q_OBJECT
public:
	CMouseServer( int port, QObject* parent );

signals:
	void OnPrepareFileTransfering( QString );

public slots:
	void OnReadyToObtainFile( QString filePath );

private slots:
	void onNewConnection();
	void onReadClient();

private:
	void sendToClient( QTcpSocket* socket, const QString& str );

	QTcpServer* server;
	quint32 blockSize;
	bool readyToObtainFile;
	QString currentFileName;
	QString currentFilePath;
	QTcpSocket* currentCaller;
};