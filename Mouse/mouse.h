#ifndef MOUSE_H
#define MOUSE_H

#include <QtWidgets\qlabel.h>

class CMouse : public QLabel {
	Q_OBJECT

public:
	CMouse( QWidget *parent = 0 ) :
		QLabel( "Server", parent )
	{

	}
};

#endif // MOUSE_H
