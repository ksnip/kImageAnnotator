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

#include "AnnotationArea.h"

#include "src/annotations/core/AbstractCamera.h"

namespace kImageAnnotator {

AnnotationArea::AnnotationArea(Config *config, AbstractSettingsProvider *settingsProvider, IDevicePixelRatioScaler *devicePixelRatioScaler, AbstractCamera *camera) :
	mUndoStack(new UndoStack),
	mImage(nullptr),
	mCurrentItem(nullptr),
	mUndoAction(nullptr),
	mRedoAction(nullptr),
	mKeyHelper(new KeyHelper),
	mSettingsProvider(settingsProvider),
	mItemModifier(new AnnotationItemModifier(camera)),
	mPropertiesFactory(new AnnotationPropertiesFactory(config, mSettingsProvider)),
	mItemFactory(new AnnotationItemFactory(mPropertiesFactory, mSettingsProvider)),
	mItems(new QList<AbstractAnnotationItem *>()),
	mItemCopier(new AnnotationItemClipboard(mItemModifier)),
	mDevicePixelRatioScaler(devicePixelRatioScaler)
{
	Q_ASSERT(mSettingsProvider != nullptr);

	addItem(mItemModifier);

	connect(mItemModifier, &AnnotationItemModifier::newCommand, mUndoStack, &UndoStack::push);
	connect(mItemModifier, &AnnotationItemModifier::itemsSelected, this, &AnnotationArea::itemsSelected);
	connect(mItemModifier, &AnnotationItemModifier::itemModified, this, &AnnotationArea::imageChanged);
	connect(mUndoStack, &UndoStack::indexChanged, this, &AnnotationArea::update);
	connect(mKeyHelper, &KeyHelper::deleteReleased, this, &AnnotationArea::deleteSelectedItems);
	connect(mKeyHelper, &KeyHelper::escapeReleased, mItemModifier, &AnnotationItemModifier::clear);

	connect(mKeyHelper, &KeyHelper::undoPressed, mUndoStack, &UndoStack::undo);
	connect(mKeyHelper, &KeyHelper::redoPressed, mUndoStack, &UndoStack::redo);

	connect(&mKeyListener, &KeyEventListener::keyPressed, mKeyHelper, &KeyHelper::keyPress);
	connect(&mKeyListener, &KeyEventListener::keyReleased, mKeyHelper, &KeyHelper::keyRelease);
}

AnnotationArea::~AnnotationArea()
{
	delete mPropertiesFactory;
	delete mItemFactory;
	delete mItems;
	delete mKeyHelper;
	delete mUndoStack;
	delete mItemModifier;
	delete mItemCopier;
}

void AnnotationArea::loadImage(const QPixmap &image)
{
	if (image.isNull()) {
		return;
	}

	resetAnnotationArea();
	replaceBackgroundImage(image);
}

void AnnotationArea::insertImageItem(const QPointF &position, const QPixmap &image)
{
    auto imageItem = mItemFactory->create(position, image);
    mUndoStack->push(new AddCommand(imageItem, this));
	toolChanged(mSettingsProvider->toolType());
}

void AnnotationArea::replaceBackgroundImage(const QPixmap &image)
{
	mImage = QSharedPointer<QGraphicsPixmapItem>(addPixmap(image));
	setSceneRect(mImage->boundingRect());
}

QImage AnnotationArea::image()
{
	if (mImage == nullptr) {
		return QImage();
	}

	mItemModifier->clear();

	setSceneRect(itemsBoundingRect()); // Cover all items

	auto scaleFactor = mDevicePixelRatioScaler->scaleFactor();
	QImage image(sceneRect().size().toSize() * scaleFactor, QImage::Format_ARGB32_Premultiplied);
	image.fill(Qt::white);
	image.setDevicePixelRatio(scaleFactor);

	QPainter painter(&image);
	painter.setRenderHint(QPainter::Antialiasing);
	render(&painter);

	setSceneRect(mImage->boundingRect()); // Reset scene rect

	return image;
}

QAction *AnnotationArea::undoAction()
{
	if(mUndoAction == nullptr) {
		mUndoAction = mUndoStack->createUndoAction(this);
	}
	return mUndoAction;
}

QAction *AnnotationArea::redoAction()
{
	if(mRedoAction == nullptr) {
		mRedoAction = mUndoStack->createRedoAction(this);
	}
	return mRedoAction;
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
	auto scaledRect = mDevicePixelRatioScaler->scale(rect);
	mUndoStack->push(new CropCommand(mImage.data(), scaledRect, this));
	emit imageChanged();
}

void AnnotationArea::scale(const QSize &size)
{
	mUndoStack->push(new ScaleCommand(mImage.data(), size, this));
	emit imageChanged();
}

void AnnotationArea::clearSelection()
{
	mItemModifier->clear();
	QGraphicsScene::clearSelection();
}

void AnnotationArea::itemSettingsChanged()
{
	auto selectedItems = mItemModifier->selectedItems();
	if(selectedItems.count() == 1) {
		auto item = selectedItems.first();
		auto properties = mPropertiesFactory->create(item->toolType());
		mUndoStack->push(new ChangePropertiesCommand(item, properties));
	}
}

void AnnotationArea::firstBadgeNumberChanged(int number)
{
	mItemFactory->setFirstBadgeNumber(number);
}

int AnnotationArea::firstBadgeNumber() const
{
	return mItemFactory->firstBadgeNumber();
}

void AnnotationArea::update()
{
	mItemModifier->updateSelection();
	QGraphicsScene::update();
}

void AnnotationArea::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		if (mSettingsProvider->toolType() == ToolTypes::Select) {
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
		if (mSettingsProvider->toolType() == ToolTypes::Select) {
			mItemModifier->handleMouseRelease(mItems);
		} else if (mCurrentItem != nullptr) {
			mCurrentItem->finish();
			mCurrentItem = nullptr;
		}
	}

