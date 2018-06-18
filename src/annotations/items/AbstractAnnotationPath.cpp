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

#include "AbstractAnnotationPath.h"

AbstractAnnotationPath::AbstractAnnotationPath(const QPointF &startPosisition, const AnnotationProperties &properties) : AbstractAnnotationItem(properties)
{
    mPath = new QPainterPath();
    mPath->moveTo(startPosisition);
    mPath->lineTo(startPosisition + QPointF(1, 1));
}

AbstractAnnotationPath::~AbstractAnnotationPath()
{
    delete mPath;
}

void AbstractAnnotationPath::addPoint(const QPointF &position, bool modified)
{
    prepareGeometryChange();
    mPath->lineTo(position);
    updateShape();
}

void AbstractAnnotationPath::setPosition(const QPointF &newPosition)
{
    prepareGeometryChange();
    mPath->translate(newPosition - position());
    updateShape();
}

void AbstractAnnotationPath::setPointAt(const QPointF &point, int handleIndex)
{
    prepareGeometryChange();

    auto currentPos = ShapeHelper::rectPointAtIndex(boundingRect(), handleIndex);
    auto rect = ShapeHelper::setRectPointAtIndex(boundingRect(), handleIndex, point);
    scalePath(rect);
    mPath->translate(currentPos - ShapeHelper::rectPointAtIndex(boundingRect(), handleIndex));

    updateShape();
}

QPointF AbstractAnnotationPath::pointAt(int index) const
{
    if (index <= 0) {
        return mPath->boundingRect().topLeft();
    } else if (index == 1) {
        return { mPath->boundingRect().center().x(), mPath->boundingRect().top() };
    } else if (index == 2) {
        return mPath->boundingRect().topRight();
    } else if (index == 3) {
        return { mPath->boundingRect().right(), mPath->boundingRect().center().y() };
    } else if (index == 4) {
        return mPath->boundingRect().bottomRight();
    } else if (index == 5) {
        return { mPath->boundingRect().center().x(), mPath->boundingRect().bottom() };
    } else if (index == 6) {
        return mPath->boundingRect().bottomLeft();
    } else {
        return { mPath->boundingRect().left(), mPath->boundingRect().center().y() };
    }
}

void AbstractAnnotationPath::scalePath(const QRectF &rect)
{
    QTransform transform;
    transform.scale(rect.width() / boundingRect().width(), rect.height() / boundingRect().height());
    auto sPath = transform.map(*mPath);
    mPath->swap(sPath);
    updateShape();
}
