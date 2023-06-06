/*
 * Copyright (C) 2023 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef KIMAGEANNOTATOR_TEXTHANDLERITEM_H
#define KIMAGEANNOTATOR_TEXTHANDLERITEM_H

#include <QGraphicsTextItem>
#include <QStyleOptionGraphicsItem>
#include <QTextCursor>
#include <QTextDocument>
#include <QGraphicsSceneMouseEvent>

#include "src/annotations/items/AbstractAnnotationItem.h"
#include "src/annotations/properties/AnnotationTextProperties.h"
#include "src/common/provider/ScaledSizeProvider.h"

namespace kImageAnnotator {

class TextHandlerItem : public QGraphicsTextItem
{
Q_OBJECT
public:
	explicit TextHandlerItem(AbstractAnnotationItem *parentItem);
	TextHandlerItem(const TextHandlerItem &other, AbstractAnnotationItem *parentItem);
	void enableEditing();
	void disableEditing();
	bool isEditing() const;
	QRect textRect() const;
	void setTextRect(const QRect &rect);
	QRectF boundingRect() const override;
	void setTextProperties(const TextPropertiesPtr &properties);
	QSize minimumSize() const;

signals:
	void textRectChanged();

protected:
	void focusOutEvent(QFocusEvent *event) override;
	void keyPressEvent(QKeyEvent *event) override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *style, QWidget *widget) override;

private:
	bool mIsFixedTextRectSize;

	void clearSelection();
	bool isTextOutsideVisibleRect() const;
	void connectSlots() const;
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_TEXTHANDLERITEM_H
