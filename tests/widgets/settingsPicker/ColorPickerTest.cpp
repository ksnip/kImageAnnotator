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

#include "ColorPickerTest.h"

void ColorPickerTest::TestSelectColor_Should_EmitSignal_When_ColorChanged()
{
    ColorPicker colorPicker(nullptr);
    QSignalSpy spy(&colorPicker, &ColorPicker::colorSelected);
    auto expectedColor = QColor(Qt::blue);

    colorPicker.setColor(expectedColor);

    QCOMPARE(spy.count(), 1);
    auto resultColor = qvariant_cast<QColor>(spy.at(0).at(0));
    QCOMPARE(resultColor, expectedColor);
}

QTEST_MAIN(ColorPickerTest);
