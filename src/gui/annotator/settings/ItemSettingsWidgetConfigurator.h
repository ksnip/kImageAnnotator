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
#include "src/widgets/settingsPicker/ColorPicker.h"
#include "src/widgets/settingsPicker/FillModePicker.h"
#include "src/widgets/ToolPicker.h"
#include "src/widgets/settingsPicker/NumberPicker.h"
#include "src/widgets/settingsPicker/StickerPicker.h"
#include "src/widgets/settingsPicker/BoolPicker.h"
#include "src/widgets/settingsPicker/FontPicker.h"

namespace kImageAnnotator {

class ItemSettingsWidgetConfigurator
{
public:
	explicit ItemSettingsWidgetConfigurator();
	~ItemSettingsWidgetConfigurator() = default;
	void setCurrentTool(Tools tool);
	void setColorWidget(ColorPicker *widget);
	void setTextColorWidget(ColorPicker *widget);
	void setWidthWidget(NumberPicker *widget);
	void setFillTypeWidget(FillModePicker *widget);
	void setFirstNumberWidget(NumberPicker *widget);
	void setObfuscateFactorWidget(NumberPicker *widget);
	void setStickerWidget(StickerPicker *widget);
	void setShadowWidget(BoolPicker *widget);
	void setFontWidget(FontPicker *widget);
	void setOpacityWidget(NumberPicker *widget);

private:
	Tools mCurrentTool;
	ColorPicker *mColorWidget;
	ColorPicker *mTextColorWidget;
	NumberPicker *mWidthWidget;
	FillModePicker *mFillModeWidget;
	NumberPicker *mFirstNumberWidget;
	NumberPicker *mObfuscateFactorWidget;
	StickerPicker *mStickerWidget;
	BoolPicker *mShadowPicker;
	FontPicker *mFontPicker;
	NumberPicker *mOpacityPicker;

	void updateWidgets() const;
	void updateProperties() const;
	void updateVisibility() const;
	void setColorWidgetVisible(bool enabled) const;
	void setTextColorWidgetVisible(bool enabled) const;
	void setWidthWidgetVisible(bool enabled) const;
	void setFillWidgetVisible(bool enabled) const;
	void setFirstNumberWidgetVisible(bool enabled) const;
	void setNoFillAndNoBorderVisible(bool enabled) const;
	void setObfuscateFactorWidgetVisible(bool enabled) const;
	void setStickerWidgetVisible(bool enabled) const;
	void setShadowWidgetVisible(bool enabled) const;
	void setFontWidgetVisible(bool enabled) const;
	void setOpacityWidgetVisible(bool enabled) const;
	void setWidthRange(int min, int max) const;
};

} // namespace kImageAnnotator

#endif // KIMAGEANNOTATOR_WIDGETCONFIGURATORSWITCHER_H
