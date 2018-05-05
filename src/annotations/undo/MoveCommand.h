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

#ifndef KIMAGEANNOTATOR_MOVECOMMAND_H
#define KIMAGEANNOTATOR_MOVECOMMAND_H

#include <QUndoCommand>

#include "../items/AbstractAnnotationItem.h"

class MoveCommand : public QUndoCommand
{
public:
    enum
    {
        Id = 1234
    };

    explicit MoveCommand(QHash<AbstractAnnotationItem *, QPointF> itemToNewPos);
    ~MoveCommand() = default;
    virtual void undo() override;
    virtual void redo() override;
    virtual bool mergeWith(const QUndoCommand *command) override;
    virtual int id() const override;

private:
    QHash<AbstractAnnotationItem *, QPointF> mOriginalPos;
    QHash<AbstractAnnotationItem *, QPointF> mNewPos;

    void moveItems(QHash<AbstractAnnotationItem *, QPointF> &itemToPos) const;
};

#endif //KIMAGEANNOTATOR_MOVECOMMAND_H
