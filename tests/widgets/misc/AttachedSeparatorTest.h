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

#ifndef KIMAGEANNOTATOR_ATTACHEDSEPARATORTEST_H
#define KIMAGEANNOTATOR_ATTACHEDSEPARATORTEST_H

#include <QtTest>

#include "tests/utils/TestRunner.h"
#include "src/widgets/misc/AttachedSeparator.h"
#include "src/widgets/settingsPicker/BoolPicker.h"

using kImageAnnotator::AttachedSeparator;
using kImageAnnotator::BoolPicker;

class AttachedSeparatorTest : public QObject
{
Q_OBJECT

private slots:
	void Constructor_Should_SetupInitialVisibilityToFalse_When_TargetPickerInitiallyNotVisible();
	void Constructor_Should_SetupInitialVisibilityToTrue_When_TargetPickerInitiallyVisible();
	void UpdateVisibility_Should_ChangeVisibility_When_TargetPickerVisibilityChanged();
	void UpdateVisibility_Should_NotChangeVisibility_When_TargetPickerVisibilityChangedButSeparatorIsDisabled();
	void SetEnabled_Should_UpdateVisibilityToFalse_When_Disabled();
};


#endif //KIMAGEANNOTATOR_ATTACHEDSEPARATORTEST_H
