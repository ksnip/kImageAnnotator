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

#include "AnnotationItemClipboard.h"

namespace kImageAnnotator {

bool AnnotationItemClipboard::isEmpty() const
{
	return mCopiedItemsToOffset.count() == 0;
}

bool AnnotationItemClipboard::isNotEmpty() const
{
	return !isEmpty();
}

void AnnotationItemClipboard::copyItems(const QPointF &position, const AnnotationItemModifier *itemModifier)
{
	clear();

	for (auto item : itemModifier->selectedItems()) {
		mCopiedItemsToOffset[item] = item->position() - position;
	}
}

QHash<AbstractAnnotationItem *, QPointF> AnnotationItemClipboard::copiedItemsWithOffset() const
{
	return mCopiedItemsToOffset;
}

void AnnotationItemClipboard::clear()
{
	mCopiedItemsToOffset.clear();
}

} // namespace kImageAnnotator
