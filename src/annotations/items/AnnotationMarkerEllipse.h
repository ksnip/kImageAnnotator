/*
 * Copyright (C) 2021 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KIMAGEANNOTATOR_ANNOTATIONMARKERELLIPSE_H
#define KIMAGEANNOTATOR_ANNOTATIONMARKERELLIPSE_H

#include "AnnotationEllipse.h"

namespace kImageAnnotator {

class AnnotationMarkerEllipse : public AnnotationEllipse
{
Q_OBJECT
public:
	AnnotationMarkerEllipse(const QPointF &startPosition, const PropertiesPtr &properties);
	AnnotationMarkerEllipse(const AnnotationMarkerEllipse &other) = default;
	~AnnotationMarkerEllipse() override = default;
	Tools toolType() const override;

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
	QPainter::CompositionMode compositionMode() const override;
	void updateShadow() override;
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_ANNOTATIONMARKERELLIPSE_H
