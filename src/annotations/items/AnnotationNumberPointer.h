/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KIMAGEANNOTATOR_ANNOTATIONNUMBERPOINTER_H
#define KIMAGEANNOTATOR_ANNOTATIONNUMBERPOINTER_H

#include "src/annotations/items/AbstractAnnotationPointerRect.h"
#include "src/annotations/items/BaseAnnotationNumber.h"
#include "src/annotations/items/helper/AnnotationShapeCreator.h"
#include "src/annotations/properties/AnnotationTextProperties.h"

namespace kImageAnnotator {

class AnnotationNumberPointer : public AbstractAnnotationPointerRect, public BaseAnnotationNumber
{
Q_OBJECT
public:
	AnnotationNumberPointer(const QPointF &startPosition, const TextPropertiesPtr& properties);
	AnnotationNumberPointer(const AnnotationNumberPointer &other);
	~AnnotationNumberPointer() override = default;
	Tools toolType() const override;
	TextPropertiesPtr textProperties() const;

protected:
	void updateShape() override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
	void updateProperties() override;

private:
	void updateRect() override;
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_ANNOTATIONNUMBERPOINTER_H
