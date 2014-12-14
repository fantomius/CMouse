#include <server.h>

#include <assert.h>

#include <QtCore\qdatastream.h>
#include <QtCore\qfile.h>
#include <QtNetwork\qtcpserver.h>
#include <QtNetwork\qtcpsocket.h>

CMouseServer::CMouseServer( int port, QObject* parent ) :
QObject( parent ),
readyToObtainFile( false ),
blockSize( 0 ),
currentCaller( 0 )
{
	server = new QTcpServer( this );
	if( !server->listen( QHostAddress::Any, port ) ) {
		// TODO: Normal error handling
		qDebug() << "Problem on listen port " << port << "Server msg: " << server->errorString();
		server->close();
		return;
	}

	connect( server, SIGNAL( newConnection() ), this, SLOT( onNewConnection() ) );
}

void CMouseServer::OnReadyToObtainFile( QString filePath )
{
	currentFilePath = filePath;
	readyToObtainFile = true;

	onReadClient();
}

void CMouseServer::onReadClient()
{
	assert( currentCaller != 0 );
	QDataStream in( currentCaller );
	in.setVersion( QDataStream::Qt_5_3 );

	if( blockSize == 0 ) {
		if( currentCaller->bytesAvailable() < sizeof( quint32 ) ) {
			return;
		}
		in >> blockSize;
		emit OnPrepareFileTransfering( "" );
	}

	if( !readyToObtainFile || currentCaller->bytesAvailable() < blockSize ) {
		return;
	}

	QFile file( currentFilePath );
	file.open( QIODevice::WriteOnly | QIODevice::Truncate );
	QByteArray data;
	in >> data;
	file.write( data );
	
	sendToClient( currentCaller, "COMPLETE" );
	currentCaller->disconnectFromHost();
	blockSize = 0;
	currentFilePath = "";
	currentCaller = 0;
}

void CMouseServer::onNewConnection()
{
	if( currentCaller != 0 ) {
		return;
	}

	QTcpSocket* socket = server->nextPendingConnection();

	connect( socket, SIGNAL( disconnected() ), socket, SLOT( deleteLater() ) );
	connect( socket, SIGNAL( readyRead() ), this, SLOT( onReadClient() ) );

	currentCaller = socket;
	sendToClient( currentCaller, "READY" );
}

void CMouseServer::sendToClient( QTcpSocket* socket, const QString& str )
{
	QByteArray bytes;
	QDataStream out( &bytes, QIODevice::WriteOnly );
	out.setVersion( QDataStream::Qt_5_3 );
	out << quint32( 0 ) << str;
	out.device()->seek( 0 );
	out << quint32( bytes.size() - sizeof( quint32 ) );

	socket->write( bytes );
}