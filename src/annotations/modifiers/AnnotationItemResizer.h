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

#ifndef ANNOTATIONITEMRESIZER_H
#define ANNOTATIONITEMRESIZER_H

#include <QGraphicsWidget>
#include <QGraphicsSceneMouseEvent>

#include "ResizeHandles.h"
#include "../items/AbstractAnnotationLine.h"
#include "../items/AbstractAnnotationRect.h"

class AnnotationItemResizer : public QGraphicsWidget
{
public:
    AnnotationItemResizer();
    ~AnnotationItemResizer();
    virtual QRectF boundingRect() const override;
    void attachTo(AbstractAnnotationItem* item);
    void detach();
    AbstractAnnotationItem* attachedItem() const;
    void grabHandle(const QPointF& pos);
    void moveHandle(const QPointF& pos);
    void releaseHandle();
    bool isResizing() const;

protected:
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0) override;

private:
    ResizeHandles*          mResizeHandles;
    AbstractAnnotationItem* mAnnotationItem;
    int                     mResizeHandleSize;
    int                     mCurrentControlPoint;
    QPointF                 mClickOffset;
};

#endif // ANNOTATIONITEMRESIZER_H
