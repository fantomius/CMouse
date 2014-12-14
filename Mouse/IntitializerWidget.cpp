#include <InitializerWidget.h>

#include <QtWidgets\qlayout.h>
#include <QtWidgets\qlabel.h>
#include <QtWidgets\qspinbox.h>
#include <QtWidgets\qpushbutton.h>

CInitializerWidget::CInitializerWidget( QWidget* parent ) :	
	QWidget( parent )
{
	QLabel* label = new QLabel( "Please, enter working &port:", this );
	spin = new QSpinBox( this );
	spin->setMinimum( 0 );
	spin->setMaximum( SHRT_MAX );
	label->setBuddy( spin );
	QPushButton* okBtn = new QPushButton( "OK", this );

	QVBoxLayout* layout = new QVBoxLayout( this );
	layout->addWidget( label );
	layout->addWidget( spin );
	layout->addWidget( okBtn );

	connect( okBtn, SIGNAL( clicked() ), this, SLOT( onOk() ) );
}

void CInitializerWidget::onOk()
{
	int portNumber = spin->value();
	emit OnComplete( portNumber );
}

