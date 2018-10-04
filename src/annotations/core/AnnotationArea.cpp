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

namespace kImageAnnotator {

AnnotationArea::AnnotationArea(Config *config) : mImage(nullptr), mCurrentItem(nullptr)
{
	Q_ASSERT(config != nullptr);

	mConfig = config;
	mItemFactory = new AnnotationItemFactory(config);
	mItems = new QList<AbstractAnnotationItem *>();
	mKeyHelper = new KeyHelper();
	mUndoStack = new UndoStack();
	mItemModifier = new AnnotationItemModifier();
	addItem(mItemModifier);
	mItemCopier = new AnnotationItemClipboard(mItemModifier);

	connect(mItemModifier, &AnnotationItemModifier::newCommand, mUndoStack, &UndoStack::push);
	connect(mUndoStack, &UndoStack::indexChanged, this, &AnnotationArea::update);
	connect(mKeyHelper, &KeyHelper::deleteReleased, this, &AnnotationArea::deleteSelectedItems);
	connect(mKeyHelper, &KeyHelper::escapeReleased, mItemModifier, &AnnotationItemModifier::clear);
	connect(mConfig, &Config::toolChanged, this, &AnnotationArea::setItemDecorationForTool);

	connect(mKeyHelper, &KeyHelper::undoPressed, mUndoStack, &UndoStack::undo);
	connect(mKeyHelper, &KeyHelper::redoPressed, mUndoStack, &UndoStack::redo);
}

AnnotationArea::~AnnotationArea()
{
	delete mItemFactory;
	delete mItems;
	delete mKeyHelper;
	delete mUndoStack;
}

void AnnotationArea::loadImage(const QPixmap &image)
{
	if (image.isNull()) {
		return;
	}

	resetAnnotationArea();
	replaceBackgroundImage(image);
}

void AnnotationArea::replaceBackgroundImage(const QPixmap &image)
{
	delete mImage;
	mImage = addPixmap(image);
	setSceneRect(image.rect());
}

QImage AnnotationArea::image()
{
	if (mImage == nullptr) {
		return QImage();
	}

	mItemModifier->clear();

	QImage image(sceneRect().size().toSize(), QImage::Format_ARGB32);
	image.fill(Qt::transparent);

	QPainter painter(&image);
	painter.setRenderHint(QPainter::Antialiasing);
	render(&painter);
	return image;
}

QAction *AnnotationArea::undoAction()
{
	return mUndoStack->createUndoAction(this);
}

QAction *AnnotationArea::redoAction()
{
	return mUndoStack->createRedoAction(this);
}

void AnnotationArea::addAnnotationItem(AbstractAnnotationItem *item)
{
	mItems->prepend(item);
	addItem(item);
	emit imageChanged();
}

void AnnotationArea::removeAnnotationItem(AbstractAnnotationItem *item)
{
	removeItem(item);
	mItems->removeOne(item);
	emit imageChanged();
}

void AnnotationArea::crop(const QRectF &rect)
{
	mUndoStack->push(new CropCommand(mImage, rect, this));
	emit imageChanged();
}

void AnnotationArea::scale(const QSize &size)
{
	mUndoStack->push(new ScaleCommand(mImage, size, this));
	emit imageChanged();
}

void AnnotationArea::clearSelection()
{
	mItemModifier->clear();
	QGraphicsScene::clearSelection();
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
			mItemModifier->clear();
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
			mCurrentItem->finish();
			mCurrentItem = nullptr;
		}
	}

	emit imageChanged();
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

	AnnotationContextMenu contextMenu;
	contextMenu.setOverItem(!selectedItems.isEmpty());
	contextMenu.setPastEnabled(!mItemCopier->isEmpty());
	AnnotationItemArranger itemArranger(selectedItems, mItems);
	connect(&itemArranger, &AnnotationItemArranger::newCommand, mUndoStack, &UndoStack::push);
	connect(&contextMenu, &AnnotationContextMenu::bringToFront, &itemArranger, &AnnotationItemArranger::bringToFront);
	connect(&contextMenu, &AnnotationContextMenu::bringForward, &itemArranger, &AnnotationItemArranger::bringForward);
	connect(&contextMenu, &AnnotationContextMenu::sendBackward, &itemArranger, &AnnotationItemArranger::sendBackward);
	connect(&contextMenu, &AnnotationContextMenu::sendToBack, &itemArranger, &AnnotationItemArranger::sendToBack);
	connect(&contextMenu, &AnnotationContextMenu::copy, mItemCopier, &AnnotationItemClipboard::copyItems);
	connect(&contextMenu, &AnnotationContextMenu::paste, this, &AnnotationArea::pasteCopiedItems);
	connect(&contextMenu, &AnnotationContextMenu::erase, this, &AnnotationArea::deleteSelectedItems);

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

void AnnotationArea::setItemDecorationForTool(ToolTypes tool)
{
	for (auto item : *mItems) {
		if (tool == ToolTypes::Select) {
			item->setCursor(CursorHelper::movableCursor());
		} else {
			item->unsetCursor();
		}
	}
}

void AnnotationArea::resetAnnotationArea()
{
	removeAllItems();
	mItemModifier->clear();
	mItemCopier->clear();
	mUndoStack->clear();
	mItemFactory->reset();
}

void AnnotationArea::removeAllItems()
{
	for (auto item : *mItems) {
		removeAnnotationItem(item);
	}
}

void AnnotationArea::deleteSelectedItems()
{
	auto selectedItems = mItemModifier->selectedItems();
	mItemModifier->clear();
	mUndoStack->push(new DeleteCommand(selectedItems, this));
}

void AnnotationArea::pasteCopiedItems(const QPointF &position)
{
	auto copiedItems = mItemCopier->copiedItemsWithOffset();
	mUndoStack->push(new PasteCommand(copiedItems, position, this));
}

} // namespace kImageAnnotator
