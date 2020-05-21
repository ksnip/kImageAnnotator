/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
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

#include "AnnotationTabCloserTest.h"

void AnnotationTabCloserTest::TestCloseTabTriggered_Should_CallMethodForRequestingTabCloseWithProvidedIndex_When_ProvidedIndexValid()
{
	auto tabWidget = getTabWidgetMock();
	QSignalSpy spy(tabWidget.data(), &QTabWidget::tabCloseRequested);
	AnnotationTabCloser tabCloser(tabWidget.data());

	tabCloser.closeTabTriggered(3);

	QCOMPARE(spy.count(), 1);
	auto arguments = spy.takeFirst();
	QCOMPARE(arguments.at(0).toInt(), 3);
}

void AnnotationTabCloserTest::TestCloseTabTriggered_Should_CallMethodForRequestingTabCloseWithCurrentIndex_When_ProvidedIndexInvalid()
{
	auto tabWidget = getTabWidgetMock();
	QSignalSpy spy(tabWidget.data(), &QTabWidget::tabCloseRequested);
	AnnotationTabCloser tabCloser(tabWidget.data());

	tabCloser.closeTabTriggered(7);

	QCOMPARE(spy.count(), 1);
	auto arguments = spy.takeFirst();
	QCOMPARE(arguments.at(0).toInt(), 2);
}

void AnnotationTabCloserTest::TestCloseOtherTabsTriggered_Should_CallMethodForRequestingTabCloseForAllButProvidedIndex()
{
	auto tabWidget = getTabWidgetMock();
	QSignalSpy spy(tabWidget.data(), &QTabWidget::tabCloseRequested);
	AnnotationTabCloser tabCloser(tabWidget.data());

	tabCloser.closeOtherTabsTriggered(2);

	QCOMPARE(spy.count(), 4);
	QCOMPARE(spy[0].at(0).toInt(), 4);
	QCOMPARE(spy[1].at(0).toInt(), 3);
	QCOMPARE(spy[2].at(0).toInt(), 1);
	QCOMPARE(spy[3].at(0).toInt(), 0);
}

void AnnotationTabCloserTest::TestCloseAllTabsTriggered_Should_CallMethodForRequestingTabCloseForAllIndex()
{
	auto tabWidget = getTabWidgetMock();
	QSignalSpy spy(tabWidget.data(), &QTabWidget::tabCloseRequested);
	AnnotationTabCloser tabCloser(tabWidget.data());

	tabCloser.closeAllTabsTriggered();

	QCOMPARE(spy.count(), 5);
	QCOMPARE(spy[0].at(0).toInt(), 4);
	QCOMPARE(spy[1].at(0).toInt(), 3);
	QCOMPARE(spy[2].at(0).toInt(), 2);
	QCOMPARE(spy[3].at(0).toInt(), 1);
	QCOMPARE(spy[4].at(0).toInt(), 0);
}

void AnnotationTabCloserTest::TestCloseAllTabsToLeftTriggered_Should_CallMethodForRequestingTabCloseForAllSmallerIndex()
{
	auto tabWidget = getTabWidgetMock();
	QSignalSpy spy(tabWidget.data(), &QTabWidget::tabCloseRequested);
	AnnotationTabCloser tabCloser(tabWidget.data());

	tabCloser.closeAllTabsToLeftTriggered(2);

	QCOMPARE(spy.count(), 2);
	QCOMPARE(spy[0].at(0).toInt(), 1);
	QCOMPARE(spy[1].at(0).toInt(), 0);
}

void AnnotationTabCloserTest::TestCloseAllTabsToRightTriggered_Should_CallMethodForRequestingTabCloseForAllLargerIndex()
{
	auto tabWidget = getTabWidgetMock();
	QSignalSpy spy(tabWidget.data(), &QTabWidget::tabCloseRequested);
	AnnotationTabCloser tabCloser(tabWidget.data());

	tabCloser.closeAllTabsToRightTriggered(2);

	QCOMPARE(spy.count(), 2);
	QCOMPARE(spy[0].at(0).toInt(), 4);
	QCOMPARE(spy[1].at(0).toInt(), 3);
}

QSharedPointer<QTabWidget> AnnotationTabCloserTest::getTabWidgetMock() const
{
	auto tabWidget = QSharedPointer<QTabWidget>(new QTabWidget);
	tabWidget->addTab(new QWidget(), QString());
	tabWidget->addTab(new QWidget(), QString());
	tabWidget->addTab(new QWidget(), QString());
	tabWidget->addTab(new QWidget(), QString());
	tabWidget->addTab(new QWidget(), QString());
	tabWidget->setCurrentIndex(2);
	return tabWidget;
}

QTEST_MAIN(AnnotationTabCloserTest);