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

#ifndef KIMAGEANNOTATOR_MOCKSETTINGSPROVIDER_H
#define KIMAGEANNOTATOR_MOCKSETTINGSPROVIDER_H

#include "src/annotations/core/AbstractSettingsProvider.h"

using kImageAnnotator::AbstractSettingsProvider;
using kImageAnnotator::AbstractAnnotationItem;
using kImageAnnotator::Tools;
using kImageAnnotator::FillModes;
using kImageAnnotator::ImageEffects;

class MockSettingsProvider : public AbstractSettingsProvider
{
public:
	void editItem(AbstractAnnotationItem *item) override;
	void activateSelectTool() override;
	Tools toolType() const override;
	void setToolType(Tools tool);
	QColor toolColor() const override;
	void setToolColor(const QColor &toolColor);
	QColor textColor() const override;
	void setTextColor(const QColor &textColor);
	int toolWidth() const override;
	void setToolWidth(int toolWidth);
	QFont font() const override;
	void setFont(const QFont &font);
	FillModes fillType() const override;
	void setFillType(FillModes fillMode);
	int obfuscationFactor() const override;
	void setBlurRadius(int blurRadius);
	QString sticker() const override;
	void setSticker(const QString &stickerPath);
	ImageEffects effect() const override;
	bool shadowEnabled() const override;
	void setShadowEnabled(bool enabled);

	void updateNumberToolSeed(int numberToolSeed) override;
	void updateZoomLevel(double value) override;

private:
	Tools mToolType;
	QColor mToolColor;
	QColor mTextColor;
	int mToolWidth;
	QFont mFont;
	FillModes mFillType;
	int mBlurRadius;
	QString mStickerPath;
	double mZoomLevel;
	bool mShadowEnabled;
};

#endif //KIMAGEANNOTATOR_MOCKSETTINGSPROVIDER_H
