/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
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

#include "ModifyCanvasCommand.h"

namespace kImageAnnotator {


ModifyCanvasCommand::ModifyCanvasCommand(const QRectF &canvasRect, AnnotationArea *annotationArea) :
	mAnnotationArea(annotationArea),
	mNewCanvasRect(canvasRect),
	mOriginalCanvasRect(annotationArea->canvasRect())
{

}

void ModifyCanvasCommand::undo()
{
	mAnnotationArea->setCanvasRect(mOriginalCanvasRect);
}

void ModifyCanvasCommand::redo()
{
	mAnnotationArea->setCanvasRect(mNewCanvasRect);
}

} // namespace kImageAnnotator