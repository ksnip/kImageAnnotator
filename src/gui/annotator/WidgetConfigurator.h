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

#include "src/common/enum/Tools.h"
#include "src/widgets/ColorPicker.h"
#include "src/widgets/FillModePicker.h"
#include "src/widgets/ToolPicker.h"
#include "src/widgets/NumberPicker.h"
#include "src/widgets/StickerPicker.h"

namespace kImageAnnotator {

class WidgetConfigurator
{
public:
	explicit WidgetConfigurator();
	~WidgetConfigurator() = default;
	void setCurrentTool(Tools tool);
	void setColorWidget(ColorPicker *widget);
	void setTextColorWidget(ColorPicker *widget);
	void setWidthWidget(NumberPicker *widget);
	void setFillTypeWidget(FillModePicker *widget);
	void setFontSizeWidget(NumberPicker *widget);
	void setFirstNumberWidget(NumberPicker *widget);
	void setObfuscateFactorWidget(NumberPicker *widget);
	void setStickerWidget(StickerPicker *widget);

private:
	Tools mCurrentTool;
	ColorPicker *mColorWidget;
	ColorPicker *mTextColorWidget;
	NumberPicker *mWidthWidget;
	FillModePicker *mFillModeWidget;
	NumberPicker *mFontSizeWidget;
	NumberPicker *mFirstNumberWidget;
	NumberPicker *mObfuscateFactorWidget;
	StickerPicker *mStickerWidget;

	void updateWidgets() const;
	void updateProperties() const;
	void updateVisibility() const;
	void setColorWidgetVisible(bool enabled) const;
	void setTextColorWidgetVisible(bool enabled) const;
	void setWidthWidgetVisible(bool enabled) const;
	void setFillWidgetVisible(bool enabled) const;
	void setFontSizeWidgetVisible(bool enabled) const;
	void setFirstNumberWidgetVisible(bool enabled) const;
	void setNoFillAndNoBorderVisible(bool enabled) const;
	void setObfuscateFactorWidgetVisible(bool enabled) const;
	void setStickerWidgetVisible(bool enabled) const;
	void setWidthRange(int min, int max) const;
};

} // namespace kImageAnnotator

#endif // KIMAGEANNOTATOR_WIDGETCONFIGURATORSWITCHER_H
