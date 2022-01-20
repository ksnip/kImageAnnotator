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

#ifndef KIMAGEANNOTATOR_ANNOTATIONTABCLOSERTEST_H
#define KIMAGEANNOTATOR_ANNOTATIONTABCLOSERTEST_H

#include <QtTest>
#include <QTabWidget>
#include <QSharedPointer>

#include "tests/utils/TestRunner.h"
#include "src/gui/annotator/tabs/AnnotationTabCloser.h"

using kImageAnnotator::AnnotationTabCloser;

class AnnotationTabCloserTest : public QObject
{
Q_OBJECT
private slots:
	void TestCloseTabTriggered_Should_CallMethodForRequestingTabCloseWithProvidedIndex_When_ProvidedIndexValid();
	void TestCloseTabTriggered_Should_CallMethodForRequestingTabCloseWithCurrentIndex_When_ProvidedIndexInvalid();
	void TestCloseOtherTabsTriggered_Should_CallMethodForRequestingTabCloseForAllButProvidedIndex();
	void TestCloseAllTabsTriggered_Should_CallMethodForRequestingTabCloseForAllIndex();
	void TestCloseAllTabsToLeftTriggered_Should_CallMethodForRequestingTabCloseForAllSmallerIndex();
	void TestCloseAllTabsToRightTriggered_Should_CallMethodForRequestingTabCloseForAllLargerIndex();

private:
	QSharedPointer<QTabWidget> getTabWidgetMock() const;
};


#endif //KIMAGEANNOTATOR_ANNOTATIONTABCLOSERTEST_H
