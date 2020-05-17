/*
 * Copyright (C) 2018 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KIMAGEANNOTATOR_WIDGETCONFIGURATORSWITCHER_H
#define KIMAGEANNOTATOR_WIDGETCONFIGURATORSWITCHER_H

#include <QWidget>

#include "src/common/enum/ToolTypes.h"
#include "src/widgets/ColorPicker.h"
#include "src/widgets/FillTypePicker.h"
#include "src/widgets/ToolPicker.h"
#include "src/widgets/NumberPicker.h"
#include "src/widgets/StickerPicker.h"

namespace kImageAnnotator {

class WidgetConfigurator
{
public:
	explicit WidgetConfigurator();
	~WidgetConfigurator() = default;
	void setCurrentTool(ToolTypes tool);
	void setColorWidget(ColorPicker *widget);
	void setTextColorWidget(ColorPicker *widget);
	void setWidthWidget(NumberPicker *widget);
	void setFillTypeWidget(FillTypePicker *widget);
	void setFontSizeWidget(NumberPicker *widget);
	void setFirstNumberWidget(NumberPicker *widget);
	void setBlurRadiusWidget(NumberPicker *widget);
	void setStickerWidget(StickerPicker *widget);

private:
	ToolTypes mCurrentTool;
	ColorPicker *mColorWidget;
	ColorPicker *mTextColorWidget;
	NumberPicker *mWidthWidget;
	FillTypePicker *mFillTypeWidget;
	NumberPicker *mFontSizeWidget;
	NumberPicker *mFirstNumberWidget;
	NumberPicker *mBlurRadiusWidget;
	StickerPicker *mStickerWidget;

	void updateWidgets() const;
	void updateProperties() const;
	void updateVisibility() const;
	void setColorWidgetEnabled(bool enabled) const;
	void setTextColorWidgetEnabled(bool enabled) const;
	void setWidthWidgetEnabled(bool enabled) const;
	void setFillWidgetEnabled(bool enabled) const;
	void setFontSizeWidgetEnabled(bool enabled) const;
	void setFirstNumberWidgetEnabled(bool enabled) const;
	void setNoFillAndNoBorderEnabled(bool enabled) const;
	void setBlurRadiusWidgetEnabled(bool enabled) const;
	void setStickerWidgetEnabled(bool enabled) const;
};

} // namespace kImageAnnotator

#endif // KIMAGEANNOTATOR_WIDGETCONFIGURATORSWITCHER_H
