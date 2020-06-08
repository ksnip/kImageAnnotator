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

#include "FillTypePickerTest.h"

void FillTypePickerTest::TestSelectFill_Should_EmitSignal_When_FillChanged()
{
	qRegisterMetaType<FillTypes>("FillTypes");
	FillTypePicker fillPicker(QIcon(), QStringLiteral("test"));
	QSignalSpy spy(&fillPicker, &FillTypePicker::fillSelected);
	auto expectedFill = FillTypes::BorderAndNoFill;

	fillPicker.setFillType(expectedFill);

	QCOMPARE(spy.count(), 1);
	auto resultFill = qvariant_cast<FillTypes>(spy.at(0).at(0));
	QCOMPARE(resultFill, expectedFill);
}

void FillTypePickerTest::TestAddNoBorderAndNoFillToList_Should_AddTypeToList()
{
	qRegisterMetaType<FillTypes>("FillTypes");
	FillTypePicker fillPicker(QIcon(), QStringLiteral("test"));
	QSignalSpy spy(&fillPicker, &FillTypePicker::fillSelected);
	auto expectedFill = FillTypes::NoBorderAndNoFill;

	fillPicker.addNoFillAndNoBorderToList();
	fillPicker.setFillType(expectedFill);

	QCOMPARE(spy.count(), 1);
	auto resultFill = qvariant_cast<FillTypes>(spy.at(0).at(0));
	QCOMPARE(resultFill, expectedFill);
}

void FillTypePickerTest::TestRemoveNoBorderAndNoFillToList_Should_RemoveTypeFromList()
{
	qRegisterMetaType<FillTypes>("FillTypes");
	FillTypePicker fillPicker(QIcon(), QStringLiteral("test"));
	QSignalSpy spy(&fillPicker, &FillTypePicker::fillSelected);
	auto expectedFill = FillTypes::NoBorderAndNoFill;
	fillPicker.addNoFillAndNoBorderToList();
	fillPicker.setFillType(expectedFill);
	QCOMPARE(spy.count(), 1);
	auto resultFill = qvariant_cast<FillTypes>(spy.at(0).at(0));
	QCOMPARE(resultFill, expectedFill);

	fillPicker.removeNoFillAndNoBorderToList();
	fillPicker.setFillType(expectedFill);

	QCOMPARE(spy.count(), 1);
}

QTEST_MAIN(FillTypePickerTest);
