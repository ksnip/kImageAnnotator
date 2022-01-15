/*
 * Copyright (C) 2021 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
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

#ifndef KIMAGEANNOTATOR_CUTWIDGET_H
#define KIMAGEANNOTATOR_CUTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QGroupBox>

#include "CutView.h"
#include "CutSelectionRestrictor.h"
#include "src/annotations/core/AnnotationArea.h"
#include "src/gui/selection/SelectionHandler.h"
#include "src/gui/selection/SelectionHandlesHorizontal.h"
#include "src/gui/selection/SelectionHandlesVertical.h"
#include "src/common/helper/KeyHelper.h"
#include "src/widgets/settingsPicker/ZoomPicker.h"

namespace kImageAnnotator {

class CutWidget : public QWidget
{
	Q_OBJECT
public:
	explicit CutWidget(QWidget *parent);
	~CutWidget() override = default;
	void activate(AnnotationArea *annotationArea);

signals:
	void closing() const;

private:
	AnnotationArea *mAnnotationArea;
	KeyHelper *mKeyHelper;
	SelectionHandler *mSelectionHandler;
	CutView *mCutView;
	ZoomPicker *mZoomPicker;
	QVBoxLayout *mMainLayout;
	QHBoxLayout *mPanelLayout;
	QHBoxLayout *mOrientationLayout;
	QPushButton *mApplyButton;
	QPushButton *mCancelButton;
	QGroupBox *mOrientationGroupBox;
	QRadioButton *mVerticalOrientationRadioButton;
	QRadioButton *mHorizontalOrientationRadioButton;
	qreal mDefaultSelectionWidth;

	void initGui();
	void initKeyHelper();
	void initSelectionHandler() const;
	void reset();
	void initZoomPicker() const;
	bool isVerticalOrientation() const;

private slots:
	void cut();
	void selectionChanged(const QRectF &rect);
	void orientationChanged();
};

} // kImageAnnotator namespace

#endif //KIMAGEANNOTATOR_CUTWIDGET_H
