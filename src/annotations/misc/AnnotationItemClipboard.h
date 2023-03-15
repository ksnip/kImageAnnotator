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

#ifndef KIMAGEANNOTATOR_ANNOTATIONITEMCLIPBOARD_H
#define KIMAGEANNOTATOR_ANNOTATIONITEMCLIPBOARD_H

#include <QList>

#include "src/annotations/modifiers/AnnotationItemModifier.h"
#include "src/annotations/core/AnnotationItemFactory.h"

namespace kImageAnnotator {

class AnnotationItemClipboard : public QObject
{
Q_OBJECT

public:
	explicit AnnotationItemClipboard() = default;
	~AnnotationItemClipboard() override = default;
	bool isEmpty() const;
	bool isNotEmpty() const;
	QHash<AbstractAnnotationItem *, QPointF> copiedItemsWithOffset() const;

public slots:
	void copyItems(const QPointF &position, const AnnotationItemModifier *itemModifier);
	void clear();

private:
	QHash<AbstractAnnotationItem *, QPointF> mCopiedItemsToOffset;
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_ANNOTATIONITEMCLIPBOARD_H
