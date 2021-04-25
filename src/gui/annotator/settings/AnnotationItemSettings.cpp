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

#include "AnnotationItemSettings.h"

namespace kImageAnnotator {

AnnotationItemSettings::AnnotationItemSettings() :
	mMainLayout(new QBoxLayout(QBoxLayout::LeftToRight)),
	mColorPicker(new ColorPicker(this)),
	mWidthPicker(new NumberPicker(this)),
	mTextColorPicker(new ColorPicker(this)),
	mFillModePicker(new FillModePicker(this)),
	mNumberToolSeedPicker(new NumberPicker(this)),
	mObfuscateFactorPicker(new NumberPicker(this)),
	mStickerPicker(new StickerPicker(this)),
	mShadowPicker(new BoolPicker(this)),
	mFontPicker(new FontPicker(this))
{
	initGui();
}

AnnotationItemSettings::~AnnotationItemSettings()
{
	delete mColorPicker;
	delete mWidthPicker;
	delete mTextColorPicker;
	delete mFillModePicker;
	delete mNumberToolSeedPicker;
	delete mObfuscateFactorPicker;
	delete mStickerPicker;
	delete mShadowPicker;
	delete mFontPicker;
	delete mMainLayout;
	qDeleteAll(mSeparators);
}

void AnnotationItemSettings::initGui()
{
	mColorPicker->setIcon(IconLoader::load(QLatin1String("color.svg")));
	mColorPicker->setToolTip(tr("Color"));

	mTextColorPicker->setIcon(IconLoader::load(QLatin1String("textColor.svg")));
	mTextColorPicker->setToolTip(tr("Text Color"));

	mWidthPicker->setIcon(IconLoader::load(QLatin1String("width.svg")));
	mWidthPicker->setToolTip(tr("Width"));

	mNumberToolSeedPicker->setIcon(IconLoader::load(QLatin1String("number.svg")));
	mNumberToolSeedPicker->setToolTip(tr("Number Seed"));
	mNumberToolSeedPicker->setRange(1, 100);

	mObfuscateFactorPicker->setIcon(IconLoader::load(QLatin1String("obfuscateFactor.svg")));
	mObfuscateFactorPicker->setToolTip(tr("Obfuscation Factor"));

	mShadowPicker->setIcon(IconLoader::load(QLatin1String("dropShadow.svg")));
	mShadowPicker->setToolTip(tr("Item Shadow"));

	insertPickerWidget(mColorPicker);
	insertPickerWidget(mWidthPicker);
	insertPickerWidget(mFillModePicker);
	insertPickerWidget(mTextColorPicker);
	insertPickerWidget(mFontPicker);
	insertPickerWidget(mNumberToolSeedPicker);
	insertPickerWidget(mObfuscateFactorPicker);
	insertPickerWidget(mStickerPicker);
	insertPickerWidget(mShadowPicker);

	mWidgetConfigurator.setColorWidget(mColorPicker);
	mWidgetConfigurator.setTextColorWidget(mTextColorPicker);
	mWidgetConfigurator.setWidthWidget(mWidthPicker);
	mWidgetConfigurator.setFillTypeWidget(mFillModePicker);
	mWidgetConfigurator.setFirstNumberWidget(mNumberToolSeedPicker);
	mWidgetConfigurator.setObfuscateFactorWidget(mObfuscateFactorPicker);
	mWidgetConfigurator.setStickerWidget(mStickerPicker);
	mWidgetConfigurator.setShadowWidget(mShadowPicker);
	mWidgetConfigurator.setFontWidget(mFontPicker);

	mMainLayout->setContentsMargins(3, 0, 3, 0);

	setLayout(mMainLayout);

	setFocusPolicy(Qt::ClickFocus);

	connect(mColorPicker, &ColorPicker::colorSelected, this, &AnnotationItemSettings::toolColorChanged);
	connect(mWidthPicker, &NumberPicker::numberSelected, this, &AnnotationItemSettings::toolWidthChanged);
	connect(mTextColorPicker, &ColorPicker::colorSelected, this, &AnnotationItemSettings::toolTextColorChanged);
	connect(mFillModePicker, &FillModePicker::fillSelected, this, &AnnotationItemSettings::toolFillTypeChanged);
	connect(mNumberToolSeedPicker, &NumberPicker::numberSelected, this, &AnnotationItemSettings::notifyNumberToolSeedChanged);
	connect(mObfuscateFactorPicker, &NumberPicker::numberSelected, this, &AnnotationItemSettings::obfuscateFactorChanged);
	connect(mStickerPicker, &StickerPicker::stickerSelected, this, &AnnotationItemSettings::stickerChanged);
	connect(mShadowPicker, &BoolPicker::enabledStateChanged, this, &AnnotationItemSettings::shadowEnabledChanged);
	connect(mFontPicker, &FontPicker::fontChanged, this, &AnnotationItemSettings::fontChanged);
}

void AnnotationItemSettings::insertPickerWidget(SettingsPickerWidget *pickerWidget)
{
	auto separator = new AttachedSeparator(pickerWidget);
	mMainLayout->addWidget(pickerWidget);
	mMainLayout->addWidget(separator);

	addExpandingWidget(pickerWidget);
	mSeparators.append(separator);
}

void AnnotationItemSettings::setUpForTool(Tools tool)
{
	mWidgetConfigurator.setCurrentTool(tool);
}

QColor AnnotationItemSettings::toolColor() const
{
	return mColorPicker->color();
}

void AnnotationItemSettings::setToolColor(const QColor &color)
{
	mColorPicker->setColor(color);
}

QColor AnnotationItemSettings::textColor() const
{
	return mTextColorPicker->color();
}

void AnnotationItemSettings::setTextColor(const QColor &color)
{
	mTextColorPicker->setColor(color);
}

int AnnotationItemSettings::toolWidth() const
{
	return mWidthPicker->number();
}

void AnnotationItemSettings::setToolWidth(int width)
{
	mWidthPicker->setNumber(width);
}

FillModes AnnotationItemSettings::fillMode() const
{
	return mFillModePicker->fillType();
}

void AnnotationItemSettings::setFillMode(FillModes mode)
{
	mFillModePicker->setFillType(mode);
}

int AnnotationItemSettings::obfuscationFactor() const
{
	return mObfuscateFactorPicker->number();
}

void AnnotationItemSettings::setObfuscationFactor(int factor)
{
	mObfuscateFactorPicker->setNumber(factor);
}

QString AnnotationItemSettings::sticker() const
{
	return mStickerPicker->sticker();
}

void AnnotationItemSettings::setStickers(const QStringList &stickerPaths, bool keepDefault)
{
	mStickerPicker->setStickers(stickerPaths, keepDefault);
}

bool AnnotationItemSettings::shadowEnabled() const
{
	return mShadowPicker->enabledState();
}

void AnnotationItemSettings::setShadowEnabled(bool enabled)
{
	mShadowPicker->setEnabledState(enabled);
}

void AnnotationItemSettings::updateNumberToolSeed(int numberToolSeed)
{
	mNumberToolSeedPicker->setNumber(numberToolSeed);
}

QFont AnnotationItemSettings::font() const
{
	return mFontPicker->currentFont();
}

void AnnotationItemSettings::setFont(const QFont &font)
{
	mFontPicker->setCurrentFont(font);
}

QString AnnotationItemSettings::name() const
{
	return tr("Item Settings");
}

void AnnotationItemSettings::setOrientation(Qt::Orientation orientation)
{
	for(auto separator : mSeparators) {
		separator->setEnabled(orientation == Qt::Horizontal);
	}

	AbstractAnnotationDockWidgetContent::setOrientation(orientation);
}

} // namespace kImageAnnotator
