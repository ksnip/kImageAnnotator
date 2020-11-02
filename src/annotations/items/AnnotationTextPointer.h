/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KIMAGEANNOTATOR_ANNOTATIONTEXTPOINTER_H
#define KIMAGEANNOTATOR_ANNOTATIONTEXTPOINTER_H

#include "AbstractAnnotationPointerRect.h"
#include "src/annotations/items/interfaces/EditableItem.h"
#include "src/annotations/items/text/AnnotationTextHandler.h"
#include "src/annotations/items/helper/AnnotationShapeCreator.h"
#include "src/annotations/properties/AnnotationTextProperties.h"

namespace kImageAnnotator {

class AnnotationTextPointer : public AbstractAnnotationPointerRect, public EditableItem
{
Q_OBJECT
public:
	AnnotationTextPointer(const QPointF &startPosition, const TextPropertiesPtr &properties);
	AnnotationTextPointer(const AnnotationTextPointer &other);
	~AnnotationTextPointer() override = default;
	void finish() override;
	Tools toolType() const override;
	QPainterPath shape() const override;
	void enableEditing() override;
	void disableEditing() override;
	TextPropertiesPtr textProperties() const;

protected:
	AnnotationTextHandler mTextHandler;

	void updateShape() override;
	void focusOutEvent(QFocusEvent *event) override;
	void keyPressEvent(QKeyEvent *event) override;
	void inputMethodEvent(QInputMethodEvent *event) override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *style, QWidget *widget) override;

private:
	void connectSlots();
	void setupFlags();

private slots:
	void escape();
	void refresh();
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_ANNOTATIONTEXTPOINTER_H
