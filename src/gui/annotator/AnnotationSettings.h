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

#ifndef KIMAGEANNOTATOR_ANNOTATIONSETTINGS_H
#define KIMAGEANNOTATOR_ANNOTATIONSETTINGS_H

#include <QWidget>

#include "WidgetConfigurator.h"
#include "src/widgets/ToolPicker.h"
#include "src/widgets/ColorPicker.h"
#include "src/widgets/NumberPicker.h"
#include "src/widgets/FillModePicker.h"
#include "src/widgets/StickerPicker.h"
#include "src/widgets/ImageEffectPicker.h"
#include "src/widgets/ZoomIndicator.h"
#include "src/backend/Config.h"
#include "src/annotations/properties/AnnotationTextProperties.h"
#include "src/annotations/properties/AnnotationObfuscateProperties.h"
#include "src/annotations/items/AbstractAnnotationItem.h"
#include "src/annotations/core/AbstractSettingsProvider.h"

namespace kImageAnnotator {

class AnnotationSettings : public QWidget, public AbstractSettingsProvider
{
Q_OBJECT
public:
	explicit AnnotationSettings(Config *config);
	~AnnotationSettings() override;
	void editItem(AbstractAnnotationItem *item) override;
	void activateSelectTool() override;
	Tools toolType() const override;
	QColor toolColor() const override;
	QColor textColor() const override;
	int toolWidth() const override;
	int fontSize() const override;
	FillModes fillType() const override;
	int obfuscationFactor() const override;
	QString sticker() const override;
	ImageEffects effect() const override;
	void updateNumberToolSeed(int numberToolSeed) override;
	void updateZoomLevel(double value) override;
	void reloadConfig();
	void setStickers(const QStringList &stickerPaths, bool keepDefault);
	void setCollapsed(bool isCollapsed);

private:
	QVBoxLayout *mMainLayout;
	QHBoxLayout *mToolLayout;
	ToolPicker *mToolPicker;
	ColorPicker *mColorPicker;
	NumberPicker *mWidthPicker;
	ColorPicker *mTextColorPicker;
	NumberPicker *mFontSizePicker;
	FillModePicker *mFillModePicker;
	NumberPicker *mNumberToolSeedPicker;
	NumberPicker *mObfuscateFactorPicker;
	StickerPicker *mStickerPicker;
	ImageEffectPicker *mEffectPicker;
	ZoomIndicator *mZoomIndicator;
	Config *mConfig;
	WidgetConfigurator mWidgetConfigurator;
	bool mEditExistingItem;

	void initGui();
	void loadFromConfig(Tools tool);

private slots:
	void loadToolTypeFromConfig();
	void toolTypeChanged(Tools toolType);
	void toolColorChanged(const QColor &color);
	void toolTextColorChanged(const QColor &color);
	void toolWidthChanged(int size);
	void toolFontSizeChanged(int size);
	void toolFillTypeChanged(FillModes fill);
	void notifyNumberToolSeedChanged(int newNumberToolSeed);
	void notifyZoomValueChanged(double value);
	void obfuscateFactorChanged(int factor);
	void stickerChanged(const QString &sticker);
	void loadFromItem(const AbstractAnnotationItem *item);
	void effectChanged(ImageEffects effect) override;
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_ANNOTATIONSETTINGS_H
