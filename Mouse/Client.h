#pragma once

#include <QtCore\qstring.h>
#include <QtCore\qobject.h>
#include <QtNetwork\qtcpsocket.h>

class CMouseClient : public QObject {
Q_OBJECT
public:
	CMouseClient( const QString& host, int port, const QString& file, QObject* parent = 0 );

private slots:
	void onReadyRead();
	void onError( QAbstractSocket::SocketError );

private:
	void sendToServer();

	QTcpSocket* connection;
	quint32 nextBlockSize;
	QString fileName;
};