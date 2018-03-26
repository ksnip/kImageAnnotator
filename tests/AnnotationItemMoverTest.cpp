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

#include "AnnotationItemMoverTest.h"

void AnnotationItemMoverTest::TestMoveItems_Should_MoveItemsToNewPosition()
{
    AnnotationProperties properties(Qt::red, 1);
    QPointF p1(10, 10);
    QPointF p2(10, 20);
    QPointF p3(15, 15);
    QPointF p4(20, 20);
    QPointF clickPos(p1 + QPointF(5, 5));
    QPointF newPos(QPointF(50, 50));
    AnnotationLine line1(p1, properties);
    AnnotationLine line2(p3, properties);
    line1.addPoint(p2);
    line2.addPoint(p4);
    QList<AbstractAnnotationItem*> items;
    items.append(&line1);
    items.append(&line2);
    AnnotationItemMover mover;
    mover.setOffset(clickPos, items);

    mover.moveItems(newPos);

    QCOMPARE(line1.boundingRect().topLeft(), newPos - (clickPos - p1));
    QCOMPARE(line2.boundingRect().topLeft(), newPos - (clickPos - p3));
}

QTEST_MAIN(AnnotationItemMoverTest);
