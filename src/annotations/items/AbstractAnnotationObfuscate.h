/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KIMAGEANNOTATOR_ABSTRACTANNOTATIONOBFUSCATE_H
#define KIMAGEANNOTATOR_ABSTRACTANNOTATIONOBFUSCATE_H

#include <QGraphicsScene>

#include "AbstractAnnotationRect.h"
#include "src/annotations/properties/AnnotationObfuscateProperties.h"

namespace kImageAnnotator {

class AbstractAnnotationObfuscate : public AbstractAnnotationRect
{
public:
	AbstractAnnotationObfuscate(const QPointF &startPosition, const PropertiesPtr &properties);
	AbstractAnnotationObfuscate(const AbstractAnnotationObfuscate &other);
	~AbstractAnnotationObfuscate() override = default;
	ObfuscatePropertiesPtr obfuscateProperties() const;

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;
	void updateShape() override;
	virtual QImage obfuscateBackground(const QImage &sceneBehindItem) const = 0;

private:
	QImage mObfuscatedImage;
	bool mObfuscationUpdateRequired;

	void updateOverlayImage();
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_ABSTRACTANNOTATIONOBFUSCATE_H
