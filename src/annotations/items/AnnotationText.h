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

#ifndef KIMAGEANNOTATOR_ANNOTATIONTEXT_H
#define KIMAGEANNOTATOR_ANNOTATIONTEXT_H

#include "AbstractAnnotationRect.h"
#include "src/annotations/items/interfaces/EditableItem.h"
#include "src/annotations/items/text/TextHandlerItem.h"
#include "src/annotations/properties/AnnotationTextProperties.h"
#include "src/common/helper/RectSizeHelper.h"

namespace kImageAnnotator {

class AnnotationText : public AbstractAnnotationRect, public EditableItem
{
Q_OBJECT
public:
	AnnotationText(const QPointF &startPosition, const TextPropertiesPtr &properties);
	AnnotationText(const AnnotationText &other);
	~AnnotationText() override;
	void finish() override;
	Tools toolType() const override;
	QPainterPath shape() const override;
	void enableEditing() override;
	void disableEditing() override;
	TextPropertiesPtr textProperties() const;
	void setPosition(const QPointF &newPosition) override;
	void addPoint(const QPointF &position, bool modified) override;
	void setPointAt(const QPointF &point, int index, bool keepAspectRatio) override;

protected:
	void updateShape() override;

private:
	TextHandlerItem *mTextHandlerItem;

	void connectSlots();

private slots:
	void refresh();
	void updateProperties();
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_ANNOTATIONTEXT_H
