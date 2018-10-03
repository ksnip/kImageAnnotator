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

#ifndef KIMAGEANNOTATOR_ANNOTATIONITEMMODIFIER_H
#define KIMAGEANNOTATOR_ANNOTATIONITEMMODIFIER_H

#include <QObject>
#include <QGraphicsItemGroup>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneDragDropEvent>

#include "AnnotationMultiItemResizer.h"
#include "AnnotationItemSelector.h"
#include "AnnotationItemMover.h"

namespace kImageAnnotator {

class AnnotationItemModifier : public QObject, public QGraphicsItemGroup
{
Q_OBJECT
public:
	explicit AnnotationItemModifier();
	~AnnotationItemModifier() override;
	void handleMousePress(const QPointF &pos, QList<AbstractAnnotationItem *> *items, bool isCtrlPressed);
	void handleMouseMove(const QPointF &pos);
	void handleMouseRelease(QList<AbstractAnnotationItem *> *items);
	void handleSelectionAt(const QPointF &pos, QList<AbstractAnnotationItem *> *items, bool isCtrlPressed);
	QList<AbstractAnnotationItem *> selectedItems() const;
	QRectF boundingRect() const override;

public slots:
	void clear();
	void updateSelection();

signals:
	void newCommand(QUndoCommand *command);

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
	void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;

private:
	AnnotationMultiItemResizer *mItemResizer;
	AnnotationItemSelector *mItemSelector;
	AnnotationItemMover *mItemMover;

	void handleSelection();
	void updateCursor(Qt::CursorShape cursor);
};

} // namespace kImageAnnotator

#endif // KIMAGEANNOTATOR_ANNOTATIONITEMMODIFIER_H