	QGraphicsScene::mouseReleaseEvent(event);
}

void AnnotationArea::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
	mItemModifier->handleSelectionAt(event->scenePos(), mItems, mKeyHelper->isControlPressed());
	auto selectedItems = mItemModifier->selectedItems();

	AnnotationContextMenu contextMenu;
	auto isMenuOverItem = !selectedItems.isEmpty();
	contextMenu.setOverItem(isMenuOverItem);
	contextMenu.setPastEnabled(!mItemCopier->isEmpty());
    contextMenu.setEditVisible(selectedEditableItem() != nullptr);
	AnnotationItemArranger itemArranger(selectedItems, mItems);
	connect(&itemArranger, &AnnotationItemArranger::newCommand, mUndoStack, &UndoStack::push);
	connect(&contextMenu, &AnnotationContextMenu::bringToFront, &itemArranger, &AnnotationItemArranger::bringToFront);
	connect(&contextMenu, &AnnotationContextMenu::bringForward, &itemArranger, &AnnotationItemArranger::bringForward);
	connect(&contextMenu, &AnnotationContextMenu::sendBackward, &itemArranger, &AnnotationItemArranger::sendBackward);
	connect(&contextMenu, &AnnotationContextMenu::sendToBack, &itemArranger, &AnnotationItemArranger::sendToBack);
	connect(&contextMenu, &AnnotationContextMenu::copy, mItemCopier, &AnnotationItemClipboard::copyItems);
	connect(&contextMenu, &AnnotationContextMenu::paste, this, &AnnotationArea::pasteCopiedItems);
	connect(&contextMenu, &AnnotationContextMenu::erase, this, &AnnotationArea::deleteSelectedItems);
	connect(&contextMenu, &AnnotationContextMenu::edit, this, &AnnotationArea::enableEditing);

	contextMenu.exec(event->screenPos());
}

void AnnotationArea::addItemAtPosition(const QPointF &position)
{
	mCurrentItem = mItemFactory->create(position);
	mUndoStack->push(new AddCommand(mCurrentItem, this));
}

void AnnotationArea::addPointToCurrentItem(const QPointF &position)
{
	mCurrentItem->addPoint(position, mKeyHelper->isControlPressed());
}

void AnnotationArea::toolChanged(ToolTypes toolType)
{
	for (auto item : *mItems) {
		if (toolType == ToolTypes::Select) {
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
	mKeyHelper->reset();
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
	mUndoStack->push(new PasteCommand(copiedItems, position, mItemFactory, this));
}

void AnnotationArea::enableEditing()
{
    auto editableItem = selectedEditableItem();
    if(editableItem != nullptr) {
        mItemModifier->clear();
        editableItem->enableEditing();
    }
}

EditableItem* AnnotationArea::selectedEditableItem() const
{
    auto selectedItems = mItemModifier->selectedItems();
    return selectedItems.length() != 1 ? nullptr : dynamic_cast<EditableItem *>(selectedItems[0]);
}

void AnnotationArea::itemsSelected(const QList<AbstractAnnotationItem *> &items) const
{
	if(items.count() != 1) {
		mSettingsProvider->activateSelectTool();
		return;
	}
	auto item = items.first();
	mSettingsProvider->editItem(item);
}

void AnnotationArea::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
	Q_UNUSED(event)

	// Overriding default dragMoveEvent in order to accept drops without items under them
}

} // namespace kImageAnnotator
