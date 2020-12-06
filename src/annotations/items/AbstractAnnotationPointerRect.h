/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef KIMAGEANNOTATOR_ABSTRACTANNOTATIONPOINTERRECT_H
#define KIMAGEANNOTATOR_ABSTRACTANNOTATIONPOINTERRECT_H

#include "AbstractAnnotationRect.h"

namespace kImageAnnotator {

class AbstractAnnotationPointerRect : public AbstractAnnotationRect
{
public:
	AbstractAnnotationPointerRect(const QPointF &startPosition, const PropertiesPtr &properties);
	AbstractAnnotationPointerRect(const AbstractAnnotationPointerRect &other);
	~AbstractAnnotationPointerRect() override = default;
	void addPoint(const QPointF &position, bool modified) override;
	void setPosition(const QPointF &newPosition) override;
	void setPointAt(const QPointF &point, int index, bool keepAspectRatio) override;
	QPointF pointAt(int index) const override;
	void finish() override;

protected:
	QPointF mPointer;
	int mPointerIndex;

	bool isPointer(int index) const;
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_ABSTRACTANNOTATIONPOINTERRECT_H
