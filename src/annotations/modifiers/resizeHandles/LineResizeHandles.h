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

#ifndef KIMAGEANNOTATOR_LINERESIZEHANDLES_H
#define KIMAGEANNOTATOR_LINERESIZEHANDLES_H

#include "AbstractItemResizeHandles.h"
#include "src/annotations/items/AbstractAnnotationLine.h"
#include "src/common/helper/ShapeHelper.h"

namespace kImageAnnotator {

class LineResizeHandles : public AbstractItemResizeHandles
{
public:
    LineResizeHandles(AbstractAnnotationLine *lineItem, double zoomValue);
    ~LineResizeHandles() = default;
    virtual void update() override;

protected:
    virtual void initCursors() override;

private:
    AbstractAnnotationLine *mLineItem;
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_LINERESIZEHANDLES_H
