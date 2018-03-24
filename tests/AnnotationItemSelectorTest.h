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

#ifndef ANNOTATIONITEMSELECTORTEST_H
#define ANNOTATIONITEMSELECTORTEST_H

#include <QtTest>

#include "../src/annotations/AnnotationItemSelector.h"
#include "../src/annotations/items/AnnotationLine.h"

class AnnotationItemSelectorTest : public QObject
{
    Q_OBJECT
private slots:
    void TestStartSelectionRectAt_Should_SelectItem_When_ItemUnderProvidedPosition();
    void TestStartSelectionRectAt_Should_NotSelectItem_When_ItemNotUnderProvidedPosition();
    void TestStartSelectionRectAt_Should_UnselectAllItems_When_ProvidedPositionNotOverAnyItem();
    void TestStartSelectionRectAt_Should_NotUnselectAnyItem_When_ProvidedPositionIsOverSelectedItem();
    void TestStartSelectionRectAt_Should_UnselectItemsNotUnderPosition_When_ProvidedPositionIsOverNotSelectedItem();
    void TestExtendSelectionRectTo_Should_SelectItems_When_ItemsWithinSelectionRect();
    void TestExtendSelectionRectTo_Should_SelectOnlyItemWithinSelectionRect();
    void TestClearSelection_Should_UnselectAllSelectedItems();
};

#endif // ANNOTATIONITEMSELECTORTEST_H
