/*
 * Copyright (C) 2022 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KIMAGEANNOTATOR_SELECTIONHANDLESMOCK_H
#define KIMAGEANNOTATOR_SELECTIONHANDLESMOCK_H

#include <gmock/gmock.h>

#include "src/gui/selection/ISelectionHandles.h"

using kImageAnnotator::ISelectionHandles;

class SelectionHandlesMock : public ISelectionHandles
{
public:
	explicit SelectionHandlesMock() = default;
	~SelectionHandlesMock() override = default;

	MOCK_METHOD(QList<QRectF>, handles, (), (const, override));
	MOCK_METHOD(void, grabHandle, (const QPointF &position, const QRectF &selection), (override));
	MOCK_METHOD(void, releaseHandle, (), (override));
	MOCK_METHOD(int, grabbedIndex, (), (const, override));
	MOCK_METHOD(void, updateHandles, (const QRectF &selection), (override));
	MOCK_METHOD(bool, isHandleGrabbed, (), (const, override));
	MOCK_METHOD(QPointF, grabOffset, (), (const, override));
	MOCK_METHOD(void, applyZoomValue, (double value), (override));
};

#endif //KIMAGEANNOTATOR_SELECTIONHANDLESMOCK_H
