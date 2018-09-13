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

#include <QtCore/QPointF>
#include "MathHelper.h"

namespace kImageAnnotator {

qreal MathHelper::roundAngleTo(const qreal currentAngle, const int increments)
{
    auto modulo = (int) currentAngle % increments;
    auto requiredRoundup = modulo < increments / 2 ? -modulo : increments - modulo;
    auto newAngle = qFloor(currentAngle + requiredRoundup);
    return newAngle;
}

qreal MathHelper::smallerValue(qreal value1, qreal value2)
{
    qreal value = (qAbs(value1) < qAbs(value2)) ? qAbs(value1) : qAbs(value2);
    return (value1 < 0) ? -value : value;
}

qreal MathHelper::distanceBetweenPoints(const QPointF &point1, const QPointF &point2)
{
    auto horizontalDistance = (point1.x() - point2.x()) * (point1.x() - point2.x());
    auto verticalDistance = (point1.y() - point2.y()) * (point1.y() - point2.y());
    return qSqrt(horizontalDistance + verticalDistance);
}

} // namespace kImageAnnotator