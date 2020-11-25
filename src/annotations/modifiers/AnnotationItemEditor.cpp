/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
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

#include "AnnotationItemEditor.h"
#include "src/annotations/items/interfaces/EditableItem.h"

namespace kImageAnnotator {

AnnotationItemEditor::AnnotationItemEditor()
	: mCurrentEditItem(nullptr)
{
}

void AnnotationItemEditor::handleEditAt(const QPointF &pos, QList<AbstractAnnotationItem *> *items)
{
	auto item = findItemAt(pos, items);
	mCurrentEditItem = dynamic_cast<EditableItem *>(item);
}

bool AnnotationItemEditor::isEditing() const
{
	return (mCurrentEditItem != nullptr);
}

void AnnotationItemEditor::clear()
{
	mCurrentEditItem = nullptr;
}

AbstractAnnotationItem *AnnotationItemEditor::findItemAt(const QPointF &position, QList<AbstractAnnotationItem *> *items)
{
	QRectF rect(position - QPointF(2, 2), QSize(4, 4));

	for (auto item : *items) {
		if (item->intersects(rect)) {
			return item;
		}
	}
	return nullptr;
}

} // namespace kImageAnnotator
