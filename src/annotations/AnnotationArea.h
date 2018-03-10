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

#ifndef ANNOTATIONAREA_H
#define ANNOTATIONAREA_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QPainter>

#include "annotationItems/AnnotationItemFactory.h"
#include "annotationItems/AnnotationItemModifier.h"
#include "backend/Config.h"
#include "common/enum/ToolTypes.h"

class AnnotationArea : public QGraphicsScene
{
    Q_OBJECT
public:
    AnnotationArea();
    ~AnnotationArea();

    void setBackgroundImage(const QPixmap& image);
    QImage exportAsImage();

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;

private:
    AnnotationItemFactory*  mItemFactory;
    QGraphicsPixmapItem*    mBackgroundImage;
    AbstractAnnotationItem* mCurrentItem;
    AnnotationItemModifier* mItemModifier;
    Config*                 mConfig;

    void addItemAtPosition(const QPointF& position);
    void addPointToCurrentItem(const QPointF& position);
    AbstractAnnotationItem* findItemAt(const QPointF& point) const;
    void deleteSelectedItem();
    void clearSelection();
};

#endif // ANNOTATIONAREA_H
