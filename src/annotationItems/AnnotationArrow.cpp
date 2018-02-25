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

#include "AnnotationArrow.h"

AnnotationArrow::AnnotationArrow(const QPointF& startPosisition, const AnnotationItemProperties& properties) :
    AbstractAnnotationLine(startPosisition, properties)
{
}

void AnnotationArrow::updateShape()
{
    QPainterPath path(mLine->p1());
    path.lineTo(mLine->p2());

    auto arrow = createArrow();
    auto finishedArrow = rotateAndPositionArrow(arrow);

    path.addPolygon(finishedArrow);
    path.closeSubpath();
    setShape(path);
}

QPolygonF AnnotationArrow::createArrow() const
{
    int mArrowHeadLength = 20;
    int mArrowHeadWidth = 10;
    int mArrowHeadMid = 17;

    QPointF p0(0, 0);
    QPointF p1(-mArrowHeadLength, mArrowHeadWidth);
    QPointF p2(-mArrowHeadMid, 1);
    QPointF p3(-mLine->length(), 1);
    QPointF p4(-mLine->length(), -1);
    QPointF p5(-mArrowHeadMid, -1);
    QPointF p6(-mArrowHeadLength, -mArrowHeadWidth);

    QPolygonF arrow;
    arrow << p0 << p1 << p2 << p3 << p4 << p5 << p6;

    return arrow;
}

QPolygonF AnnotationArrow::rotateAndPositionArrow(const QPolygonF& arrow) const
{
    auto endX = mLine->p2().x();
    auto endY = mLine->p2().y();
    auto angle = -mLine->angle();

    return QTransform().translate(endX, endY).rotate(angle).map(arrow);
}
