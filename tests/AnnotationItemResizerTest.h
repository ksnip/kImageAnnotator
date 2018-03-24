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

#ifndef ANNOTATIONITEMRESIZERTEST_H
#define ANNOTATIONITEMRESIZERTEST_H

#include <QtTest>
#include <QGraphicsView>
#include <QGraphicsScene>

#include "../src/annotations/AnnotationItemResizer.h"
#include "../src/annotations/items/AnnotationLine.h"

class AnnotationItemResizerTest : public QObject
{
Q_OBJECT

private slots:
    void TestAttachTo_Should_AttachToAnnotationItem();
    void TestDetach_Should_ClearSelectedItem();
    void TestGrabHandle_Should_GrabHandle_When_ProvidedPointIsAtHandlePosition();
    void TestGrabHandle_Should_NotGrabHandle_When_ProvidedPointIsNotAtHandlePosition();
    void TestGrabHandle_Should_MoveResizeItem_When_HandleGrabbed();
    void TestReleaseHandle_Should_ReleaseHandle();
};

#endif // ANNOTATIONITEMRESIZERTEST_H
