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

#ifndef KIMAGEANNOTATOR_ANNOTATIONDUPLICATE_H
#define KIMAGEANNOTATOR_ANNOTATIONDUPLICATE_H

#include <QGraphicsScene>

#include "AbstractAnnotationRect.h"

namespace kImageAnnotator {

class AnnotationDuplicate : public AbstractAnnotationRect
{
public:
	AnnotationDuplicate(const QPointF &startPosition, const PropertiesPtr &properties);
	~AnnotationDuplicate() override = default;
	Tools toolType() const override;
	void finish() override;
	bool requiresSelectionAfterCreation() const override;
	bool allowsApplyingImageEffects() const override;

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *style, QWidget *widget) override;
	void updateShape() override;

private:
	QImage mSceneSelectionImage;

	void captureScene();
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_ANNOTATIONDUPLICATE_H
