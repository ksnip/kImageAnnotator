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

#ifndef KIMAGEANNOTATOR_ANNOTATIONSTICKER_H
#define KIMAGEANNOTATOR_ANNOTATIONSTICKER_H

#include <QSvgRenderer>

#include "AbstractAnnotationRect.h"
#include "src/annotations/properties/AnnotationStickerProperties.h"

namespace kImageAnnotator {

class AnnotationSticker : public AbstractAnnotationRect
{
public:
	AnnotationSticker(const QPointF &centerPosition, const StickerPropertiesPtr& properties);
	AnnotationSticker(const AnnotationSticker &other);
	~AnnotationSticker() override = default;
	void addPoint(const QPointF &position, bool modified) override;
	ToolTypes toolType() const override;
	StickerPropertiesPtr stickerProperties() const;
	void setProperties(const PropertiesPtr &properties) override ;

protected:
	void updateShape() override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
	QSvgRenderer mSvgRenderer;
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_ANNOTATIONSTICKER_H
