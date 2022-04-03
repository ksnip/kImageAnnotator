/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
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

#include "MockSettingsProvider.h"

void MockSettingsProvider::editItem(AbstractAnnotationItem *item)
{

}

void MockSettingsProvider::activateSelectTool()
{

}

Tools MockSettingsProvider::toolType() const
{
	return mToolType;
}

QColor MockSettingsProvider::toolColor() const
{
	return mToolColor;
}

QColor MockSettingsProvider::textColor() const
{
	return mTextColor;
}

int MockSettingsProvider::toolWidth() const
{
	return mToolWidth;
}

QFont MockSettingsProvider::font() const
{
	return mFont;
}

FillModes MockSettingsProvider::fillType() const
{
	return mFillType;
}

int MockSettingsProvider::obfuscationFactor() const
{
	return mBlurRadius;
}

void MockSettingsProvider::setToolType(Tools tool)
{
	mToolType = tool;
}

void MockSettingsProvider::setToolColor(const QColor &toolColor)
{
	mToolColor = toolColor;
}

void MockSettingsProvider::setTextColor(const QColor &textColor)
{
	mTextColor = textColor;
}

void MockSettingsProvider::setToolWidth(int toolWidth)
{
	mToolWidth = toolWidth;
}

void MockSettingsProvider::setFont(const QFont &font)
{
	mFont = font;
}

void MockSettingsProvider::setFillType(FillModes fillMode)
{
	mFillType = fillMode;
}

void MockSettingsProvider::setBlurRadius(int blurRadius)
{
	mBlurRadius = blurRadius;
}

QString MockSettingsProvider::sticker() const
{
	return mStickerPath;
}

ImageEffects MockSettingsProvider::effect() const
{
	return ImageEffects::NoEffect;
}

qreal MockSettingsProvider::scaling() const
{
	return 1.0;
}

qreal MockSettingsProvider::opacity() const
{
	return 1.0;
}

bool MockSettingsProvider::shadowEnabled() const
{
	return mShadowEnabled;
}

void MockSettingsProvider::setSticker(const QString &stickerPath)
{
	mStickerPath =  stickerPath;
}

void MockSettingsProvider::updateZoomLevel(double value)
{
    mZoomLevel = value;
}

void MockSettingsProvider::updateNumberToolSeed(int numberToolSeed)
{

}

void MockSettingsProvider::setShadowEnabled(bool enabled)
{
	mShadowEnabled = enabled;
}
