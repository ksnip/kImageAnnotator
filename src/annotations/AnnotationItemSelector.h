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

#ifndef ANNOTATIONITEMSELECTOR_H
#define ANNOTATIONITEMSELECTOR_H

#include <QGraphicsWidget>
#include <QGraphicsSceneMouseEvent>

#include "items/AbstractAnnotationItem.h"

class AnnotationItemSelector : public QGraphicsWidget
{
public:
    explicit AnnotationItemSelector();
    ~AnnotationItemSelector() = default;
    virtual QRectF boundingRect() const override;

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0) override;

private:
    QRectF mSelectionRect;

    void initSelectionRectAt(const QPointF& position);
    void updateSelectionRect(const QPointF& position);
};

#endif // ANNOTATIONITEMSELECTOR_H
