/*
 * Copyright (C) 2018 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef KIMAGEANNOTATOR_CROPWIDGET_H
#define KIMAGEANNOTATOR_CROPWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QIntValidator>

#include "src/annotations/core/AnnotationArea.h"
#include "CropView.h"

namespace kImageAnnotator {

class CropWidget : public QWidget
{
Q_OBJECT
public:
	explicit CropWidget(AnnotationArea *annotationArea);
	~CropWidget();

signals:
	void done();

protected:
	void keyPressEvent(QKeyEvent *event) override;

private:
	AnnotationArea *mAnnotationArea;
	CropView *mCropView;
	QVBoxLayout *mMainLayout;
	QHBoxLayout *mPanelLayout;
	QPushButton *mCropButton;
	QPushButton *mCancelButton;
	QLineEdit *mPositionXLineEdit;
	QLineEdit *mPositionYLineEdit;
	QLineEdit *mWidthLineEdit;
	QLineEdit *mHeightLineEdit;

	void initGui();

private slots:
	void crop();
	void selectedRectChanged(const QRectF &rect);
	void xChanged(const QString &text);
	void yChanged(const QString &text);
	void widthChanged(const QString &text);
	void heightChanged(const QString &text);
};

}

#endif //KIMAGEANNOTATOR_CROPWIDGET_H
