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

#include "ResizeHandlesFactory.h"

namespace kImageAnnotator {

AbstractItemResizeHandles *ResizeHandlesFactory::createResizeHandles(AbstractAnnotationItem *item, double zoomValue)
{
    auto resizeHandles = GetLineResizeHandles(item, zoomValue);
    if (resizeHandles != nullptr) {
        return resizeHandles;
    }

	resizeHandles = GetPointerRectResizeHandles(item, zoomValue);
	if (resizeHandles != nullptr) {
		return resizeHandles;
	}

    resizeHandles = GetRectResizeHandles(item, zoomValue);
    if (resizeHandles != nullptr) {
        return resizeHandles;
    }

    resizeHandles = GetPathResizeHandles(item, zoomValue);
    return resizeHandles;
}

AbstractItemResizeHandles *ResizeHandlesFactory::GetLineResizeHandles(AbstractAnnotationItem *item, double zoomValue)
{
    auto lineItem = dynamic_cast<AbstractAnnotationLine *>(item);
    if (lineItem != nullptr) {
        return new LineResizeHandles(lineItem, zoomValue);
    }
    return nullptr;
}

AbstractItemResizeHandles *ResizeHandlesFactory::GetRectResizeHandles(AbstractAnnotationItem *item, double zoomValue)
{
    auto rectItem = dynamic_cast<AbstractAnnotationRect *>(item);
    if (rectItem != nullptr) {
        return new RectResizeHandles(rectItem, zoomValue);
    }
    return nullptr;
}

AbstractItemResizeHandles *ResizeHandlesFactory::GetPointerRectResizeHandles(AbstractAnnotationItem *item, double zoomValue)
{
	auto rectItem = dynamic_cast<AbstractAnnotationPointerRect *>(item);
	if (rectItem != nullptr) {
		return new PointerRectResizeHandles(rectItem, zoomValue);
	}
	return nullptr;
}

AbstractItemResizeHandles *ResizeHandlesFactory::GetPathResizeHandles(AbstractAnnotationItem *item, double zoomValue)
{
    auto pathItem = dynamic_cast<AbstractAnnotationPath *>(item);
    if (pathItem != nullptr) {
        return new PathResizeHandles(pathItem, zoomValue);
    }
    return nullptr;
}

} // namespace kImageAnnotator
