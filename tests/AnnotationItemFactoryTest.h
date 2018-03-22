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

#ifndef ANNOTATIONITEMFACTORYTEST_H
#define ANNOTATIONITEMFACTORYTEST_H

#include <QtTest>

#include "../src/annotations/AnnotationItemFactory.h"

class AnnotationItemFactoryTest : public QObject
{
Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();

    void TestCreateItem_Should_CreateItemAtProvidedPosition();
    void TestCreateItem_Should_ReturnNullPtrForUnknownType();
    void TestCreateItem_Should_ReturnAnnotationLine_When_TypeIsLine();
    void TestCreateItem_Should_ReturnAnnotationArrow_When_TypeIsArrow();
    void TestCreateItem_Should_ReturnAnnotationRect_When_TypeIsRect();
    void TestCreateItem_Should_ReturnAnnotationEllipse_When_TypeIsEllipse();
    void TestCreateItem_Should_ReturnAnnotationNumber_When_TypeIsNumber();

};

#endif // ANNOTATIONITEMFACTORYTEST_H
