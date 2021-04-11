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
	mFontSizePicker(new NumberPicker(this)),
	mFillModePicker(new FillModePicker(this)),
	mNumberToolSeedPicker(new NumberPicker(this)),
	mObfuscateFactorPicker(new NumberPicker(this)),
	mStickerPicker(new StickerPicker(this)),
	mShadowToggleButton(new ToggleButton(this))
{
	initGui();
}

AnnotationItemSettings::~AnnotationItemSettings()
{
	delete mColorPicker;
	delete mWidthPicker;
	delete mTextColorPicker;
	delete mFontSizePicker;
	delete mFillModePicker;
	delete mNumberToolSeedPicker;
	delete mObfuscateFactorPicker;
	delete mStickerPicker;
	delete mShadowToggleButton;
	delete mMainLayout;
}

void AnnotationItemSettings::initGui()
{
	mColorPicker->setIcon(IconLoader::load(QStringLiteral("color.svg")));
	mColorPicker->setToolTip(tr("Color"));

	mTextColorPicker->setIcon(IconLoader::load(QStringLiteral("textColor.svg")));
	mTextColorPicker->setToolTip(tr("Text Color"));

	mWidthPicker->setIcon(IconLoader::load(QStringLiteral("width.svg")));
	mWidthPicker->setToolTip(tr("Width"));

	mFontSizePicker->setIcon(IconLoader::load(QStringLiteral("fontSize.svg")));
	mFontSizePicker->setToolTip(tr("Font Size"));
	mFontSizePicker->setRange(10, 40);

	mNumberToolSeedPicker->setIcon(IconLoader::load(QStringLiteral("number.svg")));
	mNumberToolSeedPicker->setToolTip(tr("Number Seed"));
	mNumberToolSeedPicker->setRange(1, 100);

	mObfuscateFactorPicker->setIcon(IconLoader::load(QStringLiteral("obfuscateFactor.svg")));
	mObfuscateFactorPicker->setToolTip(tr("Obfuscation Factor"));

	mShadowToggleButton->setIcon(IconLoader::load(QStringLiteral("dropShadowImageEffect.svg")));
	mShadowToggleButton->setToolTip(tr("Item Shadow"));

	mMainLayout->addWidget(mColorPicker);
	mMainLayout->addWidget(mWidthPicker);
	mMainLayout->addWidget(mTextColorPicker);
	mMainLayout->addWidget(mFontSizePicker);
	mMainLayout->addWidget(mFillModePicker);
	mMainLayout->addWidget(mNumberToolSeedPicker);
	mMainLayout->addWidget(mObfuscateFactorPicker);
	mMainLayout->addWidget(mStickerPicker);
	mMainLayout->addWidget(mShadowToggleButton);

	mMainLayout->setContentsMargins(0, 0, 0, 0);

	mWidgetConfigurator.setColorWidget(mColorPicker);
	mWidgetConfigurator.setTextColorWidget(mTextColorPicker);
	mWidgetConfigurator.setWidthWidget(mWidthPicker);
	mWidgetConfigurator.setFillTypeWidget(mFillModePicker);
	mWidgetConfigurator.setFontSizeWidget(mFontSizePicker);
	mWidgetConfigurator.setFirstNumberWidget(mNumberToolSeedPicker);
	mWidgetConfigurator.setObfuscateFactorWidget(mObfuscateFactorPicker);
	mWidgetConfigurator.setStickerWidget(mStickerPicker);
	mWidgetConfigurator.setShadowToggleWidget(mShadowToggleButton);

	setLayout(mMainLayout);

	setFocusPolicy(Qt::ClickFocus);

	connect(mColorPicker, &ColorPicker::colorSelected, this, &AnnotationItemSettings::toolColorChanged);
	connect(mWidthPicker, &NumberPicker::numberSelected, this, &AnnotationItemSettings::toolWidthChanged);
	connect(mTextColorPicker, &ColorPicker::colorSelected, this, &AnnotationItemSettings::toolTextColorChanged);
	connect(mFontSizePicker, &NumberPicker::numberSelected, this, &AnnotationItemSettings::toolFontSizeChanged);
	connect(mFillModePicker, &FillModePicker::fillSelected, this, &AnnotationItemSettings::toolFillTypeChanged);
	connect(mNumberToolSeedPicker, &NumberPicker::numberSelected, this, &AnnotationItemSettings::notifyNumberToolSeedChanged);
	connect(mObfuscateFactorPicker, &NumberPicker::numberSelected, this, &AnnotationItemSettings::obfuscateFactorChanged);
	connect(mStickerPicker, &StickerPicker::stickerSelected, this, &AnnotationItemSettings::stickerChanged);
	connect(mShadowToggleButton, &ToggleButton::toggled, this, &AnnotationItemSettings::shadowEnabledChanged);
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

int AnnotationItemSettings::fontSize() const
{
	return mFontSizePicker->number();
}

void AnnotationItemSettings::setFontSize(int size)
{
	mFontSizePicker->setNumber(size);
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
	return mShadowToggleButton->isChecked();
}

void AnnotationItemSettings::setShadowEnabled(bool enabled)
{
	mShadowToggleButton->setChecked(enabled);
}

void AnnotationItemSettings::updateNumberToolSeed(int numberToolSeed)
{
	mNumberToolSeedPicker->setNumber(numberToolSeed);
}

void AnnotationItemSettings::setOrientation(Qt::Orientation orientation)
{
	if(orientation == Qt::Horizontal) {
		mMainLayout->setDirection(QBoxLayout::LeftToRight);
		mMainLayout->setAlignment(Qt::AlignLeft | Qt::AlignCenter);
	} else {
		mMainLayout->setDirection(QBoxLayout::TopToBottom);
		mMainLayout->setAlignment(Qt::AlignTop | Qt::AlignCenter);
	}
	adjustSize();
}

QString AnnotationItemSettings::name() const
{
	return tr("Item Settings");
}

} // namespace kImageAnnotator
