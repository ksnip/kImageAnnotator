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

#ifndef KIMAGEANNOTATOR_ANNOTATIONMULTIITEMRESIZER_H
#define KIMAGEANNOTATOR_ANNOTATIONMULTIITEMRESIZER_H

#include <QGraphicsItemGroup>
#include <QGraphicsScene>

#include "AnnotationItemResizer.h"

namespace kImageAnnotator {

class AnnotationMultiItemResizer : public QObject, public QGraphicsItemGroup
{
Q_OBJECT
public:
    explicit AnnotationMultiItemResizer();
    ~AnnotationMultiItemResizer() override = default;
    QRectF boundingRect() const override;
    void attachTo(QList<AbstractAnnotationItem *> items);
    void detach();
    void grabHandle(const QPointF &pos);
    void moveHandle(const QPointF &pos);
    void releaseHandle();
    bool isResizing() const;
    void refresh();
    void update();
    bool hasItemsAttached() const;
    Qt::CursorShape cursorForPos(const QPointF &pos);
    Qt::CursorShape cursorForCurrentHandle();
    void hideCurrentResizer();
    void showCurrentResizer();

signals:
    void newCommand(ResizeCommand *resize) const;

private:
    QHash<AbstractAnnotationItem *, AnnotationItemResizer *> mItemToResizer;
    AnnotationItemResizer *mCurrentResizer;

    AnnotationItemResizer *getResizerForItem(AbstractAnnotationItem *item);
    void showResizer(AnnotationItemResizer *resizer);
    void hideResizer(QGraphicsItem *resizer);
    AnnotationItemResizer *castToResizer(QGraphicsItem *item) const;
};

} // namespace kImageAnnotator

#endif // KIMAGEANNOTATOR_ANNOTATIONMULTIITEMRESIZER_H
