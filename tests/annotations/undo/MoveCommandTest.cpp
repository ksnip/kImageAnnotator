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


#include "MoveCommandTest.h"

void MoveCommandTest::TestRedo_Should_MoveItemToNewPosition()
{
    AnnotationProperties properties(Qt::red, 1);
    QLineF line(10, 10, 20, 20);
    auto item = new AnnotationLine(line.p1(), properties);
    item->addPoint(line.p2());
    auto oldPosition = item->position();
    QPointF newPosition(50, 50);
    QHash<AbstractAnnotationItem *, QPointF> itemToPosition;
    itemToPosition[item] = newPosition;
    MoveCommand moveCommand(itemToPosition);
    QCOMPARE(item->position(), oldPosition);

    moveCommand.redo();

    QCOMPARE(item->position(), newPosition);
}

void MoveCommandTest::TestUndo_Should_MoveItemToInitialPosition()
{
    AnnotationProperties properties(Qt::red, 1);
    QLineF line(10, 10, 20, 20);
    auto item = new AnnotationLine(line.p1(), properties);
    item->addPoint(line.p2());
    auto oldPosition = item->position();
    QPointF newPosition(50, 50);
    QHash<AbstractAnnotationItem *, QPointF> itemToPosition;
    itemToPosition[item] = newPosition;
    MoveCommand moveCommand(itemToPosition);
    moveCommand.redo();
    QCOMPARE(item->position(), newPosition);

    moveCommand.undo();

    QCOMPARE(item->position(), oldPosition);
}

void MoveCommandTest::TestMergeWith_Should_TakeNewPositrionFromLastMoveCommand()
{
    AnnotationProperties properties(Qt::red, 1);
    QLineF line(10, 10, 20, 20);
    auto item = new AnnotationLine(line.p1(), properties);
    item->addPoint(line.p2());
    auto oldPosition = item->position();
    QPointF firstPosition(50, 50);
    QPointF secondPosition(70, 70);
    QHash<AbstractAnnotationItem *, QPointF> itemToPositionFirst;
    QHash<AbstractAnnotationItem *, QPointF> itemToPositionSecond;
    itemToPositionFirst[item] = firstPosition;
    itemToPositionFirst[item] = secondPosition;
    MoveCommand moveCommandFirst(itemToPositionFirst);
    MoveCommand moveCommandSecond(itemToPositionSecond);

    moveCommandFirst.mergeWith(&moveCommandSecond);

    QCOMPARE(item->position(), oldPosition);
    moveCommandFirst.redo();
    QCOMPARE(item->position(), secondPosition);
}

void MoveCommandTest::TestMergeWith_Should_KeepInitialPositionFromFirstMoveCommand()
{
    AnnotationProperties properties(Qt::red, 1);
    QLineF line(10, 10, 20, 20);
    auto item = new AnnotationLine(line.p1(), properties);
    item->addPoint(line.p2());
    auto oldPosition = item->position();
    QPointF firstPosition(50, 50);
    QPointF secondPosition(70, 70);
    QHash<AbstractAnnotationItem *, QPointF> itemToPositionFirst;
    QHash<AbstractAnnotationItem *, QPointF> itemToPositionSecond;
    itemToPositionFirst[item] = firstPosition;
    itemToPositionFirst[item] = secondPosition;
    MoveCommand moveCommandFirst(itemToPositionFirst);
    MoveCommand moveCommandSecond(itemToPositionSecond);

    moveCommandFirst.mergeWith(&moveCommandSecond);

    moveCommandFirst.redo();
    QCOMPARE(item->position(), secondPosition);
    moveCommandFirst.undo();
    QCOMPARE(item->position(), oldPosition);
}

void MoveCommandTest::TestMergeWith_Should_NotMergeMoveCommandsWhenItemsAreNotTheSame()
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
    QHash<AbstractAnnotationItem *, QPointF> item1ToPosition;
    QHash<AbstractAnnotationItem *, QPointF> item2ToPosition;
    item1ToPosition[item1] = newPosition1;
    item2ToPosition[item2] = newPosition2;
    MoveCommand moveCommand1(item1ToPosition);
    MoveCommand moveCommand2(item2ToPosition);

    moveCommand1.mergeWith(&moveCommand2);

    moveCommand1.redo();
    moveCommand2.redo();
    QCOMPARE(item1->position(), newPosition1);
    QCOMPARE(item2->position(), newPosition2);
}

QTEST_MAIN(MoveCommandTest);
