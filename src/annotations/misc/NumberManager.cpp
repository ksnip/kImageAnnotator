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

#include "NumberManager.h"

namespace kImageAnnotator {

NumberManager::NumberManager() :
	mFirstNumber(1)
{
}

void kImageAnnotator::NumberManager::addItem(AnnotationNumber *item)
{
	addItemInner(item);
}

void kImageAnnotator::NumberManager::addItem(AnnotationNumberPointer *item)
{
	addItemInner(item);
}

void NumberManager::addItemInner(AbstractAnnotationItem *item)
{
	Q_ASSERT(item != nullptr);

	connect(item, &AbstractAnnotationItem::visibleChanged, this, &NumberManager::updateNumbers);
	mItems.append(item);
	updateNumbers();
}

void NumberManager::reset()
{
	mItems.clear();
}

void NumberManager::updateNumbers()
{
	auto number = mFirstNumber;
	for (auto item : mItems) {
		if (item->isVisible()) {
			auto numberItem = dynamic_cast<BaseAnnotationNumber *>(item);
			numberItem->setNumber(number++);
		}
	}
}

void NumberManager::firstBadgeNumberChanged(int number)
{
	mFirstNumber = number;
	updateNumbers();
}

} // namespace kImageAnnotator
