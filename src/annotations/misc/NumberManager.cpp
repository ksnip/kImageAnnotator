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

#include "NumberManager.h"

namespace kImageAnnotator {

void kImageAnnotator::NumberManager::addItem(kImageAnnotator::AnnotationNumber *item)
{
	Q_ASSERT(item != nullptr);

	connect(item, &AnnotationNumber::visibleChanged, this, &NumberManager::updateNumbers);
	mItems.append(item);
	updateNumbers();
}

void NumberManager::reset()
{
	mItems.clear();
}

void NumberManager::updateNumbers()
{
	auto number = 1;
	for (auto item : mItems) {
		if (item->isVisible()) {
			item->setNumber(number++);
		} else {
			item->setNumber(-1);
		}
	}
}

} // namespace kImageAnnotator
