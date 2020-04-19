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

#include "AnnotationContextMenu.h"

namespace kImageAnnotator {

AnnotationContextMenu::AnnotationContextMenu()
{
	mArrangeMenu = addMenu(tr("Arrange"));
	mArrangeMenu->addAction(tr("Bring to Front"), this, &AnnotationContextMenu::bringToFront);
	mArrangeMenu->addAction(tr("Bring Forward"), this, &AnnotationContextMenu::bringForward);
	mArrangeMenu->addAction(tr("Send Backward"), this, &AnnotationContextMenu::sendBackward);
	mArrangeMenu->addAction(tr("Send to Back"), this, &AnnotationContextMenu::sendToBack);
	addSeparator();
	mSelectThisAction = addAction(tr("Select This"));
	addSeparator();
	mCopyAction = addAction(tr("Copy"));
	mPastAction = addAction(tr("Paste"));
	addSeparator();
    mEditAction = addAction(tr("Edit"), this, &AnnotationContextMenu::edit);
	mDeleteAction = addAction(tr("Delete"), this, &AnnotationContextMenu::erase);
}

void AnnotationContextMenu::setOverItem(bool isOverItem)
{
	mArrangeMenu->setEnabled(isOverItem);
	mCopyAction->setEnabled(isOverItem);
	mDeleteAction->setEnabled(isOverItem);
	mSelectThisAction->setEnabled(isOverItem);
}

void AnnotationContextMenu::setPastEnabled(bool enabled)
{
	mPastAction->setEnabled(enabled);
}

void AnnotationContextMenu::setEditVisible(bool enabled)
{
    mEditAction->setVisible(enabled);
}

void AnnotationContextMenu::exec(const QPointF &position)
{
	auto selectedAction = QMenu::exec(position.toPoint());

	if (selectedAction && selectedAction == mPastAction) {
		emit paste(position);
	}

	if (selectedAction && selectedAction == mCopyAction) {
		emit copy(position);
	}
}

} // namespace kImageAnnotator
