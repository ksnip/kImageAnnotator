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

#include "AnnotationItemFactory.h"

namespace kImageAnnotator {

AnnotationItemFactory::AnnotationItemFactory()
{
	mConfig = Config::instance();
	mPropertiesFactory = new AnnotationPropertiesFactory();
	reset();
}

AnnotationItemFactory::~AnnotationItemFactory()
{
	delete mPropertiesFactory;
}

void AnnotationItemFactory::reset()
{
	mNextNumber = 1;
	mNextZValue = 1;
}

AbstractAnnotationItem *AnnotationItemFactory::createItem(const QPointF &initPosition, ToolTypes toolType)
{
	auto properties = mPropertiesFactory->createProperties(toolType);
	AbstractAnnotationItem *item = nullptr;

	switch (toolType) {
		case ToolTypes::Pen:
			item = new AnnotationPen(initPosition, dynamic_cast<AnnotationPathProperties *>(properties));
			break;
		case ToolTypes::Marker:
			item = new AnnotationPen(initPosition, dynamic_cast<AnnotationPathProperties *>(properties));
			break;
		case ToolTypes::Line:
			item = new AnnotationLine(initPosition, properties);
			break;
		case ToolTypes::Ellipse:
			item = new AnnotationEllipse(initPosition, properties);
			break;
		case ToolTypes::Rect:
			item = new AnnotationRect(initPosition, properties);
			break;
		case ToolTypes::Arrow:
			item = new AnnotationArrow(initPosition, properties);
			break;
		case ToolTypes::Number:
			item = new AnnotationNumber(initPosition, mNextNumber++, dynamic_cast<AnnotationTextProperties *>(properties));
			break;
		case ToolTypes::Text:
			item = new AnnotationText(initPosition, mConfig->textFont(), properties);
			break;
		default:
			qCritical("Cannot create item for provided tool type.");
	}

	if (item != nullptr) {
		item->setZValue(mNextZValue++);
	}

	return item;
}

} // namespace kImageAnnotator
