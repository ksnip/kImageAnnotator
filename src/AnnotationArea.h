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
#include <QPainter>

#include "annotationItems/AnnotationItemFactory.h"
#include "annotationItems/AnnotationItemModifier.h"
#include "AnnotationToolTypes.h"

class AnnotationArea : public QGraphicsScene
{
    Q_OBJECT
public:
    AnnotationArea(AnnotationItemFactory* itemFactory);
    ~AnnotationArea();

    void setBackgroundImage(const QPixmap& image);
    QImage exportAsImage();

public slots:
    void setToolType(AnnotationToolTypes toolType);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

private:
    AnnotationItemFactory*  mItemFactory;
    QGraphicsPixmapItem*    mBackgroundImage;
    AbstractAnnotationItem* mCurrentItem;
    AnnotationItemModifier* mItemModifier;
    AnnotationToolTypes     mSelectedToolType;

    void addItemAtPosition(const QPointF& position);
    void addPointToCurrentItem(const QPointF& position);
    AbstractAnnotationItem* findItemAt(const QPointF& point) const;
};

#endif // ANNOTATIONAREA_H
