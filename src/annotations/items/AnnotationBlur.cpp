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

#include "AnnotationBlur.h"

namespace kImageAnnotator {

AnnotationBlur::AnnotationBlur(const QPointF &startPosition, AnnotationProperties *properties) : AbstractAnnotationRect(startPosition, properties)
{
	setGraphicsEffect(new BlurEffect());
}

AnnotationBlur *AnnotationBlur::clone() const
{
	return new AnnotationBlur(*this);
}

void AnnotationBlur::updateShape()
{
	QPainterPath path;
	path.addRect(*mRect);
	setShape(path);
}

void AnnotationBlur::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	auto parentScene = scene();
	if (parentScene != nullptr) {
		QImage image(parentScene->sceneRect().size().toSize(), QImage::Format_ARGB32);
		image.fill(Qt::transparent);

		QPainter imagePainter(&image);
		parentScene->render(&imagePainter);

		auto sceneBehindItem = image.copy(mRect->toRect());

		painter->drawImage(*mRect, sceneBehindItem);
	}
}

} // namespace kImageAnnotator
