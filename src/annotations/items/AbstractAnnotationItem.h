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
#include <QCursor>

#include "src/annotations/properties/AnnotationProperties.h"
#include "src/common/enum/FillTypes.h"
#include "src/common/enum/ToolTypes.h"
#include "src/annotations/misc/ShadowEffect.h"

namespace kImageAnnotator {

class AbstractAnnotationItem : public QGraphicsItem
{
public:
	explicit AbstractAnnotationItem(AnnotationProperties *properties);
	AbstractAnnotationItem(const AbstractAnnotationItem &other);
	virtual ~AbstractAnnotationItem();
	virtual QRectF boundingRect() const;
	virtual QPainterPath shape() const;
	virtual bool intersects(const QRectF &rect) const;
	virtual void addPoint(const QPointF &position, bool modified = false) = 0;
	virtual void setPointAt(const QPointF &point, int index) = 0;
	virtual QPointF pointAt(int index) const = 0;
	virtual void setPosition(const QPointF &newPosition) = 0;
	virtual QPointF position();
	virtual const AnnotationProperties *properties() const;
	virtual void finish();
	virtual void scale(qreal sx, qreal sy) = 0;
	virtual AbstractAnnotationItem *clone() const = 0;
	virtual ToolTypes toolType() const = 0;

protected:
	void setShape(QPainterPath &newShape);
	virtual void updateShape() = 0;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

private:
	AnnotationProperties *mProperties;
	QPainterPath *mShape;
	QPainterPathStroker *mStroker;
	QPen mPainterPen;
	ShadowEffect *mShadowEffect;

	bool hasFill() const;
	void shiftPainterForAllOddShapeWidth(QPainter *painter) const;
	void addShadowIfRequired();
};

} // namespace kImageAnnotator

#endif // KIMAGEANNOTATOR_ABSTRACTANNOTATIONITEM_H
