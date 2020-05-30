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

#ifndef KIMAGEANNOTATOR_BASEANNOTATIONNUMBER_H
#define KIMAGEANNOTATOR_BASEANNOTATIONNUMBER_H

#include <QString>
#include <QRectF>

#include "src/annotations/items/helper/NumberRectHelper.h"

namespace kImageAnnotator {

class BaseAnnotationNumber
{
public:
	BaseAnnotationNumber() = default;
	~BaseAnnotationNumber() = default;
	BaseAnnotationNumber(const BaseAnnotationNumber &other) = default;
	void setNumber(int number);
	int number() const;

protected:
	QString numberString() const;
	void updateRect(QRectF *rect, const QFont &font) const;
	virtual void updateRect() = 0;

private:
	QString mNumberString;
	NumberRectHelper mNumberRectHelper;
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_BASEANNOTATIONNUMBER_H
