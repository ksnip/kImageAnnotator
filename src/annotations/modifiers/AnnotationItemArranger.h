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

#ifndef KIMAGEANNOTATOR_ANNOTATIONITEMARRANGER_H
#define KIMAGEANNOTATOR_ANNOTATIONITEMARRANGER_H

#include <QObject>

#include "src/annotations/items/AbstractAnnotationItem.h"
#include "src/annotations/undo/ArrangeCommand.h"
#include "src/common/helper/ItemHelper.h"

namespace kImageAnnotator {

class AnnotationItemArranger : public QObject
{
Q_OBJECT
public:
    explicit AnnotationItemArranger(const QList<AbstractAnnotationItem *> selectedItems, QList<AbstractAnnotationItem *> *items);
    ~AnnotationItemArranger() = default;

signals:
    void newCommand(ArrangeCommand *arrange) const;

public slots:
    void bringToFront();
    void bringForward();
    void sendBackward();
    void sendToBack();

private:
    QList<AbstractAnnotationItem *> mSelectedItems;
    QList<AbstractAnnotationItem *> *mItems;

    void moveForward(bool toFront);
    void moveBackward(bool toBack);
    void createAndEmitArrangeCommand(const QList<QPair<AbstractAnnotationItem *, AbstractAnnotationItem *>> &itemToSwap) const;
};

} // namespace kImageAnnotator

#endif // KIMAGEANNOTATOR_ANNOTATIONITEMARRANGER_H
