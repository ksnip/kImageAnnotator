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

#include "ControlPoints.h"

ControlPoints::ControlPoints(int controlPointSize)
{
    mPointSize = controlPointSize;
    mLineItem = nullptr;
    mRectItem = nullptr;
}

void ControlPoints::initPoints(AbstractAnnotationItem* item)
{
    mLineItem = dynamic_cast<AbstractAnnotationLine*>(item);
    mRectItem = dynamic_cast<AbstractAnnotationRect*>(item);
    mPoints.clear();
    if(mLineItem) {
        addPosintsToList(2);
    } else if(mRectItem) {
        addPosintsToList(8);
    }
    updatePointsPosition();
}

void ControlPoints::updatePointsPosition()
{
    if(mLineItem) {
        auto line = mLineItem->line();
        mPoints[0].moveCenter(line.p1());
        mPoints[1].moveCenter(line.p2());
    } else if(mRectItem) {
        auto rect = mRectItem->rect();
        mPoints[0].moveCenter(rect.topLeft());
        mPoints[1].moveCenter(QPointF(rect.center().x(), rect.top()));
        mPoints[2].moveCenter(rect.topRight());
        mPoints[3].moveCenter(QPointF(rect.right(), rect.center().y()));
        mPoints[4].moveCenter(rect.bottomRight());
        mPoints[5].moveCenter(QPointF(rect.center().x(), rect.bottom()));
        mPoints[6].moveCenter(rect.bottomLeft());
        mPoints[7].moveCenter(QPointF(rect.left(), rect.center().y()));
    }
}

int ControlPoints::indexOfPointAt(const QPointF& point) const
{
    for(auto controlPoint : mPoints) {
        if(controlPoint.contains(point)) {
            return mPoints.indexOf(controlPoint);
        }
    }
    return -1;
}

QList<QRectF> ControlPoints::points() const
{
    return mPoints;
}

QRectF ControlPoints::point(int index) const
{
    if(index < 0 || index >= mPoints.count()) {
        return QRectF();
    }

    return mPoints[index];
}

void ControlPoints::addPosintsToList(int count)
{
    for(auto i = 0; i < count; i++) {
        mPoints.append(QRectF(0, 0, mPointSize, mPointSize));
    }
}
