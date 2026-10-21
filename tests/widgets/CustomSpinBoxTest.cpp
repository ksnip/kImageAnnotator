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

#include "CustomSpinBoxTest.h"

void CustomSpinBoxTest::TestSetValue_Should_EmitValueChangedSignal()
{
	auto newValue = 23;
	CustomSpinBox spinBox;
	QSignalSpy spy(&spinBox, &CustomSpinBox::valueChanged);

	spinBox.setValue(newValue);

	QCOMPARE(spy.count(), 1);
	auto resultValue = qvariant_cast<int>(spy.at(0).at(0));
	QCOMPARE(resultValue, newValue);
}

void CustomSpinBoxTest::TestSetValueSilent_Should_NotEmitValueChangedSignal()
{
	CustomSpinBox spinBox;
	QSignalSpy spy(&spinBox, &CustomSpinBox::valueChanged);

	spinBox.setValueSilent(23);

	QCOMPARE(spy.count(), 0);
}

void CustomSpinBoxTest::TestStepBy_Should_StepToNextMultipleOfSingleStep_When_SnapEnabled()
{
	CustomSpinBox spinBox;
	spinBox.setRange(10, 800);
	spinBox.setSingleStep(10);
	spinBox.setSnapToSingleStep(true);

	spinBox.setValue(75);
	spinBox.stepBy(1);
	QCOMPARE(spinBox.value(), 80);

	spinBox.stepBy(1);
	QCOMPARE(spinBox.value(), 90);

	spinBox.setValue(75);
	spinBox.stepBy(-1);
	QCOMPARE(spinBox.value(), 70);

	spinBox.stepBy(-1);
	QCOMPARE(spinBox.value(), 60);
}

void CustomSpinBoxTest::TestStepBy_Should_AddSingleStep_When_SnapDisabled()
{
	CustomSpinBox spinBox;
	spinBox.setRange(10, 800);
	spinBox.setSingleStep(10);

	spinBox.setValue(75);
	spinBox.stepBy(1);

	QCOMPARE(spinBox.value(), 85);
}

TEST_MAIN(CustomSpinBoxTest);
