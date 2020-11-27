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

#include "AnnotationDuplicate.h"

namespace kImageAnnotator {

AnnotationDuplicate::AnnotationDuplicate(const QPointF &startPosition, const PropertiesPtr &properties) :
		AbstractAnnotationRect(startPosition, properties),
		mItemCreationFinished(false)
{
	auto annotationProperties = new AnnotationProperties(QColor(0, 255, 0, 30), 1);
	annotationProperties->setFillType(FillModes::NoBorderAndFill);
	annotationProperties->setShadowEnabled(false);
	PropertiesPtr propsPtr(annotationProperties);
	updateProperties(propsPtr);
}

Tools AnnotationDuplicate::toolType() const
{
	return Tools::Duplicate;
}

bool AnnotationDuplicate::requiresSelectionAfterCreation() const
{
	return true;
}

void AnnotationDuplicate::updateShape()
{
	QPainterPath path;
	path.addRect(*mRect);
	setShape(path);
}

void AnnotationDuplicate::finish()
{
	prepareGeometryChange();
	mItemCreationFinished = true;

	captureScene();
}

void AnnotationDuplicate::captureScene()
{
	auto parentScene = scene();
	if (parentScene != nullptr) {
		mSceneSelectionImage = QImage(mRect->normalized().size().toSize(), QImage::Format_ARGB32_Premultiplied);
		mSceneSelectionImage.fill(Qt::transparent);
		QPainter imagePainter(&mSceneSelectionImage);

		QRectF targetRect;
		targetRect.setSize(mRect->normalized().size());
		targetRect.setTopLeft(QPointF(0, 0));

		parentScene->render(&imagePainter, targetRect, mRect->normalized());
	}
}

void AnnotationDuplicate::paint(QPainter *painter, const QStyleOptionGraphicsItem *style, QWidget *widget)
{
	if (!mItemCreationFinished) {
		AbstractAnnotationItem::paint(painter, style, widget);
	} else {
		painter->drawImage(mRect->normalized(), mSceneSelectionImage);
	}
}

} // namespace kImageAnnotator
