/*
 * Copyright (C) 2018 Damir Porobic <damir.porobic@gmx.com>
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

#include "AnnotationItemProperties.h"

AnnotationItemProperties::AnnotationItemProperties(const QColor& color, int size)
{
    mBorderColor = color;
    mFillColor = color;
    mSize = size;
}

AnnotationItemProperties::AnnotationItemProperties(const QColor& borderColor, const QColor& fillColor, int size)
{
    mBorderColor = qMove(borderColor);
    mFillColor = qMove(fillColor);
    mSize = size;
}

AnnotationItemProperties::AnnotationItemProperties(const AnnotationItemProperties& other)
{
    mBorderColor = other.mBorderColor;
    mFillColor = other.mFillColor;
    mSize = other.mSize;
    mFillType = other.mFillType;
}

QColor AnnotationItemProperties::borderColor() const
{
    return mBorderColor;
}

void AnnotationItemProperties::setBorderColor(const QColor& borderColor)
{
    mBorderColor = qMove(borderColor);
}

QColor AnnotationItemProperties::fillColor() const
{
    return mFillColor;
}

void AnnotationItemProperties::setFillColor(const QColor& fillColor)
{
    mFillColor = qMove(fillColor);
}

int AnnotationItemProperties::size() const
{
    return mSize;
}

void AnnotationItemProperties::setSize(int size)
{
    mSize = size;
}

FillTypes AnnotationItemProperties::fillType() const
{
    return mFillType;
}

void AnnotationItemProperties::setFillType(FillTypes fillType)
{
    mFillType = fillType;
}

