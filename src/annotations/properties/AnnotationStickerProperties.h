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

#ifndef KIMAGEANNOTATOR_ANNOTATIONSTICKERPROPERTIES_H
#define KIMAGEANNOTATOR_ANNOTATIONSTICKERPROPERTIES_H

#include "AnnotationProperties.h"

namespace kImageAnnotator {

class AnnotationStickerProperties : public AnnotationProperties
{
public:
	AnnotationStickerProperties() = default;
	AnnotationStickerProperties(const AnnotationStickerProperties &other);
	~AnnotationStickerProperties() override = default;
	PropertiesPtr clone() const override;
	QString path() const;
	void setPath(const QString &path);
	qreal scaling() const;
	void setScaling(qreal scaling);

private:
	QString mPath;
	qreal mScaling;
};

typedef QSharedPointer<AnnotationStickerProperties> StickerPropertiesPtr;

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_ANNOTATIONSTICKERPROPERTIES_H
