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

#ifndef KIMAGEANNOTATOR_ANNOTATIONITEMMODIFIERTEST_H
#define KIMAGEANNOTATOR_ANNOTATIONITEMMODIFIERTEST_H

#include <QtTest>
#include <QUndoStack>

#include "../../../src/annotations/modifiers/AnnotationItemModifier.h"
#include "../../../src/annotations/items/AnnotationLine.h"

class AnnotationItemModifierTest : public QObject
{
    Q_OBJECT
private slots:
    void TestHandleMousePressMoveRelease_Should_MoveResizerHandle_When_ClickedOnResizerHandle();
    void TestHandleMousePressMove_Should_NotMoveResizerHandle_When_NotClickedOnResizerHandle();
    void TestHandleMousePressMoveRelease_Should_SelectMultipleItems_When_ClickedNotOnItem();
    void TestHandleMousePressMove_Should_MoveClickedItem_When_ClickedOnItemAndMoved();
    void TestHandleMousePressMove_Should_MoveSelectedItems_When_ClickedOnOfSelectedItemsAndMoved();
};

#endif // KIMAGEANNOTATOR_ANNOTATIONITEMMODIFIERTEST_H
