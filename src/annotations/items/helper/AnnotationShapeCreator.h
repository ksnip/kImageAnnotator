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

#ifndef KIMAGEANNOTATOR_ANNOTATIONSHAPECREATOR_H
#define KIMAGEANNOTATOR_ANNOTATIONSHAPECREATOR_H

#include <QPolygonF>
#include <QTransform>

namespace kImageAnnotator {

class AnnotationShapeCreator
{
public:
	static QPolygonF createPointer(qreal width, qreal length);
	static QPolygonF createArrowHead(int scaleFactor);
	static QPolygonF translate(const QPolygonF &shape, const QPointF &pos, qreal angle);
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_ANNOTATIONSHAPECREATOR_H
