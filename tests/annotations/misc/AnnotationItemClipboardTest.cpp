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

#include "AnnotationItemClipboardTest.h"

#include "tests/mocks/MockZoomValueProvider.h"

void AnnotationItemClipboardTest::TestCopyItems_Should_StoreSelectedItems()
{
	auto properties = PropertiesPtr(new AnnotationProperties(Qt::red, 1));
	AnnotationRect rect(QPointF(0, 0), properties);
	rect.addPoint(QPointF(50, 50), false);
	QPointF position(50, 50);
	QList<AbstractAnnotationItem *> items;
	items.append(&rect);
	MockZoomValueProvider zoomValueProvider;
	AnnotationItemModifier modifier(&zoomValueProvider);
	modifier.handleSelectionAt(position, &items, false);
	AnnotationItemClipboard clipboard(&modifier);

	clipboard.copyItems(QPointF());

	QCOMPARE(clipboard.copiedItemsWithOffset().count(), 1);
	QCOMPARE(clipboard.copiedItemsWithOffset().keys().first(), &rect);
}

void AnnotationItemClipboardTest::TestCopyItems_Should_SetCorrectOffset()
{
	auto properties = PropertiesPtr(new AnnotationProperties(Qt::red, 1));
	AnnotationRect rect(QPointF(0, 0), properties);
	rect.addPoint(QPointF(50, 50), false);
	QPointF position(50, 50);
	QList<AbstractAnnotationItem *> items;
	items.append(&rect);
	MockZoomValueProvider zoomValueProvider;
	AnnotationItemModifier modifier(&zoomValueProvider);
	modifier.handleSelectionAt(position, &items, false);
	AnnotationItemClipboard clipboard(&modifier);

	clipboard.copyItems(QPointF(20, 20));

	QCOMPARE(clipboard.copiedItemsWithOffset()[&rect], QPointF(-20, -20));
}

QTEST_MAIN(AnnotationItemClipboardTest);

