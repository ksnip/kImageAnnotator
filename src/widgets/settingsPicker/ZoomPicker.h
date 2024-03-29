/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef KIMAGEANNOTATOR_ZOOMPICKER_H
#define KIMAGEANNOTATOR_ZOOMPICKER_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QButtonGroup>
#include <QAction>

#include "src/widgets/CustomSpinBox.h"
#include "src/widgets/CustomToolButton.h"
#include "src/widgets/CustomToolButtonAction.h"
#include "src/widgets/settingsPicker/SettingsPickerWidget.h"
#include "src/common/helper/IconLoader.h"
#include "src/common/provider/ScaledSizeProvider.h"

namespace kImageAnnotator {

class ZoomPicker : public SettingsPickerWidget
{
Q_OBJECT
public:
	explicit ZoomPicker(QWidget *parent);
	~ZoomPicker() override = default;

public slots:
	void setZoomValue(double value);
	void fitImageToCurrentView();

signals:
	void zoomValueChanged(double zoomLevel);
	void fitImageToView();

protected:
	QWidget* expandingWidget() override;

private:
	QHBoxLayout *mLayout;
	QLabel *mLabel;
	CustomSpinBox *mSpinBox;
	QAction *mZoomInAction;
	QAction *mZoomOutAction;
	QAction *mResetZoomAction;
	CustomToolButton *mResetZoomButton;
	QAction *mFitImageAction;
	CustomToolButton *mFitImageButton;
	QAction *createAction(const QString &tooltip, const QIcon &icon);
	CustomToolButton *createButton(QAction *defaultAction);
	void initGui();

private slots:
	void notifyZoomValueChanged(double value);
	void zoomIn();
	void zoomOut();
	void resetZoomOut();
	QString getToolTip() const;
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_ZOOMPICKER_H
