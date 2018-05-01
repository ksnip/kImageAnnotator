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
#include <QMenu>
#include <QUndoStack>

#include <KLocalizedString>

#include "AnnotationItemFactory.h"
#include "modifiers/AnnotationItemModifier.h"
#include "modifiers/AnnotationItemArranger.h"
#include "../backend/Config.h"
#include "../common/enum/ToolTypes.h"
#include "../common/helper/CursorHelper.h"
#include "../common/helper/KeyHelper.h"
#include "undoRedo/AddCommand.h"
#include "undoRedo/DeleteCommand.h"

class AnnotationArea : public QGraphicsScene
{
    Q_OBJECT
public:
    AnnotationArea();
    ~AnnotationArea();
    void setBackgroundImage(const QPixmap& image);
    QImage exportAsImage();
    virtual void addAnnotationItem(AbstractAnnotationItem *item);
    virtual void removeAnnotationItem(AbstractAnnotationItem *item);
    virtual void update();

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;
    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent * event) override;

private:
    AnnotationItemFactory*          mItemFactory;
    QGraphicsPixmapItem*            mBackgroundImage;
    AbstractAnnotationItem*         mCurrentItem;
    AnnotationItemModifier*         mItemModifier;
    Config*                         mConfig;
    QList<AbstractAnnotationItem*> *mItems;
    KeyHelper                      *mKeyHelper;
    QUndoStack                     *mUndoStack;

    void addItemAtPosition(const QPointF& position);
    void addPointToCurrentItem(const QPointF& position);
    void setCursorForTool(ToolTypes tool);

private slots:
    void deleteSelectedItems();
};

#endif // ANNOTATIONAREA_H
