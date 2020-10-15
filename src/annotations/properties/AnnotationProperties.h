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

#ifndef KIMAGEANNOTATOR_ANNOTATIONPROPERTIES_H
#define KIMAGEANNOTATOR_ANNOTATIONPROPERTIES_H

#include <QColor>
#include <QSharedPointer>

#include "src/common/enum/FillModes.h"

namespace kImageAnnotator {

class AnnotationProperties;
typedef QSharedPointer<AnnotationProperties> PropertiesPtr;

class AnnotationProperties
{
public:
	AnnotationProperties() = default;
	AnnotationProperties(const QColor &color, int size);
	explicit AnnotationProperties(const PropertiesPtr &other);
	virtual ~AnnotationProperties() = default;
	QColor color() const;
	void setColor(const QColor &color);
	QColor textColor() const;
	void setTextColor(const QColor &color);
	int width() const;
	void setWidth(int size);
	FillModes fillType() const;
	void setFillType(FillModes fillType);
	bool shadowEnabled() const;
	void setShadowEnabled(bool enabled);
	virtual PropertiesPtr clone() const;

private:
	QColor mColor;
	QColor mTextColor;
	int mWidth;
	FillModes mFillType;
	bool mShadowEnabled;
};

} // namespace kImageAnnotator

#endif // KIMAGEANNOTATOR_ANNOTATIONPROPERTIES_H
