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

#ifndef KIMAGEANNOTATOR_ANNOTATIONITEMMOVERTEST_H
#define KIMAGEANNOTATOR_ANNOTATIONITEMMOVERTEST_H

#include <QtTest>
#include <QUndoStack>

#include "tests/utils/TestRunner.h"
#include "src/annotations/modifiers/AnnotationItemMover.h"
#include "src/annotations/items/AnnotationLine.h"

using kImageAnnotator::AnnotationItemMover;
using kImageAnnotator::AnnotationProperties;
using kImageAnnotator::AnnotationLine;
using kImageAnnotator::AbstractAnnotationItem;
using kImageAnnotator::PropertiesPtr;

class AnnotationItemMoverTest : public QObject
{
Q_OBJECT
private slots:
	void TestMoveItems_Should_MoveItemsToNewPosition();
};

#endif // KIMAGEANNOTATOR_ANNOTATIONITEMMOVERTEST_H
