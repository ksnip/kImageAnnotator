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

#include "AnnotationItemSelector.h"

namespace kImageAnnotator {

AnnotationItemSelector::AnnotationItemSelector(AbstractCamera *camera)
{
	mSelectedItems = new QList<AbstractAnnotationItem *>();
	mShowSelectionRect = false;

	mSelectionPen.setStyle(Qt::DashLine);
	mSelectionPen.setColor(Qt::gray);

	applyZoomValue(camera->zoomValue());
	connect(camera, &AbstractCamera::zoomValueChanged, this, &AnnotationItemSelector::applyZoomValue);
}

AnnotationItemSelector::~AnnotationItemSelector()
{
	delete mSelectedItems;
}

QRectF AnnotationItemSelector::boundingRect() const
{
	if (isSelecting()) {
		return mSelectionRect.normalized();
	} else {
		return mSelectedItemsBoundingRect;
	}
}

void AnnotationItemSelector::handleSelectionOrShowSelectionRectAt(const QPointF &pos, QList<AbstractAnnotationItem *> *items, bool modifing)
{
	handleSelectionAt(pos, items, modifing);

	if (mSelectedItems->count() > 0) {
		return;
	}

	initSelectionRectAt(pos);
	mShowSelectionRect = true;
}

void AnnotationItemSelector::handleSelectionAt(const QPointF &pos, QList<AbstractAnnotationItem *> *items, bool modifying)
{
	prepareGeometryChange();

	if (modifying) {
		toggleItemSelectionAt(pos, items);
	} else {
		selectItemAt(pos, items);
	}
}

void AnnotationItemSelector::extendSelectionRectWhenShown(const QPointF &pos)
{
	if (!mShowSelectionRect) {
		return;
	}

	prepareGeometryChange();
	updateSelectionRect(pos);
}

void AnnotationItemSelector::finishSelectionRectWhenShown(QList<AbstractAnnotationItem *> *items)
{
	if (!mShowSelectionRect) {
		return;
	}

	prepareGeometryChange();
	mShowSelectionRect = false;
	selectItemsUnderRect(items);
}

void AnnotationItemSelector::clearSelection()
{
	prepareGeometryChange();
	mSelectedItems->clear();
	mSelectedItemsBoundingRect = QRectF();
}

QList<AbstractAnnotationItem *> AnnotationItemSelector::selectedItems() const
{
	return *mSelectedItems;
}

bool AnnotationItemSelector::isSelecting() const
{
	return mShowSelectionRect;
}

void AnnotationItemSelector::refresh()
{
	prepareGeometryChange();
	mSelectedItemsBoundingRect = QRectF();
	for (auto item : *mSelectedItems) {
		mSelectedItemsBoundingRect = mSelectedItemsBoundingRect.united(item->boundingRect());
	}
}

void AnnotationItemSelector::update()
{
	for (auto item : *mSelectedItems) {
		if (!item->isVisible()) {
			unselectItem(item);
		}
	}
}

void AnnotationItemSelector::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(option)
	Q_UNUSED(widget)

	if (mShowSelectionRect) {
		painter->setPen(QPen(Qt::darkBlue, mSelectionPen.widthF()));
		painter->setBrush(QColor(0, 0, 255, 60));
		painter->drawRect(mSelectionRect);
	}

	painter->setPen(mSelectionPen);
	painter->setBrush(Qt::NoBrush);
	for (auto item : *mSelectedItems) {
		if (!isLineItem(item)) {
			painter->drawRect(item->boundingRect());
		}
	}
}

bool AnnotationItemSelector::isLineItem(AbstractAnnotationItem *item) const
{
	return dynamic_cast<AbstractAnnotationLine *>(item) != nullptr;
}

void AnnotationItemSelector::initSelectionRectAt(const QPointF &position)
{
	mSelectionRect.setTopLeft(position);
	updateSelectionRect(position);
}

void AnnotationItemSelector::updateSelectionRect(const QPointF &position)
{
	mSelectionRect.setBottomRight(position);
}

void AnnotationItemSelector::selectItemAt(const QPointF &position, QList<AbstractAnnotationItem *> *items)
{
	auto item = findItemAt(position, items);

	if (item == nullptr) {
		clearSelection();
		return;
	}

	if (!mSelectedItems->contains(item)) {
		clearSelection();
		selectItem(item);
	}
}

void AnnotationItemSelector::toggleItemSelectionAt(const QPointF &position, QList<AbstractAnnotationItem *> *items)
{
	auto item = findItemAt(position, items);

	if (item == nullptr) {
		clearSelection();
		return;
	}

	if (mSelectedItems->contains(item)) {
		unselectItem(item);
	} else {
		selectItem(item);
	}
}

void AnnotationItemSelector::selectItemsUnderRect(QList<AbstractAnnotationItem *> *items)
{
	clearSelection();
	for (auto item : *items) {
		if (item->intersects(mSelectionRect)) {
			selectItem(item);
		}
	}
}

void AnnotationItemSelector::selectItem(AbstractAnnotationItem *item)
{
	mSelectedItems->append(item);
	refresh();
}

void AnnotationItemSelector::unselectItem(AbstractAnnotationItem *item)
{
	mSelectedItems->removeOne(item);
	refresh();
}

AbstractAnnotationItem *AnnotationItemSelector::findItemAt(const QPointF &position, QList<AbstractAnnotationItem *> *items)
{
	QRectF rect(position - QPointF(2, 2), QSize(4, 4));

	for (auto item : *items) {
		if (item->intersects(rect)) {
			return item;
		}
	}
	return nullptr;
}

void AnnotationItemSelector::applyZoomValue(double value)
{
	mSelectionPen.setWidthF(1.0 / value);
}

} // namespace kImageAnnotator
