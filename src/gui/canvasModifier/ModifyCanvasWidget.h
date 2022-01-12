/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KIMAGEANNOTATOR_MODIFYCANVASWIDGET_H
#define KIMAGEANNOTATOR_MODIFYCANVASWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QIntValidator>
#include <QCheckBox>

#include "ModifyCanvasView.h"
#include "ModifyCanvasSelectionRestrictor.h"
#include "src/annotations/core/AnnotationArea.h"
#include "src/common/helper/KeyHelper.h"
#include "src/gui/selection/SelectionHandler.h"
#include "src/gui/selection/SelectionHandlesAll.h"
#include "src/widgets/ColorDialogButton.h"
#include "src/widgets/settingsPicker/ZoomPicker.h"

namespace kImageAnnotator {

class ModifyCanvasWidget : public QWidget
{
Q_OBJECT
public:
	explicit ModifyCanvasWidget();
	~ModifyCanvasWidget() override;
	void activate(AnnotationArea *annotationArea);

signals:
	void closing() const;

protected:
	void keyReleaseEvent(QKeyEvent *event) override;

private:
	AnnotationArea *mAnnotationArea;
	KeyHelper *mKeyHelper;
	SelectionHandler *mSelectionHandler;
	ModifyCanvasView *mModifyCanvasView;
	QVBoxLayout *mMainLayout;
	QHBoxLayout *mPanelLayout;
	QPushButton *mApplyButton;
	QPushButton *mCancelButton;
	QLineEdit *mPositionXLineEdit;
	QLineEdit *mPositionYLineEdit;
	QLineEdit *mWidthLineEdit;
	QLineEdit *mHeightLineEdit;
	QLabel *mPositionXLabel;
	QLabel *mPositionYLabel;
	QLabel *mWidthLabel;
	QLabel *mHeightLabel;
	QLabel *mColorLabel;
	QIntValidator *mInputValidator;
	QCheckBox *mRestrictCheckBox;
	ColorDialogButton *mColorDialogButton;
	ZoomPicker *mZoomPicker;

	void initGui();
	void initKeyHelper();
	void initSelectionHandler() const;
	void reset();
	void initZoomPicker();

private slots:
	void apply();
	void selectionChanged(const QRectF &rect);
	void xChanged(const QString &text);
	void yChanged(const QString &text);
	void widthChanged(const QString &text);
	void heightChanged(const QString &text);
	void restrictionChanged();
};

} // kImageAnnotator namespace

#endif //KIMAGEANNOTATOR_MODIFYCANVASWIDGET_H
