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

#ifndef KIMAGEANNOTATOR_NUMBERMANAGER_H
#define KIMAGEANNOTATOR_NUMBERMANAGER_H

#include <QObject>

#include "src/annotations/items/AnnotationNumber.h"
#include "src/annotations/items/AnnotationNumberPointer.h"
#include "src/annotations/items/AnnotationNumberArrow.h"

namespace kImageAnnotator {

class NumberManager : public QObject
{
Q_OBJECT
public:
	explicit NumberManager();
	~NumberManager() override = default;
	void addItem(AnnotationNumber *item);
	void addItem(AnnotationNumberPointer *item);
	void addItem(AnnotationNumberArrow *item);
	void reset();
	void setFirstNumber(int number);
	int firstNumber() const;
	void setStartingNumberUpdatesExistingItems(bool value);

public slots:
	void updateNumbers();

private:
	int mFirstNumber;
	QList<AbstractAnnotationItem *> mItems;
	bool mStartingNumberUpdatesExistingItems;

	void addItemInner(AbstractAnnotationItem *item);
};

} // namepsace kImageAnnotator

#endif //KIMAGEANNOTATOR_NUMBERMANAGER_H
