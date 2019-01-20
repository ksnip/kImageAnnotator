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

AnnotationItemFactory::AnnotationItemFactory(Config *config)
{
	mPropertiesFactory = new AnnotationPropertiesFactory(config);
	mNumberManager = new NumberManager();
	connect(config, &Config::firstBadgeNumberChanged, mNumberManager, &NumberManager::firstNumberChanged);
	reset();
}

AnnotationItemFactory::~AnnotationItemFactory()
{
	delete mPropertiesFactory;
	delete mNumberManager;
}

void AnnotationItemFactory::reset()
{
	mNextZValue = 1;
	mNumberManager->reset();
}

AbstractAnnotationItem *AnnotationItemFactory::create(const QPointF &initPosition, ToolTypes toolType)
{
	auto properties = mPropertiesFactory->create(toolType);
	auto *newItem = createItem(initPosition, toolType, properties);

	setZValue(newItem);

	return newItem;
}

AbstractAnnotationItem *AnnotationItemFactory::clone(const AbstractAnnotationItem *item)
{
	Q_ASSERT(item != nullptr);

	auto newItem = cloneItem(item);
	setZValue(newItem);

	return newItem;
}

AbstractAnnotationItem *AnnotationItemFactory::createItem(const QPointF &initPosition, const ToolTypes &toolType, AnnotationProperties *properties)
{
	AbstractAnnotationItem *newItem = nullptr;

	switch (toolType) {
		case ToolTypes::Pen:
			newItem = new AnnotationPen(initPosition, dynamic_cast<AnnotationPathProperties *>(properties));
			break;
		case ToolTypes::MarkerPen:
			newItem = new AnnotationPen(initPosition, dynamic_cast<AnnotationPathProperties *>(properties));
			break;
		case ToolTypes::MarkerRect:
			newItem = new AnnotationRect(initPosition, properties);
			break;
		case ToolTypes::MarkerEllipse:
			newItem = new AnnotationEllipse(initPosition, properties);
			break;
		case ToolTypes::Line:
			newItem = new AnnotationLine(initPosition, properties);
			break;
		case ToolTypes::Ellipse:
			newItem = new AnnotationEllipse(initPosition, properties);
			break;
		case ToolTypes::Rect:
			newItem = new AnnotationRect(initPosition, properties);
			break;
		case ToolTypes::Arrow:
			newItem = new AnnotationArrow(initPosition, properties);
			break;
		case ToolTypes::Number:
			newItem = new AnnotationNumber(initPosition, dynamic_cast<AnnotationTextProperties *>(properties));
			mNumberManager->addItem(dynamic_cast<AnnotationNumber *>(newItem));
			break;
		case ToolTypes::Text:
			newItem = new AnnotationText(initPosition, dynamic_cast<AnnotationTextProperties *>(properties));
			break;
		case ToolTypes::Blur:
			newItem = new AnnotationBlur(initPosition, properties);
			break;
		default:
			qCritical("Cannot create item for provided tool type.");
	}
	return newItem;
}

AbstractAnnotationItem *AnnotationItemFactory::cloneItem(const AbstractAnnotationItem *item)
{
	Q_ASSERT(item != nullptr);
	AbstractAnnotationItem *newItem = nullptr;

	switch (item->toolType()) {
		case ToolTypes::Pen:
			newItem = new AnnotationPen(*(static_cast<const AnnotationPen *>(item)));
			break;
		case ToolTypes::MarkerPen:
			newItem = new AnnotationPen(*(static_cast<const AnnotationPen *>(item)));
			break;
		case ToolTypes::Line:
			newItem = new AnnotationLine(*(static_cast<const AnnotationLine *>(item)));
			break;
		case ToolTypes::Ellipse:
			newItem = new AnnotationEllipse(*(static_cast<const AnnotationEllipse *>(item)));
			break;
		case ToolTypes::Rect:
			newItem = new AnnotationRect(*(static_cast<const AnnotationRect *>(item)));
			break;
		case ToolTypes::Arrow:
			newItem = new AnnotationArrow(*(static_cast<const AnnotationArrow *>(item)));
			break;
		case ToolTypes::Number:
			newItem = new AnnotationNumber(*(static_cast<const AnnotationNumber *>(item)));
			break;
		case ToolTypes::Text:
			newItem = new AnnotationText(*(static_cast<const AnnotationText *>(item)));
			break;
		case ToolTypes::Blur:
			newItem = new AnnotationBlur(*(static_cast<const AnnotationBlur *>(item)));
			break;
		default:
			qCritical("Cannot create item for provided tool type.");
	}
	return newItem;
}

void AnnotationItemFactory::setZValue(AbstractAnnotationItem *item)
{
	if (item != nullptr) {
		item->setZValue(mNextZValue++);
	}
}

} // namespace kImageAnnotator
