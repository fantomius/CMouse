#pragma once

#include <QtWidgets\qwidget.h>

class QSpinBox;

class CInitializerWidget : public QWidget {
Q_OBJECT
public:
	CInitializerWidget( QWidget* parent = 0 );

signals:
	void OnComplete( int connectionPort );

private slots:
	void onOk();

private:
	QSpinBox* spin;
};