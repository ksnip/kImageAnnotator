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

#include "ShapeHelper.h"

QPointF ShapeHelper::rectTopLeftWithOffset(const QRectF &rect, int offset)
{
    auto xOffset = invertOffsetIfLeftSmallerThenRight(rect, offset);
    auto yOffset = invertOffsetIfTopSmallerThenBottom(rect, offset);
    return QPointF(rect.topLeft().x() + xOffset, rect.topLeft().y() + yOffset);
}

QPointF ShapeHelper::rectTop(const QRectF &rect)
{
    return QPointF(rect.center().x(), rect.top());
}

QPointF ShapeHelper::rectTopWithOffset(const QRectF &rect, int offset)
{
    offset = invertOffsetIfTopSmallerThenBottom(rect, offset);
    return QPointF(rect.center().x(), rect.top() + offset);
}

QPointF ShapeHelper::rectTopRightWithOffset(const QRectF &rect, int offset)
{
    auto xOffset = invertOffsetIfLeftSmallerThenRight(rect, -offset);
    auto yOffset = invertOffsetIfTopSmallerThenBottom(rect, offset);
    return QPointF(rect.topRight().x() + xOffset, rect.topRight().y() + yOffset);
}

QPointF ShapeHelper::rectRight(const QRectF &rect)
{
    return QPointF(rect.right(), rect.center().y());
}

QPointF ShapeHelper::rectRightWithOffset(const QRectF &rect, int offset)
{
    offset = invertOffsetIfLeftSmallerThenRight(rect, -offset);
    return QPointF(rect.right() + offset, rect.center().y());
}

QPointF ShapeHelper::rectBottomRightWithOffset(const QRectF &rect, int offset)
{
    auto xOffset = invertOffsetIfLeftSmallerThenRight(rect, -offset);
    auto yOffset = invertOffsetIfTopSmallerThenBottom(rect, -offset);
    return QPointF(rect.bottomRight().x() + xOffset, rect.bottomRight().y() + yOffset);
}

QPointF ShapeHelper::rectBottom(const QRectF &rect)
{
    return QPointF(rect.center().x(), rect.bottom());
}

QPointF ShapeHelper::rectBottomWithOffset(const QRectF &rect, int offset)
{
    offset = invertOffsetIfTopSmallerThenBottom(rect, -offset);
    return QPointF(rect.center().x(), rect.bottom() + offset);
}

QPointF ShapeHelper::rectBottomLeftWithOffset(const QRectF &rect, int offset)
{
    auto xOffset = invertOffsetIfLeftSmallerThenRight(rect, offset);
    auto yOffset = invertOffsetIfTopSmallerThenBottom(rect, -offset);
    return QPointF(rect.bottomLeft().x() + xOffset, rect.bottomLeft().y() + yOffset);
}

QPointF ShapeHelper::rectLeft(const QRectF &rect)
{
    return QPointF(rect.left(), rect.center().y());
}

QPointF ShapeHelper::rectLeftWithOffset(const QRectF &rect, int offset)
{
    offset = invertOffsetIfLeftSmallerThenRight(rect, offset);
    return QPointF(rect.left() + offset, rect.center().y());
}

QLineF ShapeHelper::extendLine(const QLineF &line, int extendBy)
{
    QLineF newLine(line.p2().x(), line.p2().y(), line.p1().x(), line.p1().y());
    newLine.setLength(newLine.length() + extendBy / 2);
    newLine.setLine(newLine.p2().x(), newLine.p2().y(), newLine.p1().x(), newLine.p1().y());
    newLine.setLength(newLine.length() + extendBy / 2);
    return newLine;
}

int ShapeHelper::invertOffsetIfLeftSmallerThenRight(const QRectF &rect, int xOffset)
{
    if (rect.left() < rect.right()) {
        xOffset *= -1;
    }
    return xOffset;
}

int ShapeHelper::invertOffsetIfTopSmallerThenBottom(const QRectF &rect, int yOffset)
{
    if (rect.top() < rect.bottom()) {
        yOffset *= -1;
    }
    return yOffset;
}
