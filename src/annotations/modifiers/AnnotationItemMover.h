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

#ifndef KIMAGEANNOTATOR_ANNOTATIONITEMMOVER_H
#define KIMAGEANNOTATOR_ANNOTATIONITEMMOVER_H

#include <QObject>
#include <QHash>

#include "src/annotations/items/AbstractAnnotationItem.h"
#include "src/annotations/undo/MoveCommand.h"
#include "src/common/helper/CursorHelper.h"

namespace kImageAnnotator {

class AnnotationItemMover : public QObject
{
Q_OBJECT
public:
    explicit AnnotationItemMover() = default;
    ~AnnotationItemMover() override = default;
    void setOffset(const QPointF &pos, const QList<AbstractAnnotationItem *> &selectedItems);
    void moveItems(const QPointF &pos);
    void clearOffset();
    bool isMoving();
    Qt::CursorShape cursor();

signals:
    void newCommand(MoveCommand *move) const;

private:
    QHash<AbstractAnnotationItem *, QPointF> mItemToOffset;
};

} // namespace kImageAnnotator

#endif // KIMAGEANNOTATOR_ANNOTATIONITEMMOVER_H
