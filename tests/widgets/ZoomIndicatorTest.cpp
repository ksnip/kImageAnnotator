/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "ZoomIndicatorTest.h"

void ZoomIndicatorTest::SetZoomValue_Should_NotEmitSignalForChangedZoomValue()
{
	ZoomIndicator zoomIndicator(nullptr);
	QSignalSpy spy(&zoomIndicator, &ZoomIndicator::zoomValueChanged);

	zoomIndicator.setZoomValue(7.77);

	QCOMPARE(spy.count(), 0);
}

void ZoomIndicatorTest::ActivateZoomInShortcut_Should_EmitSignalForChangedZoomValue()
{
	ZoomIndicator zoomIndicator(nullptr);
	QSignalSpy spy(&zoomIndicator, &ZoomIndicator::zoomValueChanged);
	zoomIndicator.setZoomValue(2);
	zoomIndicator.show();
	if(!QTest::qWaitForWindowExposed(&zoomIndicator)) {
		QFAIL("Failed to show zoomIndicator before timeout");
	}

	QTest::keyPress(&zoomIndicator, Qt::Key_Plus, Qt::ControlModifier);
	QTest::keyRelease(&zoomIndicator, Qt::Key_Plus, Qt::ControlModifier);

	QCOMPARE(spy.count(), 1);
	auto zoomValue = qvariant_cast<double>(spy.at(0).at(0));
	QCOMPARE(zoomValue, 2.1);
}

void ZoomIndicatorTest::ActivateZoomOutShortcut_Should_EmitSignalForChangedZoomValue()
{
	ZoomIndicator zoomIndicator(nullptr);
	QSignalSpy spy(&zoomIndicator, &ZoomIndicator::zoomValueChanged);
	zoomIndicator.setZoomValue(2);
	zoomIndicator.show();
	if(!QTest::qWaitForWindowExposed(&zoomIndicator)) {
		QFAIL("Failed to show zoomIndicator before timeout");
	}

	QTest::keyPress(&zoomIndicator, Qt::Key_Minus, Qt::ControlModifier);
	QTest::keyRelease(&zoomIndicator, Qt::Key_Minus, Qt::ControlModifier);

	QCOMPARE(spy.count(), 1);
	auto zoomValue = qvariant_cast<double>(spy.at(0).at(0));
	QCOMPARE(zoomValue, 1.9);
}

QTEST_MAIN(ZoomIndicatorTest);
