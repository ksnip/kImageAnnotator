/*
 * Copyright (C) 2019 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KIMAGEANNOTATOR_ANNOTATIONITEMSETTINGS_H
#define KIMAGEANNOTATOR_ANNOTATIONITEMSETTINGS_H

#include "ItemSettingsWidgetConfigurator.h"
#include "src/backend/Config.h"
#include "src/widgets/settingsPicker/ColorPicker.h"
#include "src/widgets/settingsPicker/NumberPicker.h"
#include "src/widgets/settingsPicker/FillModePicker.h"
#include "src/widgets/settingsPicker/StickerPicker.h"
#include "src/widgets/settingsPicker/BoolPicker.h"
#include "src/widgets/settingsPicker/FontPicker.h"
#include "src/widgets/misc/AttachedSeparator.h"
#include "src/gui/annotator/docks/AbstractAnnotationDockWidgetContent.h"
#include "src/annotations/properties/AnnotationTextProperties.h"
#include "src/annotations/properties/AnnotationObfuscateProperties.h"
#include "src/annotations/items/AbstractAnnotationItem.h"

namespace kImageAnnotator {

class AnnotationItemSettings : public AbstractAnnotationDockWidgetContent
{
Q_OBJECT
public:
	explicit AnnotationItemSettings();
	~AnnotationItemSettings() override;
	void setUpForTool(Tools tool);
	QColor toolColor() const;
	void setToolColor(const QColor &color);
	QColor textColor() const;
	void setTextColor(const QColor &color);
	int toolWidth() const;
	void setToolWidth(int width);
	FillModes fillMode() const;
	void setFillMode(FillModes mode);
	int obfuscationFactor() const;
	void setObfuscationFactor(int factor);
	QString sticker() const;
	void setStickers(const QStringList &stickerPaths, bool keepDefault);
	bool shadowEnabled() const;
	void setShadowEnabled(bool enabled);
	void updateNumberToolSeed(int numberToolSeed);
	QFont font() const;
	void setFont(const QFont &font);
	QString name() const override;
	void setOrientation(Qt::Orientation orientation) override;

signals:
	void toolColorChanged(const QColor &color);
	void toolTextColorChanged(const QColor &color);
	void toolWidthChanged(int width);
	void toolFillTypeChanged(FillModes fill);
	void notifyNumberToolSeedChanged(int newNumberToolSeed);
	void obfuscateFactorChanged(int factor);
	void stickerChanged(const QString &sticker);
	void shadowEnabledChanged(bool enabled);
	void fontChanged(const QFont &font);

private:
	QBoxLayout *mMainLayout;
	ColorPicker *mColorPicker;
	NumberPicker *mWidthPicker;
	ColorPicker *mTextColorPicker;
	FillModePicker *mFillModePicker;
	NumberPicker *mNumberToolSeedPicker;
	NumberPicker *mObfuscateFactorPicker;
	StickerPicker *mStickerPicker;
	BoolPicker *mShadowPicker;
	FontPicker *mFontPicker;
	ItemSettingsWidgetConfigurator mWidgetConfigurator;
	QList<AttachedSeparator*> mSeparators;

	void initGui();
	void insertPickerWidget(SettingsPickerWidget *pickerWidget);
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_ANNOTATIONITEMSETTINGS_H
