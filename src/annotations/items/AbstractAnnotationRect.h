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

#ifndef KIMAGEANNOTATOR_ABSTRACTANNOTATIONRECT_H
#define KIMAGEANNOTATOR_ABSTRACTANNOTATIONRECT_H

#include "AbstractAnnotationItem.h"
#include "src/common/helper/MathHelper.h"
#include "src/common/helper/ShapeHelper.h"
#include "src/common/constants/Constants.h"
#include "src/common/helper/RectSizeHelper.h"

namespace kImageAnnotator {

class AbstractAnnotationRect : public AbstractAnnotationItem
{
public:
	AbstractAnnotationRect(const QPointF &startPosition, const PropertiesPtr &properties);
	AbstractAnnotationRect(const AbstractAnnotationRect &other);
	~AbstractAnnotationRect() override;
	void addPoint(const QPointF &position, bool modified) override;
	void setPosition(const QPointF &newPosition) override;
	QRectF rect() const;
	void setPointAt(const QPointF &point, int index, bool keepAspectRatio) override;
	QPointF pointAt(int index) const override;
	void scale(qreal sx, qreal sy) override;

protected:
	QRectF *mRect;

	void makeSymmetric(bool enabled);
};

} // namespace kImageAnnotator

#endif // KIMAGEANNOTATOR_ABSTRACTANNOTATIONRECT_H
