#pragma once

#include <QtWidgets\qwidget.h>
#include <QtCore\qstring.h>

class QLineEdit;
class QSpinBox;

class CSendFileWidget : public QWidget {
Q_OBJECT
public:
	CSendFileWidget( QWidget* parent = 0 );

signals:
	void Transfer( QString host, quint32 port, QString fileName );

private slots:
	void onSelectFileButtonClick();
	void onTransferButtonClick();

private:
	QLineEdit* host;
	QSpinBox* port;
	QLineEdit* fileName;
};