#ifndef ORIENTATION_H
#define ORIENTATION_H

#include "rotatableimageview.h"
#include "../qinterface/qnavdatalistener.h"
#include <QWidget>
#include <QLabel>

class Orientation : public QWidget, public QNavdataListener
{
	Q_OBJECT
	
	public:
		explicit Orientation(QWidget *parent = 0);
	public Q_SLOTS:
		void navdataAvailable(std::shared_ptr<const drone::navdata> nd);
	private:
		QLabel *yawLabel;
		QLabel *pitchLabel;
		QLabel *rollLabel;
		RotatableImageView *yawIndicator;
		RotatableImageView *pitchIndicator;
		RotatableImageView *rollIndicator;
};

#endif
