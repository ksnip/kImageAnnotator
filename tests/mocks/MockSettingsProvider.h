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
using kImageAnnotator::ToolTypes;
using kImageAnnotator::FillTypes;

class MockSettingsProvider : public AbstractSettingsProvider
{
public:
	void editItem(AbstractAnnotationItem *item) override;
	void activateSelectTool() override;
	ToolTypes toolType() const override;
	void setToolType(ToolTypes toolType);
	QColor toolColor() const override;
	void setToolColor(const QColor &toolColor);
	QColor textColor() const override;
	void setTextColor(const QColor &textColor);
	int toolWidth() const override;
	void setToolWidth(int toolWidth);
	int fontSize() const override;
	void setFontSize(int fontSize);
	FillTypes fillType() const override;
	void setFillType(FillTypes fillType);
	int blurRadius() const override;
	void setBlurRadius(int blurRadius);

private:
	ToolTypes mToolType;
	QColor mToolColor;
	QColor mTextColor;
	int mToolWidth;
	int mFontSize;
	FillTypes mFillType;
	int mBlurRadius;
};

#endif //KIMAGEANNOTATOR_MOCKSETTINGSPROVIDER_H
