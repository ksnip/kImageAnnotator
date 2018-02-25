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

#include "AnnotationItemFactory.h"

AnnotationItemFactory::AnnotationItemFactory()
{
    mItemProperties = new AnnotationItemProperties(QColor("red"), 3);
}

AnnotationItemFactory::~AnnotationItemFactory()
{
    delete mItemProperties;
}

AbstractAnnotationItem* AnnotationItemFactory::createItem(const QPointF& initPosition, ToolTypes type) const
{
    switch(type) {
        case ToolTypes::Line:
            return new AnnotationLine(initPosition, *mItemProperties);
        case ToolTypes::Ellipse:
            return new AnnotationEllipse(initPosition, *mItemProperties);
        case ToolTypes::Rect:
            return new AnnotationRect(initPosition, *mItemProperties);
        case ToolTypes::Arrow:
            return new AnnotationArrow(initPosition, *mItemProperties);
        default:
            qCritical("Cannot create item for provided tool type.");
            return nullptr;
    }
}

void AnnotationItemFactory::setColor(const QColor& color)
{
    mItemProperties->setBorderColor(color);
    mItemProperties->setFillColor(color);
}

void AnnotationItemFactory::setSize(int size)
{
    mItemProperties->setSize(size);
}
