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

#include "PasteCommand.h"

namespace kImageAnnotator {

PasteCommand::PasteCommand(const QHash<kImageAnnotator::AbstractAnnotationItem *, QPointF> &itemsWithOffset,
                           const QPointF &position,
                           AnnotationItemFactory *itemFactory,
                           kImageAnnotator::AnnotationArea *annotationArea)
{
	Q_ASSERT(annotationArea != nullptr);
	Q_ASSERT(itemFactory != nullptr);

	mAnnotationArea = annotationArea;
	mItemFactory = itemFactory;
	for (auto item : itemsWithOffset.keys()) {
		auto pastedItem = itemFactory->clone(item);
		pastedItem->setPosition(position + itemsWithOffset[item]);
		mPastedItems.append(pastedItem);
	}
}

PasteCommand::~PasteCommand()
{
	// Deleting with the annotation area
}

void PasteCommand::undo()
{
	for (auto item : mPastedItems) {
		mAnnotationArea->removeAnnotationItem(item);
		item->hide();
	}
}

void PasteCommand::redo()
{
	for (auto item : mPastedItems) {
		mAnnotationArea->addAnnotationItem(item);
		item->show();
	}
}

} // namespace kImageAnnotator
