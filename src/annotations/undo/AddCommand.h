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

#ifndef KIMAGEANNOTATOR_ADDCOMMAND_H
#define KIMAGEANNOTATOR_ADDCOMMAND_H

#include <QUndoCommand>

#include "src/annotations/items/AbstractAnnotationItem.h"
#include "src/annotations/core/AnnotationArea.h"

class AnnotationArea;

class AddCommand : public QUndoCommand
{
public:
    AddCommand(AbstractAnnotationItem *item, AnnotationArea *annotationArea);
    ~AddCommand();
    virtual void undo() override;
    virtual void redo() override;

private:
    AbstractAnnotationItem *mItem;
    AnnotationArea         *mAnnotationArea;
};

#endif //KIMAGEANNOTATOR_ADDCOMMAND_H
