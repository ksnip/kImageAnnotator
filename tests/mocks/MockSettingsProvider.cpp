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

ToolTypes MockSettingsProvider::toolType() const
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

int MockSettingsProvider::fontSize() const
{
	return mFontSize;
}

FillTypes MockSettingsProvider::fillType() const
{
	return mFillType;
}

int MockSettingsProvider::obfuscationFactor() const
{
	return mBlurRadius;
}

void MockSettingsProvider::setToolType(ToolTypes toolType)
{
	mToolType = toolType;
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

void MockSettingsProvider::setFontSize(int fontSize)
{
	mFontSize = fontSize;
}

void MockSettingsProvider::setFillType(FillTypes fillType)
{
	mFillType = fillType;
}

void MockSettingsProvider::setBlurRadius(int blurRadius)
{
	mBlurRadius = blurRadius;
}

QString MockSettingsProvider::sticker() const
{
	return mStickerPath;
}

void MockSettingsProvider::setSticker(const QString &stickerPath)
{
	mStickerPath =  stickerPath;
}

void MockSettingsProvider::updateFirstBadgeNumber(int number)
{

}
