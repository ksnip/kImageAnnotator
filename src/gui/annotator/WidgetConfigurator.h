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

#ifndef KIMAGEANNOTATOR_WIDGETCONFIGURATORSWITCHER_H
#define KIMAGEANNOTATOR_WIDGETCONFIGURATORSWITCHER_H

#include <QWidget>

#include "src/common/enum/ToolTypes.h"
#include "src/widgets/ColorPicker.h"
#include "src/widgets/FillTypePicker.h"
#include "src/widgets/ToolPicker.h"
#include "src/widgets/SizePicker.h"

namespace kImageAnnotator {

class WidgetConfigurator
{
public:
	explicit WidgetConfigurator();
	~WidgetConfigurator() = default;
	void setCurrentTool(ToolTypes tool);
	void setColorWidget(ColorPicker *widget);
	void setTextColorWidget(ColorPicker *widget);
	void setWidthWidget(SizePicker *widget);
	void setFillTypeWidget(FillTypePicker *widget);
	void setFontSizeWidget(SizePicker *widget);
	void setFirstNumberWidget(SizePicker *widget);

private:
	ToolTypes mCurrentTool;
	ColorPicker *mColorWidget;
	ColorPicker *mTextColorWidget;
	SizePicker *mWidthWidget;
	FillTypePicker *mFillTypeWidget;
	SizePicker *mFontSizeWidget;
	SizePicker *mFirstNumberWidget;

	void updateWidgets();
	void updateProperties();
	void updateVisibility();
	void setColorWidgetEnabled(bool enabled);
	void setTextColorWidgetEnabled(bool enabled);
	void setWidthWidgetEnabled(bool enabled);
	void setFillWidgetEnabled(bool enabled);
	void setFontSizeWidgetEnabled(bool enabled);
	void setFirstNumberWidgetEnabled(bool enabled);
	void setNoFillAndNoBorderEnabled(bool enabled) const;
};

} // namespace kImageAnnotator

#endif // KIMAGEANNOTATOR_WIDGETCONFIGURATORSWITCHER_H
