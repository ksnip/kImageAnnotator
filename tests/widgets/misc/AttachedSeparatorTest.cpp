/*
 * Copyright (C) 2021 Damir Porobic <damir.porobic@gmx.com>
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

#include "AttachedSeparatorTest.h"

void AttachedSeparatorTest::Constructor_Should_SetupInitialVisibilityToFalse_When_TargetPickerInitiallyNotVisible()
{
	// arrange
	BoolPicker picker(nullptr);
	picker.setVisible(false);

	// act
	AttachedSeparator separator(&picker);

	// assert
	QCOMPARE(separator.isVisible(), false);
}

void AttachedSeparatorTest::Constructor_Should_SetupInitialVisibilityToTrue_When_TargetPickerInitiallyVisible()
{
	// arrange
	BoolPicker picker(nullptr);
	picker.setVisible(true);

	// act
	AttachedSeparator separator(&picker);

	// assert
	QCOMPARE(separator.isVisible(), true);
}

void AttachedSeparatorTest::UpdateVisibility_Should_ChangeVisibility_When_TargetPickerVisibilityChanged()
{
	// arrange
	BoolPicker picker(nullptr);
	picker.setVisible(true);
	AttachedSeparator separator(&picker);
	QCOMPARE(separator.isVisible(), true);

	// act
	picker.setVisible(false);

	// assert
	QCOMPARE(separator.isVisible(), false);
}

void AttachedSeparatorTest::UpdateVisibility_Should_NotChangeVisibility_When_TargetPickerVisibilityChangedButSeparatorIsDisabled()
{
	// arrange
	BoolPicker picker(nullptr);
	picker.setVisible(false);
	AttachedSeparator separator(&picker);
	QCOMPARE(separator.isVisible(), false);
	separator.setEnabled(false);

	// act
	picker.setVisible(true);

	// assert
	QCOMPARE(separator.isVisible(), false);
}

void AttachedSeparatorTest::SetEnabled_Should_UpdateVisibilityToFalse_When_Disabled()
{
	// arrange
	BoolPicker picker(nullptr);
	picker.setVisible(true);
	AttachedSeparator separator(&picker);
	QCOMPARE(separator.isVisible(), true);

	// act
	separator.setEnabled(false);
	separator.setEnabled(false);

	// assert
	QCOMPARE(separator.isVisible(), false);
	QCOMPARE(picker.isVisible(), true);
}

QTEST_MAIN(AttachedSeparatorTest)
