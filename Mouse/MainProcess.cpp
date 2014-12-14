#include <MainProcess.h>

#include <QtWidgets\qfiledialog.h>

CMainProccess::CMainProccess() :
	QObject( 0 )
{
	initializerWidget.show();
	connect( &initializerWidget, SIGNAL( OnComplete( int ) ), this, SLOT( onInititalized( int ) ) );
	connect( &sendFileWidget, SIGNAL( Transfer( QString, quint32, QString ) ), this, SLOT( onTransferFile( QString, quint32, QString ) ) );
}

void CMainProccess::onInititalized( int port )
{
	server = new CMouseServer( port, this );
	connect( server, SIGNAL( OnPrepareFileTransfering( QString ) ), this, SLOT( onPrepareFileTransfer( QString ) ) );
	connect( this, SIGNAL( SaveFileSelected( QString ) ), server, SLOT( OnReadyToObtainFile( QString ) ) );
	initializerWidget.hide();
	sendFileWidget.show();
}

void CMainProccess::onTransferFile( QString host, quint32 port, QString fileName )
{
	client = new CMouseClient( host, port, fileName, this );
}

void CMainProccess::onPrepareFileTransfer( QString fileName )
{
	QString saveFileName = QFileDialog::getSaveFileName( &sendFileWidget, "Select file to save " );
	emit SaveFileSelected( saveFileName );
}