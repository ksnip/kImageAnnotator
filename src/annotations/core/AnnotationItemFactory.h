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

#ifndef KIMAGEANNOTATOR_ANNOTATIONITEMFACTORY_H
#define KIMAGEANNOTATOR_ANNOTATIONITEMFACTORY_H

#include <QObject>

#include "AnnotationPropertiesFactory.h"
#include "src/annotations/items/AnnotationPen.h"
#include "src/annotations/items/AnnotationPixelate.h"
#include "src/annotations/items/AnnotationLine.h"
#include "src/annotations/items/AnnotationArrow.h"
#include "src/annotations/items/AnnotationDoubleArrow.h"
#include "src/annotations/items/AnnotationRect.h"
#include "src/annotations/items/AnnotationEllipse.h"
#include "src/annotations/items/AnnotationNumber.h"
#include "src/annotations/items/AnnotationNumberPointer.h"
#include "src/annotations/items/AnnotationNumberArrow.h"
#include "src/annotations/items/AnnotationText.h"
#include "src/annotations/items/AnnotationTextPointer.h"
#include "src/annotations/items/AnnotationTextArrow.h"
#include "src/annotations/items/AnnotationBlur.h"
#include "src/annotations/items/AnnotationImage.h"
#include "src/annotations/items/AnnotationSticker.h"
#include "src/annotations/misc/NumberManager.h"
#include "src/common/enum/Tools.h"

namespace kImageAnnotator {

class AnnotationItemFactory : public QObject
{
Q_OBJECT
public:
	explicit AnnotationItemFactory(AnnotationPropertiesFactory *propertiesFactory, AbstractSettingsProvider *settingsProvider);
	~AnnotationItemFactory() override;
	void reset();
	void setFirstBadgeNumber(int number);
	int firstBadgeNumber() const;
	AbstractAnnotationItem *create(const QPointF &initPosition);
	AbstractAnnotationItem *create(const QPointF &initPosition, const QPixmap &image);
	AbstractAnnotationItem *clone(const AbstractAnnotationItem *item);

private:
	int mNextZValue;
	AnnotationPropertiesFactory *mPropertiesFactory;
	AbstractSettingsProvider *mSettingsProvider;
	NumberManager *mNumberManager;

	AbstractAnnotationItem *createItem(const QPointF &initPosition, const Tools &toolType, const PropertiesPtr &properties);
	AbstractAnnotationItem *cloneItem(const AbstractAnnotationItem *item);
	void setZValue(AbstractAnnotationItem *item);
};

} // namespace kImageAnnotator

#endif // KIMAGEANNOTATOR_ANNOTATIONITEMFACTORY_H
