/*
 * Copyright (C) 2019 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KIMAGEANNOTATOR_ANNOTATIONDOUBLEARROW_H
#define KIMAGEANNOTATOR_ANNOTATIONDOUBLEARROW_H

#include "AnnotationArrow.h"

namespace kImageAnnotator {

class AnnotationDoubleArrow : public AnnotationArrow
{
public:
	AnnotationDoubleArrow(const QPointF &startPosition, const PropertiesPtr &properties);
	explicit AnnotationDoubleArrow(const AnnotationArrow &other);
	~AnnotationDoubleArrow() override = default;
	ToolTypes toolType() const override;

protected:
	void updateShape() override;
	QPolygonF positionArrowHeadAtStart(const QPolygonF &arrow) const;
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_ANNOTATIONDOUBLEARROW_H
