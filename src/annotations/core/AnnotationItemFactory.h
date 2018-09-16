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

#ifndef KIMAGEANNOTATOR_ANNOTATIONITEMFACTORY_H
#define KIMAGEANNOTATOR_ANNOTATIONITEMFACTORY_H

#include <QObject>

#include "AnnotationPropertiesFactory.h"
#include "src/backend/Config.h"
#include "src/annotations/items/AnnotationPen.h"
#include "src/annotations/items/AnnotationLine.h"
#include "src/annotations/items/AnnotationArrow.h"
#include "src/annotations/items/AnnotationRect.h"
#include "src/annotations/items/AnnotationEllipse.h"
#include "src/annotations/items/AnnotationNumber.h"
#include "src/annotations/items/AnnotationText.h"
#include "src/common/enum/ToolTypes.h"

namespace kImageAnnotator {

class AnnotationItemFactory : public QObject
{
Q_OBJECT
public:
	explicit AnnotationItemFactory();
	~AnnotationItemFactory() override;
	void reset();

	AbstractAnnotationItem *createItem(const QPointF &initPosition, ToolTypes toolType);

private:
	int mNextNumber;
	int mNextZValue;
	Config *mConfig;
	AnnotationPropertiesFactory *mPropertiesFactory;
};

} // namespace kImageAnnotator

#endif // KIMAGEANNOTATOR_ANNOTATIONITEMFACTORY_H
