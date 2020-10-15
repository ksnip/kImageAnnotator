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

#include "AnnotationSettings.h"

namespace kImageAnnotator {

AnnotationSettings::AnnotationSettings(Config *config) :
	mConfig(config),
	mEditExistingItem(false),
	mMainLayout(new QVBoxLayout),
	mToolLayout(new QHBoxLayout),
	mToolPicker(new ToolPicker(this)),
	mColorPicker(new ColorPicker(this)),
	mWidthPicker(new NumberPicker(this)),
	mTextColorPicker(new ColorPicker(this)),
	mFontSizePicker(new NumberPicker(this)),
	mFillTypePicker(new FillModePicker(this)),
	mFirstNumberPicker(new NumberPicker(this)),
	mObfuscateFactorPicker(new NumberPicker(this)),
	mStickerPicker(new StickerPicker(this)),
	mEffectPicker(new EffectPicker(this))
{
	initGui();
	loadToolTypeFromConfig();
}

AnnotationSettings::~AnnotationSettings()
{
	delete mToolPicker;
	delete mColorPicker;
	delete mWidthPicker;
	delete mTextColorPicker;
	delete mFontSizePicker;
	delete mFillTypePicker;
	delete mEffectPicker;
	delete mFirstNumberPicker;
	delete mObfuscateFactorPicker;
	delete mStickerPicker;
	delete mToolLayout;
}

void AnnotationSettings::editItem(AbstractAnnotationItem *item)
{
	activateSelectTool();
	loadFromItem(item);
	mEditExistingItem = true;
}

void AnnotationSettings::loadFromItem(const AbstractAnnotationItem *item)
{
	auto properties = item->properties();
	mWidgetConfigurator.setCurrentTool(item->toolType());
	mColorPicker->setColor(properties->color());
	mTextColorPicker->setColor(properties->textColor());
	mWidthPicker->setNumber(properties->width());
	mFillTypePicker->setFillType(properties->fillType());
	auto textProperties = properties.dynamicCast<AnnotationTextProperties>();
	if(textProperties != nullptr) {
		mFontSizePicker->setNumber(textProperties->font().pointSize());
	}
	auto obfuscateProperties = properties.dynamicCast<AnnotationObfuscateProperties>();
	if(obfuscateProperties != nullptr) {
		mObfuscateFactorPicker->setNumber(obfuscateProperties->factor());
	}
}

void AnnotationSettings::activateSelectTool()
{
	mEditExistingItem = false;
	mWidgetConfigurator.setCurrentTool(Tools::Select);
	mToolPicker->setTool(Tools::Select);
}

Tools AnnotationSettings::toolType() const
{
	return mToolPicker->tool();
}

void AnnotationSettings::initGui()
{
	mColorPicker->setIcon(IconLoader::load(QLatin1Literal("color.svg")));
	mColorPicker->setToolTip(tr("Color"));

	mTextColorPicker->setIcon(IconLoader::load(QLatin1Literal("textColor.svg")));
	mTextColorPicker->setToolTip(tr("Text Color"));

	mWidthPicker->setIcon(IconLoader::load(QLatin1Literal("width.svg")));
	mWidthPicker->setToolTip(tr("Width"));

	mFontSizePicker->setIcon(IconLoader::load(QLatin1Literal("fontSize.svg")));
	mFontSizePicker->setToolTip(tr("Font Size"));
	mFontSizePicker->setRange(10, 40);

	mFirstNumberPicker->setIcon(IconLoader::load(QLatin1Literal("number.svg")));
	mFirstNumberPicker->setToolTip(tr("Starting Number"));
	mFirstNumberPicker->setRange(1, 100);

	mObfuscateFactorPicker->setIcon(IconLoader::load(QLatin1Literal("obfuscateFactor.svg")));
	mObfuscateFactorPicker->setToolTip(tr("Obfuscation Factor"));
	mObfuscateFactorPicker->setRange(1, 20);


	mToolLayout->addWidget(mToolPicker);
	mMainLayout->addLayout(mToolLayout);
	mMainLayout->addSpacing(10);
	mMainLayout->addWidget(mEffectPicker);
	mMainLayout->addSpacing(10);
	mMainLayout->addWidget(mColorPicker);
	mMainLayout->addWidget(mWidthPicker);
	mMainLayout->addWidget(mTextColorPicker);
	mMainLayout->addWidget(mFontSizePicker);
	mMainLayout->addWidget(mFillTypePicker);
	mMainLayout->addWidget(mFirstNumberPicker);
	mMainLayout->addWidget(mObfuscateFactorPicker);
	mMainLayout->addWidget(mStickerPicker);
	mMainLayout->setAlignment(Qt::AlignTop | Qt::AlignCenter);
	mMainLayout->setContentsMargins(0, 0, 0, 0);

	mWidgetConfigurator.setColorWidget(mColorPicker);
	mWidgetConfigurator.setTextColorWidget(mTextColorPicker);
	mWidgetConfigurator.setWidthWidget(mWidthPicker);
	mWidgetConfigurator.setFillTypeWidget(mFillTypePicker);
	mWidgetConfigurator.setFontSizeWidget(mFontSizePicker);
	mWidgetConfigurator.setFirstNumberWidget(mFirstNumberPicker);
	mWidgetConfigurator.setObfuscateFactorWidget(mObfuscateFactorPicker);
	mWidgetConfigurator.setStickerWidget(mStickerPicker);

	setLayout(mMainLayout);

	setFocusPolicy(Qt::ClickFocus);

	connect(mToolPicker, &ToolPicker::toolSelected, this, &AnnotationSettings::toolTypeChanged);
	connect(mColorPicker, &ColorPicker::colorSelected, this, &AnnotationSettings::toolColorChanged);
	connect(mWidthPicker, &NumberPicker::numberSelected, this, &AnnotationSettings::toolWidthChanged);
	connect(mTextColorPicker, &ColorPicker::colorSelected, this, &AnnotationSettings::toolTextColorChanged);
	connect(mFontSizePicker, &NumberPicker::numberSelected, this, &AnnotationSettings::toolFontSizeChanged);
	connect(mFillTypePicker, &FillModePicker::fillSelected, this, &AnnotationSettings::toolFillTypeChanged);
	connect(mFirstNumberPicker, &NumberPicker::numberSelected, this, &AnnotationSettings::saveFirstBadgeNumber);
	connect(mObfuscateFactorPicker, &NumberPicker::numberSelected, this, &AnnotationSettings::obfuscateFactorChanged);
	connect(mStickerPicker, &StickerPicker::stickerSelected, this, &AnnotationSettings::stickerChanged);
	connect(mEffectPicker, &EffectPicker::effectSelected, this, &AnnotationSettings::effectChanged);
}

void AnnotationSettings::loadToolTypeFromConfig()
{
	mToolPicker->setTool(mConfig->selectedTool());
}

void AnnotationSettings::loadFromConfig(Tools tool)
{
	mWidgetConfigurator.setCurrentTool(tool);
	mColorPicker->setColor(mConfig->toolColor(tool));
	mTextColorPicker->setColor(mConfig->toolTextColor(tool));
	mWidthPicker->setNumber(mConfig->toolWidth(tool));
	mFillTypePicker->setFillType(mConfig->toolFillType(tool));
	mFontSizePicker->setNumber(mConfig->toolFontSize(tool));
	mObfuscateFactorPicker->setNumber(mConfig->obfuscationFactor(tool));
}

void AnnotationSettings::toolTypeChanged(Tools toolType)
{
	mEditExistingItem = false;
	mConfig->setSelectedToolType(toolType);
	if(!mEditExistingItem) {
		loadFromConfig(toolType);
	}
	toolChanged(toolType);
}

void AnnotationSettings::toolColorChanged(const QColor &color)
{
	if(mEditExistingItem) {
		itemSettingChanged();
	} else {
		mConfig->setToolColor(color, mToolPicker->tool());
	}
}

void AnnotationSettings::toolTextColorChanged(const QColor &color)
{
	if(mEditExistingItem) {
		itemSettingChanged();
	} else {
		mConfig->setToolTextColor(color, mToolPicker->tool());
	}
}

void AnnotationSettings::toolWidthChanged(int size)
{
	if(mEditExistingItem) {
		itemSettingChanged();
	} else {
		mConfig->setToolWidth(size, mToolPicker->tool());
	}
}

void AnnotationSettings::toolFillTypeChanged(FillModes fill)
{
	if(mEditExistingItem) {
		itemSettingChanged();
	} else {
		mConfig->setToolFillType(fill, mToolPicker->tool());
	}
}

void AnnotationSettings::toolFontSizeChanged(int size)
{
	if(mEditExistingItem) {
		itemSettingChanged();
	} else {
		mConfig->setToolFontSize(size, mToolPicker->tool());
	}
}

void AnnotationSettings::saveFirstBadgeNumber(int number)
{
	firstBadgeNumberChanged(number);
}

void AnnotationSettings::obfuscateFactorChanged(int factor)
{
	if(mEditExistingItem) {
		itemSettingChanged();
	} else {
		mConfig->setObfuscationFactor(factor, mToolPicker->tool());
	}
}

void AnnotationSettings::stickerChanged(const QString &sticker)
{
	if(mEditExistingItem) {
		itemSettingChanged();
	}
}

QColor AnnotationSettings::toolColor() const
{
	return mColorPicker->color();
}

QColor AnnotationSettings::textColor() const
{
	return mTextColorPicker->color();
}

int AnnotationSettings::toolWidth() const
{
	return mWidthPicker->number();
}

FillModes AnnotationSettings::fillType() const
{
	return mFillTypePicker->fillType();
}

int AnnotationSettings::fontSize() const
{
	return mFontSizePicker->number();
}

int AnnotationSettings::obfuscationFactor() const
{
	return mObfuscateFactorPicker->number();
}

QString AnnotationSettings::sticker() const
{
	return mStickerPicker->sticker();
}

void AnnotationSettings::updateFirstBadgeNumber(int number)
{
	mFirstNumberPicker->setNumber(number);
}

void AnnotationSettings::reloadConfig()
{
	loadToolTypeFromConfig();
}

void AnnotationSettings::setStickers(const QStringList &stickerPaths, bool keepDefault)
{
	mStickerPicker->setStickers(stickerPaths, keepDefault);
}

void AnnotationSettings::effectChanged(Effects effect)
{
	AbstractSettingsProvider::effectChanged(effect);
}

} // namespace kImageAnnotator
