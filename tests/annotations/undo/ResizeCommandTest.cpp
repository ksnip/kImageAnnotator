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


#include "ResizeCommandTest.h"

void ResizeCommandTest::TestRedo_Should_MoveProvidedHandleToNewPosition()
{
    AnnotationProperties properties(Qt::red, 1);
    QLineF line(10, 10, 20, 20);
    auto item = new AnnotationLine(line.p1(), properties);
    item->addPoint(line.p2());
    QPointF newPosition(50, 50);
    ResizeCommand resize(item, 1, newPosition);
    QCOMPARE(item->line().p2(), line.p2());

    resize.redo();

    QCOMPARE(item->line().p2(), newPosition);
}

void ResizeCommandTest::TestUndo_Should_MoveProvidedHandleToInitialPosition()
{
    AnnotationProperties properties(Qt::red, 1);
    QLineF line(10, 10, 20, 20);
    auto item = new AnnotationLine(line.p1(), properties);
    item->addPoint(line.p2());
    QPointF newPosition(50, 50);
    ResizeCommand resize(item, 1, newPosition);
    resize.redo();
    QCOMPARE(item->line().p2(), newPosition);

    resize.undo();

    QCOMPARE(item->line().p2(), line.p2());
}

void ResizeCommandTest::TestMergeWith_Should_TakeNewHandlePositionFromLastResizeCommand()
{
    AnnotationProperties properties(Qt::red, 1);
    QLineF line(10, 10, 20, 20);
    auto item = new AnnotationLine(line.p1(), properties);
    item->addPoint(line.p2());
    QPointF newPosition1(50, 50);
    QPointF newPosition2(60, 60);
    ResizeCommand resize1(item, 1, newPosition1);
    ResizeCommand resize2(item, 1, newPosition2);
    QCOMPARE(item->line().p2(), line.p2());

    resize1.mergeWith(&resize2);
    resize1.redo();

    QCOMPARE(item->line().p2(), newPosition2);
}

void ResizeCommandTest::TestMergeWith_Should_KeepInitialPositionFromFirstResizeCommand()
{
    AnnotationProperties properties(Qt::red, 1);
    QLineF line(10, 10, 20, 20);
    auto item = new AnnotationLine(line.p1(), properties);
    item->addPoint(line.p2());
    QPointF newPosition1(50, 50);
    QPointF newPosition2(60, 60);
    ResizeCommand resize1(item, 1, newPosition1);
    ResizeCommand resize2(item, 1, newPosition2);

    resize1.mergeWith(&resize2);

    resize1.redo();
    QCOMPARE(item->line().p2(), newPosition2);
    resize1.undo();
    QCOMPARE(item->line().p2(), line.p2());
}

void ResizeCommandTest::TestMergeWith_Should_NotMergeResizeCommands_When_ItemsAreNotTheSame()
{
    AnnotationProperties properties(Qt::red, 1);
    QLineF line1(10, 10, 20, 20);
    QLineF line2(15, 15, 25, 25);
    auto item1 = new AnnotationLine(line1.p1(), properties);
    auto item2 = new AnnotationLine(line2.p1(), properties);
    item1->addPoint(line1.p2());
    item2->addPoint(line2.p2());
    QPointF newPosition1(50, 50);
    QPointF newPosition2(60, 60);
    ResizeCommand resize1(item1, 1, newPosition1);
    ResizeCommand resize2(item2, 1, newPosition2);
    QCOMPARE(item1->line().p2(), line1.p2());

    resize1.mergeWith(&resize2);

    resize1.redo();
    QCOMPARE(item1->line().p2(), newPosition1);
}

void ResizeCommandTest::TestMergeWith_Should_NotMergeResizeCommands_When_HandlesAreNotTheSame()
{
    AnnotationProperties properties(Qt::red, 1);
    QLineF line1(10, 10, 20, 20);
    auto item1 = new AnnotationLine(line1.p1(), properties);
    item1->addPoint(line1.p2());
    QPointF newPosition1(50, 50);
    QPointF newPosition2(60, 60);
    ResizeCommand resize1(item1, 1, newPosition1);
    ResizeCommand resize2(item1, 3, newPosition2);
    QCOMPARE(item1->line().p2(), line1.p2());

    resize1.mergeWith(&resize2);

    resize1.redo();
    QCOMPARE(item1->line().p2(), newPosition1);
}

QTEST_MAIN(ResizeCommandTest);
