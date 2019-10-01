/*
 * Copyright (C) 2019 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KIMAGEANNOTATOR_ANNOTATIONSETTINGS_H
#define KIMAGEANNOTATOR_ANNOTATIONSETTINGS_H

#include <QWidget>

#include "WidgetConfigurator.h"
#include "src/widgets/ToolPicker.h"
#include "src/widgets/ColorPicker.h"
#include "src/widgets/NumberPicker.h"
#include "src/widgets/FillTypePicker.h"
#include "src/backend/Config.h"
#include "src/annotations/properties/AnnotationTextProperties.h"
#include "src/annotations/properties/AnnotationBlurProperties.h"
#include "src/annotations/items/AbstractAnnotationItem.h"
#include "src/annotations/core/AbstractSettingsProvider.h"

namespace kImageAnnotator {

class AnnotationSettings : public QWidget, public AbstractSettingsProvider
{
	Q_OBJECT
public:
	explicit AnnotationSettings(Config *config);
	~AnnotationSettings() override;
	void loadFromItem(AbstractAnnotationItem *item);
	void activateSelectTool() override;
	ToolTypes toolType() const override;
	QColor toolColor() const override;
	QColor textColor() const override;
	int toolWidth() const override;
	int fontSize() const override;
	FillTypes fillType() const override;
	int blurRadius() const override;

signals:
	void toolChanged(ToolTypes toolType) const override;
	void firstBadgeNumberChanged(int number) const override;

private:
	QVBoxLayout *mMainLayout;
	ToolPicker *mToolPicker;
	ColorPicker *mColorPicker;
	NumberPicker *mWidthPicker;
	ColorPicker *mTextColorPicker;
	NumberPicker *mFontSizePicker;
	FillTypePicker *mFillTypePicker;
	NumberPicker *mFirstNumberPicker;
	NumberPicker *mBlurRadiusPicker;
	Config *mConfig;
	WidgetConfigurator mWidgetConfigurator;

	void initGui();
	void loadFromConfig(ToolTypes tool);

private slots:
	void loadToolTypeFromConfig();
	void saveToolType(ToolTypes toolType);
	void saveToolColor(const QColor &color);
	void saveToolTextColor(const QColor &color);
	void saveToolWidth(int size);
	void saveToolFontSize(int size);
	void saveToolFillType(FillTypes fill);
	void saveFirstBadgeNumber(int size);
	void saveBlurRadius(int radius);
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_ANNOTATIONSETTINGS_H
