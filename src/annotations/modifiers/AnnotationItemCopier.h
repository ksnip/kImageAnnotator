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

#ifndef KIMAGEANNOTATOR_ANNOTATIONITEMCOPIER_H
#define KIMAGEANNOTATOR_ANNOTATIONITEMCOPIER_H

#include <QList>

#include "src/annotations/modifiers/AnnotationItemModifier.h"

namespace kImageAnnotator {

class AnnotationItemCopier : public QObject
{
Q_OBJECT
public:
	explicit AnnotationItemCopier(const AnnotationItemModifier *itemModifier);
	~AnnotationItemCopier() override = default;
	QList<AbstractAnnotationItem *> copiedItems() const;
	bool isEmpty() const;

public slots:
	void copyItems();
	void pastItems();
	void clear();

private:
	const AnnotationItemModifier *mItemModifier;
	QList<AbstractAnnotationItem *> mCopiedItems;
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_ANNOTATIONITEMCOPIER_H
