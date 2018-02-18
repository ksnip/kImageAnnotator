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

#include "AnnotationItemModifier.h"

AnnotationItemModifier::AnnotationItemModifier()
{
    mLineItem = nullptr;
}

QRectF AnnotationItemModifier::boundingRect() const
{
    if (mLineItem) {
        return mLineItem->boundingRect().adjusted(-5, -5, 5, 5);
    }
}

void AnnotationItemModifier::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    if (mLineItem != nullptr) {
        auto line = mLineItem->line();
        painter->setPen(QColor("white"));
        painter->setBrush(QColor("gray"));
        painter->drawEllipse(line.p1(), 5, 5);
        painter->drawEllipse(line.p2(), 5, 5);
    }
}

void AnnotationItemModifier::attachTo(AbstractAnnotationLine* lineItem)
{
    prepareGeometryChange();
    mLineItem = lineItem;
}

