#include <Client.h>

#include <assert.h>

#include <QtCore\qdatastream.h>
#include <QtCore\qfile.h>

CMouseClient::CMouseClient( const QString& host, int port, const QString& file, QObject* parent ) :
	QObject( parent ),
	fileName( file ),
	nextBlockSize( 0 )
{
	connection = new QTcpSocket( this );
	connection->connectToHost( host, port );

	connect( connection, SIGNAL( readyRead() ), SLOT( onReadyRead() ) );
	connect( connection, SIGNAL( error( QAbstractSocket::SocketError ) ), SLOT( onError( QAbstractSocket::SocketError ) ) );
}

void CMouseClient::sendToServer()
{
	QByteArray arrBlock;
	QDataStream out( &arrBlock, QIODevice::WriteOnly );

	QFile file( fileName );
	file.open( QFile::ReadOnly );
	QByteArray fileContent = file.readAll();
	out << ( quint32 )0;
	out << fileContent;

	out.device()->seek( 0 );
	out << quint32( arrBlock.size() - sizeof( quint32 ) );

	connection->write( arrBlock );
} 

void CMouseClient::onReadyRead()
{
	QDataStream in( connection );
	in.setVersion( QDataStream::Qt_5_3 );

	while( true ) {
		if( nextBlockSize == 0 ) {
			if( connection->bytesAvailable() < sizeof( quint32 ) ) {
				break;
			}

			in >> nextBlockSize;
		}

		if( connection->bytesAvailable() < nextBlockSize ) {
			return;
		}

		QString message;
		in >> message;

		if( message == "READY" ) {
			sendToServer();
		} else if( message == "COMPLETE" ) {
			connection->disconnectFromHost();
		} else {
			assert( false );
		}
	}
}

void CMouseClient::onError( QAbstractSocket::SocketError error )
{
	qDebug() << "Socket message: "<< connection->errorString() << " Error code: "  << error;
}