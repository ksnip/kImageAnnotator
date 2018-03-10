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

#ifndef ANNOTATIONPROPERTIES_H
#define ANNOTATIONPROPERTIES_H

#include <QColor>

#include "../common/enum/FillTypes.h"

class AnnotationProperties
{
public:
    AnnotationProperties(const QColor& color, int size);
    AnnotationProperties(const QColor& borderColor, const QColor& fillColor, int size);
    AnnotationProperties(const AnnotationProperties& other);
    ~AnnotationProperties() = default;
    QColor borderColor() const;
    void setBorderColor(const QColor& borderColor);
    QColor fillColor() const;
    void setFillColor(const QColor& fillColor);
    int size() const;
    void setSize(int size);
    FillTypes fillType() const;
    void setFillType(FillTypes fillType);

private:
    QColor    mBorderColor;
    QColor    mFillColor;
    int       mSize;
    FillTypes mFillType;
};

#endif // ANNOTATIONPROPERTIES_H
