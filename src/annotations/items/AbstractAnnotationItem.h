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

#ifndef KIMAGEANNOTATOR_ABSTRACTANNOTATIONITEM_H
#define KIMAGEANNOTATOR_ABSTRACTANNOTATIONITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPainterPathStroker>

#include "../core/AnnotationProperties.h"
#include "../../common/enum/FillTypes.h"
#include "../misc/ShadowEffect.h"

class AbstractAnnotationItem : public QGraphicsItem
{
public:
    explicit AbstractAnnotationItem(const AnnotationProperties &properties);
    virtual ~AbstractAnnotationItem();
    virtual QRectF boundingRect() const override;
    virtual QPainterPath shape() const override;
    virtual bool intersects(const QRectF &rect) const;
    virtual void addPoint(const QPointF &position, bool modified = false) = 0;
    virtual void setPointAt(const QPointF &point, int index) = 0;
    virtual QPointF pointAt(int index) const = 0;
    virtual void setPosition(const QPointF &newPosition) = 0;
    virtual QPointF position();
    AnnotationProperties properties() const;
    virtual void finish();

protected:
    void setShape(QPainterPath &newShape);
    virtual void updateShape() = 0;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

private:
    AnnotationProperties *mProperties;
    QPainterPath *mShape;
    QPainterPathStroker *mStroker;
    QPen mPainterPen;
    ShadowEffect *mShadowEffect;

    bool hasFill() const;
    void shiftPainterForAllOddShapeWidth(QPainter *painter) const;
};

#endif // KIMAGEANNOTATOR_ABSTRACTANNOTATIONITEM_H
