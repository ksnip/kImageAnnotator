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

#include "AnnotationItemCopier.h"

namespace kImageAnnotator {

AnnotationItemCopier::AnnotationItemCopier(const AnnotationItemModifier *itemModifier, const AnnotationItemFactory *annotationItemFactory)
{
	Q_ASSERT(itemModifier != nullptr);
	Q_ASSERT(annotationItemFactory != nullptr);

	mItemModifier = itemModifier;
	mItemFactory = annotationItemFactory;
}

bool AnnotationItemCopier::isEmpty() const
{
	return mCopiedItems.count() == 0;
}

void AnnotationItemCopier::copyItems(const QPointF &position)
{
	clear();
	mCopiedItems = mItemModifier->selectedItems();
}

void AnnotationItemCopier::pasteItems(const QPointF &position)
{

}

void AnnotationItemCopier::clear()
{
	mCopiedItems.clear();
}

} // namespace kImageAnnotator
