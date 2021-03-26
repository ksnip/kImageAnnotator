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

#include "ScaleSizeHandler.h"

namespace kImageAnnotator {

ScaleSizeHandler::ScaleSizeHandler() :
	mKeepAspectRatio(true)
{

}

void ScaleSizeHandler::setSize(QSize size)
{
	mSize = size;
}

QSize ScaleSizeHandler::size() const
{
	return mSize;
}

void ScaleSizeHandler::setAspectRatio(bool keepAspectRatio)
{
	mKeepAspectRatio = keepAspectRatio;
}

void ScaleSizeHandler::setWidthPixel(int width)
{
	auto percent = calculatePercent(width, mSize.width());

	emit widthPercentChanged(percent * 100);

	if (mKeepAspectRatio) {
		setHeight(percent);
	}
}

void ScaleSizeHandler::setWidthPercent(float width)
{
	auto percent = calculatePercent(width, 100);

	emit widthPixelChanged(percent * mSize.width());

	if (mKeepAspectRatio) {
		setHeight(percent);
	}
}

void ScaleSizeHandler::setHeightPixel(int height)
{
	auto percent = calculatePercent(height, mSize.height());

	emit heightPercentChanged(percent * 100);

	if (mKeepAspectRatio) {
		setWidth(percent);
	}
}

void ScaleSizeHandler::setHeightPercent(float height)
{
	auto percent = calculatePercent(height, 100);

	emit heightPixelChanged(percent * mSize.height());

	if (mKeepAspectRatio) {
		setWidth(percent);
	}
}

float ScaleSizeHandler::calculatePercent(int newValue, int baseValue) const
{
	return (float) newValue / (float) baseValue;
}

void ScaleSizeHandler::setHeight(float percent) const
{
	emit heightPixelChanged(percent * mSize.height());
	emit heightPercentChanged(percent * 100);
}

void ScaleSizeHandler::setWidth(float percent) const
{
	emit widthPixelChanged(percent * mSize.width());
	emit widthPercentChanged(percent * 100);
}

} // namespace kImageAnnotator