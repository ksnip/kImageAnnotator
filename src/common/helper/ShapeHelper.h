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

#ifndef KIMAGEANNOTATOR_SHAPEHELPER_H
#define KIMAGEANNOTATOR_SHAPEHELPER_H

#include <QRectF>
#include <QLineF>

#include "src/common/helper/MathHelper.h"
#include "src/common/constants/AnnotationConstants.h"

class ShapeHelper
{
public:
    static QPointF rectTopLeftWithOffset(const QRectF &rect, int offset);
    static QPointF rectTop(const QRectF &rect);
    static QPointF rectTopWithOffset(const QRectF &rect, int offset);
    static QPointF rectTopRightWithOffset(const QRectF &rect, int offset);
    static QPointF rectRight(const QRectF &rect);
    static QPointF rectRightWithOffset(const QRectF &rect, int offset);
    static QPointF rectBottomRightWithOffset(const QRectF &rect, int offset);
    static QPointF rectBottom(const QRectF &rect);
    static QPointF rectBottomWithOffset(const QRectF &rect, int offset);
    static QPointF rectBottomLeftWithOffset(const QRectF &rect, int offset);
    static QPointF rectLeft(const QRectF &rect);
    static QPointF rectLeftWithOffset(const QRectF &rect, int offset);
    static QLineF extendLine(const QLineF &line, int extendBy);
    static QPointF rectPointAtIndex(const QRectF &rect, int index);
    static QRectF setRectPointAtIndex(const QRectF &rect, int index, const QPointF &pos);
    static QPainterPath smoothOut(const QPainterPath &path);

private:
    static int invertOffsetIfTopSmallerThenBottom(const QRectF &rect, int yOffset);
    static int invertOffsetIfLeftSmallerThenRight(const QRectF &rect, int xOffset);
    static QPointF getBeginOfRounding(const QPointF &point1, const QPointF &point2);
    static QPointF getEndOfRounding(const QPointF &point1, const QPointF &point2);
    static double getRoundingRate(const QPointF &point1, const QPointF &point2);
    static QList<QPointF> getPathPoints(const QPainterPath &path);
    static QPainterPath createSmoothPath(const QList<QPointF> &points);
};

#endif // KIMAGEANNOTATOR_SHAPEHELPER_H
