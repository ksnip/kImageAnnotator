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

#ifndef KIMAGEANNOTATOR_ANNOTATIONAREA_H
#define KIMAGEANNOTATOR_ANNOTATIONAREA_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QPainter>
#include <QMenu>
#include <QUndoStack>

#include "AnnotationItemFactory.h"
#include "src/annotations/modifiers/AnnotationItemModifier.h"
#include "src/annotations//modifiers/AnnotationItemArranger.h"
#include "src/backend/Config.h"
#include "src/common/enum/ToolTypes.h"
#include "src/common/helper/CursorHelper.h"
#include "src/common/helper/KeyHelper.h"
#include "src/annotations/undo/UndoStack.h"

namespace kImageAnnotator {

class AnnotationArea : public QGraphicsScene
{
    Q_OBJECT
public:
    AnnotationArea();
    ~AnnotationArea() override;
    void loadImage(const QPixmap &image);
    QImage image();
	QAction* undoAction();
	QAction* redoAction();
    virtual void addAnnotationItem(AbstractAnnotationItem *item);
    virtual void removeAnnotationItem(AbstractAnnotationItem *item);

public slots:
    virtual void update();

signals:
    void imageChanged() const;

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;
    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent * event) override;

private:
    AnnotationItemFactory*          mItemFactory;
    QGraphicsPixmapItem*            mImage;
    AbstractAnnotationItem*         mCurrentItem;
    AnnotationItemModifier*         mItemModifier;
    Config*                         mConfig;
    QList<AbstractAnnotationItem*> *mItems;
    KeyHelper                      *mKeyHelper;
    UndoStack                      *mUndoStack;

    void addItemAtPosition(const QPointF& position);
    void addPointToCurrentItem(const QPointF& position);
    void setItemDecorationForTool(ToolTypes tool);
	void resetAnnotationArea();
	void removeAllItems();
	void replaceBackgroundImage(const QPixmap &image);

private slots:
    void deleteSelectedItems();
};

} // namespace kImageAnnotator

#endif // KIMAGEANNOTATOR_ANNOTATIONAREA_H
