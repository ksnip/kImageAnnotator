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

#ifndef KIMAGEANNOTATOR_PASTECOMMAND_H
#define KIMAGEANNOTATOR_PASTECOMMAND_H

#include <QUndoCommand>

#include "src/annotations/core/AnnotationArea.h"

namespace kImageAnnotator {

class PasteCommand : public QUndoCommand
{
public:
	PasteCommand(const QHash<AbstractAnnotationItem *, QPointF> &itemsWithOffset, const QPointF &position, AnnotationItemFactory *itemFactory, AnnotationArea *annotationArea);
	~PasteCommand();
	void undo() override;
	void redo() override;

private:
	AnnotationArea *mAnnotationArea;
	QVector<AbstractAnnotationItem*> mPastedItems;
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_PASTECOMMAND_H
