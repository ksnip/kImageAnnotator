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
#include <src/gui/annotator/AnnotationSettings.h>

#include "AnnotationItemFactory.h"
#include "AbstractSettingsProvider.h"
#include "AbstractToolChangeListener.h"
#include "AbstractItemSettingsChangeListener.h"
#include "src/annotations/modifiers/AnnotationItemModifier.h"
#include "src/annotations/modifiers/AnnotationItemArranger.h"
#include "src/annotations/misc/AnnotationItemClipboard.h"
#include "src/backend/Config.h"
#include "src/common/enum/ToolTypes.h"
#include "src/common/helper/CursorHelper.h"
#include "src/common/helper/KeyHelper.h"
#include "src/annotations/undo/UndoStack.h"
#include "src/annotations/undo/CropCommand.h"
#include "src/annotations/undo/ScaleCommand.h"
#include "src/annotations/undo/PasteCommand.h"
#include "src/annotations/undo/ChangePropertiesCommand.h"
#include "src/annotations/misc/AnnotationContextMenu.h"

namespace kImageAnnotator {

class AnnotationArea : public QGraphicsScene, public AbstractToolChangeListener, public AbstractItemSettingsChangeListener
{
    Q_OBJECT
public:
	explicit AnnotationArea(Config *config, AbstractSettingsProvider *settingsProvider);
    ~AnnotationArea() override;
    virtual void loadImage(const QPixmap &image);
    virtual void insertImageItem(const QPointF &position, const QPixmap &image);
    QImage image();
	QAction* undoAction();
	QAction* redoAction();
    virtual void addAnnotationItem(AbstractAnnotationItem *item);
    virtual void removeAnnotationItem(AbstractAnnotationItem *item);
    virtual void crop(const QRectF& rect);
    virtual void scale(const QSize& size);
    virtual void clearSelection();
    virtual void setUndoEnabled(bool enabled);
	virtual void toolChanged(ToolTypes toolType) override;
	void itemSettingsChanged();

public slots:
    virtual void update();

signals:
    void imageChanged() const;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent * event) override;

private:
    AnnotationItemFactory *mItemFactory;
    AnnotationPropertiesFactory *mPropertiesFactory;
    QGraphicsPixmapItem *mImage;
    AbstractAnnotationItem *mCurrentItem;
    AnnotationItemModifier *mItemModifier;
    AbstractSettingsProvider *mSettingsProvider;
    QList<AbstractAnnotationItem*> *mItems;
    KeyHelper *mKeyHelper;
    UndoStack *mUndoStack;
	AnnotationItemClipboard *mItemCopier;
	QAction *mUndoAction;
	QAction *mRedoAction;

    void addItemAtPosition(const QPointF& position);
    void addPointToCurrentItem(const QPointF& position);
	void resetAnnotationArea();
	void removeAllItems();
	void replaceBackgroundImage(const QPixmap &image);

private slots:
    void deleteSelectedItems();
	void pasteCopiedItems(const QPointF &position);
    void enableEditing();
    EditableItem* selectedEditableItem() const;
	void itemsSelected(const QList<AbstractAnnotationItem *> &items) const;
};

} // namespace kImageAnnotator

#endif // KIMAGEANNOTATOR_ANNOTATIONAREA_H
