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

#include "AnnotationSticker.h"

namespace kImageAnnotator {

AnnotationSticker::AnnotationSticker(const QPointF &centerPosition, const StickerPropertiesPtr &properties) : AbstractAnnotationRect(centerPosition, properties)
{
	mSvgRenderer.load(properties->path());

	prepareGeometryChange();
	auto center = mRect->center();
	auto size = QSize(100,100);
	mRect->setSize(size);
	mRect->moveCenter(center);
	updateShape();
}

AnnotationSticker::AnnotationSticker(const AnnotationSticker &other) : AbstractAnnotationRect(other)
{
	mSvgRenderer.load(other.stickerProperties()->path());
}

void AnnotationSticker::addPoint(const QPointF &position, bool modified)
{
	Q_UNUSED(position);
	Q_UNUSED(modified);

	// Nothing to do here
}

ToolTypes AnnotationSticker::toolType() const
{
	return ToolTypes::Sticker;
}

StickerPropertiesPtr AnnotationSticker::stickerProperties() const
{
	return AbstractAnnotationItem::properties().staticCast<AnnotationStickerProperties>();
}

void AnnotationSticker::setProperties(const PropertiesPtr &properties)
{
	AbstractAnnotationItem::setProperties(properties);
	mSvgRenderer.load(stickerProperties()->path());
}

void AnnotationSticker::updateShape()
{
	QPainterPath path;
	path.addEllipse(*mRect);
	setShape(path);
}

void AnnotationSticker::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	mSvgRenderer.render(painter, mRect->toRect());
}

} // namespace kImageAnnotator
