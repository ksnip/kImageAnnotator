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

#include "AnnotationItemModifierTest.h"

void AnnotationItemModifierTest::TestAttachTo_Should_AttachToAnnotationItem()
{
    QGraphicsScene scene;
    AnnotationItemModifier annotationItemModifier;
    scene.addItem(&annotationItemModifier);
    AnnotationProperties properties(QColor(QStringLiteral("Red")), 2);
    QPointF p1(10, 10);
    QPointF p2(20, 20);
    AnnotationLine lineItem(p1, properties);
    lineItem.addPoint(p2);

    annotationItemModifier.attachTo(&lineItem);

    auto result = dynamic_cast<AnnotationLine*>(annotationItemModifier.attachedItem());
    QCOMPARE(result->line(), lineItem.line());
}

void AnnotationItemModifierTest::TestDetach_Should_ClearSelectedItem()
{
    QGraphicsScene scene;
    AnnotationItemModifier annotationItemModifier;
    scene.addItem(&annotationItemModifier);
    AnnotationProperties properties(QColor(QStringLiteral("Red")), 2);
    QPointF p1(10, 10);
    QPointF p2(20, 20);
    AnnotationLine lineItem(p1, properties);
    lineItem.addPoint(p2);
    annotationItemModifier.attachTo(&lineItem);

    annotationItemModifier.detach();

    auto result = annotationItemModifier.attachedItem();
    QVERIFY(result == nullptr);
}

QTEST_MAIN(AnnotationItemModifierTest);
