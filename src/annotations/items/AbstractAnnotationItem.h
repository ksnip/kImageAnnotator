/*
 * Copyright (C) 2018 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
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

#include <QGraphicsWidget>
#include <QPainter>
#include <QPainterPathStroker>
#include <QCursor>

#include "src/annotations/properties/AnnotationProperties.h"
#include "src/common/enum/FillModes.h"
#include "src/common/enum/Tools.h"
#include "src/annotations/misc/ShadowEffect.h"

namespace kImageAnnotator {

class AbstractAnnotationItem : public QGraphicsWidget
{
public:
	explicit AbstractAnnotationItem(const PropertiesPtr &properties);
	AbstractAnnotationItem(const AbstractAnnotationItem &other);
	~AbstractAnnotationItem() override;
	QRectF boundingRect() const override;
	QPainterPath shape() const override;
	virtual bool intersects(const QRectF &rect) const;
	virtual void addPoint(const QPointF &position, bool modified) = 0;
	virtual void setPointAt(const QPointF &point, int index) = 0;
	virtual QPointF pointAt(int index) const = 0;
	virtual void setPosition(const QPointF &newPosition) = 0;
	virtual QPointF position();
	virtual PropertiesPtr properties() const;
	virtual void finish();
	virtual bool requiresSelectionAfterCreation() const;
	virtual void scale(qreal sx, qreal sy) = 0;
	virtual Tools toolType() const = 0;
	virtual void setProperties(const PropertiesPtr &properties);

protected:
	void setShape(QPainterPath &newShape);
	virtual void updateShape() = 0;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;
	virtual void updateProperties(const PropertiesPtr &properties);
	bool hasFill() const;
	bool hasBorder() const;
	void adjustPainter(QPainter *painter) const;
	QPen painterPen() const;

private:
	PropertiesPtr mProperties;
	QPainterPath *mShape;
	QPainterPathStroker *mStroker;
	QPen mPainterPen;
	ShadowEffect *mShadowEffect;

	void shiftPainterForAllOddShapeWidth(QPainter *painter) const;
	void addShadowIfRequired();
	void drawPath(QPainter *painter) const;
	void drawPoint(QPainter *painter) const;
};

} // namespace kImageAnnotator

#endif // KIMAGEANNOTATOR_ABSTRACTANNOTATIONITEM_H
