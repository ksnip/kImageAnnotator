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

#include "AbstractAnnotationObfuscate.h"

#include <QDebug>

namespace kImageAnnotator {


AbstractAnnotationObfuscate::AbstractAnnotationObfuscate(const QPointF &startPosition, const PropertiesPtr &properties) :
	AbstractAnnotationRect(startPosition, properties),
	mObfuscationUpdateRequired(true)
{

}

AbstractAnnotationObfuscate::AbstractAnnotationObfuscate(const AbstractAnnotationObfuscate &other) :
	AbstractAnnotationRect(other),
	mObfuscationUpdateRequired(true)
{

}

ObfuscatePropertiesPtr AbstractAnnotationObfuscate::obfuscateProperties() const
{
	return AbstractAnnotationItem::properties().staticCast<AnnotationObfuscateProperties>();
}

void AbstractAnnotationObfuscate::setProperties(const PropertiesPtr &properties)
{
	AbstractAnnotationItem::setProperties(properties);
	updateShape();
}

void AbstractAnnotationObfuscate::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	// We need to update the image here, otherwise the scene is not ready
	// to be painted, and we only draw the background
	if (mObfuscationUpdateRequired) {
		updateOverlayImage();
		mObfuscationUpdateRequired = false;
	}

	painter->drawImage(mRect->normalized(), mObfuscatedImage);
}

void AbstractAnnotationObfuscate::updateShape()
{
	mObfuscationUpdateRequired = true;

	QPainterPath path;
	path.addRect(*mRect);
	setShape(path);
}

void AbstractAnnotationObfuscate::updateOverlayImage()
{
	auto parentScene = scene();
	if (parentScene != nullptr) {
		auto sceneSize = parentScene->sceneRect().size().toSize();
		QImage image(sceneSize, QImage::Format_ARGB32_Premultiplied);
		image.fill(Qt::transparent);

		QPainter imagePainter(&image);
		parentScene->render(&imagePainter);

		auto sceneOffset = parentScene->sceneRect().topLeft().toPoint();
		auto itemRect = mRect->normalized().toRect();
		itemRect.translate(-sceneOffset);
		auto sceneBehindItem = image.copy(itemRect);
		mObfuscatedImage = obfuscateBackground(sceneBehindItem);
	}
}

} // namespace kImageAnnotator