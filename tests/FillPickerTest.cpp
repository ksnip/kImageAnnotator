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

#include "FillPickerTest.h"

// void SizePickerTest::TestSelectSize_Should_EmitSignal_When_SizeChanged()
// {
//     SizePicker sizePicker;
//     QSignalSpy spy(&sizePicker, &SizePicker::sizeSelected);
//     auto expectedSize = 8;
// 
//     sizePicker.setSize(expectedSize);
// 
//     QCOMPARE(spy.count(), 1);
//     auto resultSize = qvariant_cast<int>(spy.at(0).at(0));
//     QCOMPARE(resultSize, expectedSize);
// }
// 
// void SizePickerTest::TestSelectSize_Should_NotEmitSignal_When_SelectedSizeDoesntExists()
// {
//     SizePicker sizePicker;
//     QSignalSpy spy(&sizePicker, &SizePicker::sizeSelected);
//     auto sizeNotInList = 99;
// 
//     sizePicker.setSize(sizeNotInList);
// 
//     QCOMPARE(spy.count(), 0);
// }

void SizePickerTest::TestSelectFill_Should_EmitSignal_When_FillChanged()
{
    FillPicker fillPicker;
    QSignalSpy spy(&fillPicker, &FillPicker::fillSelected);
    auto expectedFill = FillTypes::SameFill;

    fillPicker.setFill(expectedFill);

    QCOMPARE(spy.count(), 1);
    auto resultFill = qvariant_cast<FillTypes>(spy.at(0).at(0));
    QCOMPARE(resultFill, expectedFill);
}


QTEST_MAIN(SizePickerTest);
