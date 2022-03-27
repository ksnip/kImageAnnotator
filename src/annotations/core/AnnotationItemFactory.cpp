/*
 * Copyright (C) 2018 Damir Porobic <damir.porobic@gmx.com>
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

#include "AnnotationItemFactory.h"

namespace kImageAnnotator {

AnnotationItemFactory::AnnotationItemFactory(AnnotationPropertiesFactory *propertiesFactory, AbstractSettingsProvider *settingsProvider, Config *config) :
	mPropertiesFactory(propertiesFactory),
	mSettingsProvider(settingsProvider),
	mConfig(config),
	mNumberManager(new NumberManager),
	mNextZValue(1)
{
	Q_ASSERT(mSettingsProvider != nullptr);
	Q_ASSERT(mConfig != nullptr);

	connect(mConfig, &Config::numberUpdateModeChanged, this, &AnnotationItemFactory::setNumberUpdateMode);
	connect(mNumberManager, &NumberManager::numberSeedChanged, this, &AnnotationItemFactory::numberSeedChanged);
	setNumberUpdateMode(mConfig->numberUpdateMode());

	reset();
}


AnnotationItemFactory::~AnnotationItemFactory()
{
	delete mNumberManager;
}

void AnnotationItemFactory::reset()
{
	mNextZValue = 1;
	mNumberManager->reset();
}

void AnnotationItemFactory::setNumberToolSeed(int numberSeed)
{
	mNumberManager->setNumberSeed(numberSeed);
}

int AnnotationItemFactory::numberToolSeed() const
{
	return mNumberManager->numberSeed();
}

void AnnotationItemFactory::setNumberUpdateMode(NumberUpdateMode numberUpdateMode)
{
	mNumberManager->setNumberUpdateMode(numberUpdateMode);
}

AbstractAnnotationItem *AnnotationItemFactory::create(const QPointF &initPosition)
{
	auto toolType = mSettingsProvider->toolType();
	auto properties = mPropertiesFactory->create(toolType);
	auto newItem = createItem(initPosition, toolType, properties);

	initItem(newItem);

	return newItem;
}

AbstractAnnotationItem *AnnotationItemFactory::create(const QPointF &initPosition, const QPixmap &image)
{
    auto properties = mPropertiesFactory->createFromConfig(Tools::Image);
    auto newItem = new AnnotationImage(initPosition, image, properties);

	initItem(newItem);

    return newItem;
}

AbstractAnnotationItem *AnnotationItemFactory::clone(const AbstractAnnotationItem *item)
{
	Q_ASSERT(item != nullptr);

	auto newItem = cloneItem(item);

	initItem(newItem);

	return newItem;
}

AbstractAnnotationItem *AnnotationItemFactory::createItem(const QPointF &initPosition, const Tools &toolType, const PropertiesPtr &properties)
{
	AbstractAnnotationItem *newItem = nullptr;

	switch (toolType) {
		case Tools::Duplicate:
			newItem = new AnnotationDuplicate(initPosition, properties);
			break;
		case Tools::Pen:
			newItem = new AnnotationPen(initPosition, properties.staticCast<AnnotationPathProperties>());
			break;
		case Tools::MarkerPen:
			newItem = new AnnotationMarkerPen(initPosition, properties.staticCast<AnnotationPathProperties>());
			break;
		case Tools::MarkerRect:
			newItem = new AnnotationMarkerRect(initPosition, properties);
			break;
		case Tools::MarkerEllipse:
			newItem = new AnnotationMarkerEllipse(initPosition, properties);
			break;
		case Tools::Line:
			newItem = new AnnotationLine(initPosition, properties);
			break;
		case Tools::Ellipse:
			newItem = new AnnotationEllipse(initPosition, properties);
			break;
		case Tools::Rect:
			newItem = new AnnotationRect(initPosition, properties);
			break;
		case Tools::Arrow:
			newItem = new AnnotationArrow(initPosition, properties);
			break;
		case Tools::DoubleArrow:
			newItem = new AnnotationDoubleArrow(initPosition, properties);
			break;
		case Tools::Number:
			newItem = new AnnotationNumber(initPosition, properties.staticCast<AnnotationTextProperties>());
			mNumberManager->addItem(dynamic_cast<AnnotationNumber *>(newItem));
			break;
		case Tools::NumberPointer:
			newItem = new AnnotationNumberPointer(initPosition, properties.staticCast<AnnotationTextProperties>());
			mNumberManager->addItem(dynamic_cast<AnnotationNumberPointer *>(newItem));
			break;
		case Tools::NumberArrow:
			newItem = new AnnotationNumberArrow(initPosition, properties.staticCast<AnnotationTextProperties>());
			mNumberManager->addItem(dynamic_cast<AnnotationNumberArrow *>(newItem));
			break;
		case Tools::Text:
			newItem = new AnnotationText(initPosition, properties.staticCast<AnnotationTextProperties>());
			break;
		case Tools::TextPointer:
			newItem = new AnnotationTextPointer(initPosition, properties.staticCast<AnnotationTextProperties>());
			break;
		case Tools::TextArrow:
			newItem = new AnnotationTextArrow(initPosition, properties.staticCast<AnnotationTextProperties>());
			break;
		case Tools::Blur:
			newItem = new AnnotationBlur(initPosition, properties.staticCast<AnnotationObfuscateProperties>());
			break;
		case Tools::Pixelate:
			newItem = new AnnotationPixelate(initPosition, properties.staticCast<AnnotationObfuscateProperties>());
			break;
		case Tools::Sticker:
			newItem = new AnnotationSticker(initPosition, properties.staticCast<AnnotationStickerProperties>());
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
		case Tools::Duplicate:
			newItem = new AnnotationDuplicate(*(dynamic_cast<const AnnotationDuplicate *>(item)));
			break;
		case Tools::Pen:
			newItem = new AnnotationPen(*(dynamic_cast<const AnnotationPen *>(item)));
			break;
		case Tools::MarkerPen:
			newItem = new AnnotationMarkerPen(*(dynamic_cast<const AnnotationMarkerPen *>(item)));
			break;
		case Tools::MarkerRect:
			newItem = new AnnotationMarkerRect(*(dynamic_cast<const AnnotationMarkerRect *>(item)));
			break;
		case Tools::MarkerEllipse:
			newItem = new AnnotationMarkerEllipse(*(dynamic_cast<const AnnotationMarkerEllipse *>(item)));
			break;
		case Tools::Line:
			newItem = new AnnotationLine(*(dynamic_cast<const AnnotationLine *>(item)));
			break;
		case Tools::Ellipse:
			newItem = new AnnotationEllipse(*(dynamic_cast<const AnnotationEllipse *>(item)));
			break;
		case Tools::Rect:
			newItem = new AnnotationRect(*(dynamic_cast<const AnnotationRect *>(item)));
			break;
		case Tools::Arrow:
			newItem = new AnnotationArrow(*(dynamic_cast<const AnnotationArrow *>(item)));
			break;
		case Tools::DoubleArrow:
			newItem = new AnnotationDoubleArrow(*(dynamic_cast<const AnnotationArrow *>(item)));
			break;
		case Tools::Number:
			newItem = new AnnotationNumber(*(dynamic_cast<const AnnotationNumber *>(item)));
			mNumberManager->addItem(dynamic_cast<AnnotationNumber *>(newItem));
			break;
		case Tools::NumberPointer:
			newItem = new AnnotationNumberPointer(*(dynamic_cast<const AnnotationNumberPointer *>(item)));
			mNumberManager->addItem(dynamic_cast<AnnotationNumberPointer *>(newItem));
			break;
		case Tools::NumberArrow:
			newItem = new AnnotationNumberArrow(*(dynamic_cast<const AnnotationNumberArrow *>(item)));
			mNumberManager->addItem(dynamic_cast<AnnotationNumberArrow *>(newItem));
			break;
		case Tools::Text:
			newItem = new AnnotationText(*(dynamic_cast<const AnnotationText *>(item)));
			break;
		case Tools::TextPointer:
			newItem = new AnnotationTextPointer(*(dynamic_cast<const AnnotationTextPointer *>(item)));
			break;
		case Tools::TextArrow:
			newItem = new AnnotationTextArrow(*(dynamic_cast<const AnnotationTextArrow *>(item)));
			break;
		case Tools::Blur:
			newItem = new AnnotationBlur(*(dynamic_cast<const AnnotationBlur *>(item)));
			break;
		case Tools::Pixelate:
			newItem = new AnnotationPixelate(*(dynamic_cast<const AnnotationPixelate *>(item)));
			break;
		case Tools::Image:
			newItem = new AnnotationImage(*(dynamic_cast<const AnnotationImage *>(item)));
			break;
		case Tools::Sticker:
			newItem = new AnnotationSticker(*(dynamic_cast<const AnnotationSticker *>(item)));
			break;
		default:
			qCritical("Cannot create item for provided tool type.");
	}
	return newItem;
}

void AnnotationItemFactory::initItem(AbstractAnnotationItem *item)
{
	if(item != nullptr) {
		item->init();
		item->setZValue(mNextZValue++);
	}
}

void AnnotationItemFactory::numberSeedChanged(int newNumberSeed)
{
	mSettingsProvider->updateNumberToolSeed(newNumberSeed);
}

} // namespace kImageAnnotator
