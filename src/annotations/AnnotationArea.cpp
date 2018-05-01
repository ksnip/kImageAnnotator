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

#include "AnnotationArea.h"

AnnotationArea::AnnotationArea()
{
    mConfig = Config::instance();
    mItemFactory = new AnnotationItemFactory();
    mBackgroundImage = nullptr;
    mCurrentItem = nullptr;
    mItems = new QList<AbstractAnnotationItem *>();
    mItemModifier = new AnnotationItemModifier();
    addItem(mItemModifier);
    mKeyHelper = new KeyHelper();
    mUndoStack = new QUndoStack();

    connect(mKeyHelper, &KeyHelper::deleteReleased, this, &AnnotationArea::deleteSelectedItems);
    connect(mKeyHelper, &KeyHelper::escapeReleased, mItemModifier, &AnnotationItemModifier::clearSelection);

    connect(mConfig, &Config::toolChanged, this, &AnnotationArea::setCursorForTool);

    // TODO cleanup
    auto undoAction = mUndoStack->createUndoAction(this);
    auto redoAction = mUndoStack->createRedoAction(this);
    connect(mKeyHelper, &KeyHelper::undoPressed, undoAction, &QAction::trigger);
    connect(mKeyHelper, &KeyHelper::redoPressed, redoAction, &QAction::trigger);
}

AnnotationArea::~AnnotationArea()
{
    delete mItemFactory;
    delete mItems;
    delete mItemModifier;
    delete mKeyHelper;
    delete mUndoStack;
}

void AnnotationArea::setBackgroundImage(const QPixmap &image)
{
    if (image.isNull()) {
        return;
    }

    mBackgroundImage = addPixmap(image);
    mItemFactory->reset();
}

QImage AnnotationArea::exportAsImage()
{
    if (mBackgroundImage == nullptr) {
        return QImage();
    }

    mItemModifier->clearSelection();

    QImage image(sceneRect().size().toSize(), QImage::Format_ARGB32);
    image.fill(Qt::transparent);

    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);
    render(&painter);
    return image;
}

void AnnotationArea::addAnnotationItem(AbstractAnnotationItem *item)
{
    mItems->prepend(item);
    addItem(item);
}

void AnnotationArea::removeAnnotationItem(AbstractAnnotationItem *item)
{
    removeItem(item);
    mItems->removeOne(item);
}

void AnnotationArea::update()
{
    mItemModifier->updateSelection();
    QGraphicsScene::update();
}

void AnnotationArea::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if (mConfig->selectedTool() == ToolTypes::Select) {
            mItemModifier->handleMousePress(event->scenePos(), mItems, mKeyHelper->isControlPressed());
        } else {
            mItemModifier->clearSelection();
            addItemAtPosition(event->scenePos());
        }
    }

    QGraphicsScene::mousePressEvent(event);
}

void AnnotationArea::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton) {
        if (mCurrentItem) {
            addPointToCurrentItem(event->scenePos());
        } else {
            mItemModifier->handleMouseMove(event->scenePos());
        }
    }

    QGraphicsScene::mouseMoveEvent(event);
}

void AnnotationArea::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if (mConfig->selectedTool() == ToolTypes::Select) {
            mItemModifier->handleMouseRelease(mItems);
        } else {
            mCurrentItem = nullptr;
        }
    }

    QGraphicsScene::mouseReleaseEvent(event);
}

void AnnotationArea::keyPressEvent(QKeyEvent *event)
{
    mKeyHelper->keyPress(event);
    QGraphicsScene::keyPressEvent(event);
}

void AnnotationArea::keyReleaseEvent(QKeyEvent *event)
{
    mKeyHelper->keyRelease(event);
    QGraphicsScene::keyReleaseEvent(event);
}

void AnnotationArea::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    mItemModifier->handleSelectionAt(event->scenePos(), mItems, mKeyHelper->isControlPressed());
    auto selectedItems = mItemModifier->selectedItems();

    if (selectedItems.isEmpty()) {
        return;
    }

    AnnotationItemArranger itemArranger(selectedItems, mItems);

    QMenu contextMenu;
    auto arrangeMenu = contextMenu.addMenu(i18n("Arrange"));
    arrangeMenu->addAction(i18n("Bring to Front"), &itemArranger, &AnnotationItemArranger::bringToFront);
    arrangeMenu->addAction(i18n("Bring Forward"), &itemArranger, &AnnotationItemArranger::bringForward);
    arrangeMenu->addAction(i18n("Send Backward"), &itemArranger, &AnnotationItemArranger::sendBackward);
    arrangeMenu->addAction(i18n("Send to Back"), &itemArranger, &AnnotationItemArranger::sendToBack);
    contextMenu.addSeparator();
    contextMenu.addAction(i18n("Delete"), this, &AnnotationArea::deleteSelectedItems);

    contextMenu.exec(event->screenPos());
}

void AnnotationArea::addItemAtPosition(const QPointF &position)
{
    mCurrentItem = mItemFactory->createItem(position, mConfig->selectedTool());
    mUndoStack->push(new AddCommand(mCurrentItem, this));
}

void AnnotationArea::addPointToCurrentItem(const QPointF &position)
{
    mCurrentItem->addPoint(position, mKeyHelper->isControlPressed());
}

void AnnotationArea::setCursorForTool(ToolTypes tool)
{
    for (auto item : *mItems) {
        if (tool == ToolTypes::Select) {
            item->setCursor(CursorHelper::movableCursor());
        } else {
            item->unsetCursor();
        }
    }
}

void AnnotationArea::deleteSelectedItems()
{
    auto selectedItems = mItemModifier->selectedItems();
    mItemModifier->clearSelection();
    mUndoStack->push(new DeleteCommand(selectedItems, this));
}