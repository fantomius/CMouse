#include <SendFileWidget.h>

#include <QtWidgets\qlayout.h>
#include <QtWidgets\qlabel.h>
#include <QtWidgets\qlineedit.h>
#include <QtWidgets\qspinbox.h>
#include <QtWidgets\qpushbutton.h>
#include <QtWidgets\qfiledialog.h>

CSendFileWidget::CSendFileWidget( QWidget* parent ) :
QWidget( parent )
{
	QLabel* serverHostLabel = new QLabel( "&Server address: ", this );
	host = new QLineEdit( this );
	serverHostLabel->setBuddy( host );

	QLabel* portLabel = new QLabel( "Server &Port:", this );
	port = new QSpinBox( this );
	port->setMinimum( 0 );
	port->setMaximum( SHRT_MAX );
	portLabel->setBuddy( port );

	QLabel* fileLabel = new QLabel( "&File:", this );
	fileName = new QLineEdit( this );

	QPushButton* openFileDialogBtn = new QPushButton( "...", this );
	QPushButton* transmit = new QPushButton( "Transmit", this );

	/*QHBoxLayout* selectFileLayout = new QHBoxLayout( this );
	selectFileLayout->addWidget( fileName );
	selectFileLayout->addWidget( openFileDialogBtn );*/

	QVBoxLayout* layout = new QVBoxLayout( this );
	layout->addWidget( serverHostLabel );
	layout->addWidget( host );
	layout->addWidget( portLabel );
	layout->addWidget( port );
	layout->addWidget( fileLabel );
	layout->addWidget( fileName );
	layout->addWidget( openFileDialogBtn );
	layout->addWidget( transmit );

	setLayout( layout );

	connect( openFileDialogBtn, SIGNAL( clicked() ), this, SLOT( onSelectFileButtonClick() ) );
	connect( transmit, SIGNAL( clicked() ), this, SLOT( onTransferButtonClick() ) );
}

void CSendFileWidget::onTransferButtonClick()
{
	QString hostName = host->text();
	int portValue = port->value();
	QString transferFileName = fileName->text();

	emit Transfer( hostName, portValue, transferFileName );
}

void CSendFileWidget::onSelectFileButtonClick()
{
	fileName->setText( QFileDialog::getOpenFileName( this, "Select transfer file" ) );
}