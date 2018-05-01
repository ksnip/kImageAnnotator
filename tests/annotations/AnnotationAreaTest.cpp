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

#include "AnnotationAreaTest.h"

void AnnotationAreaTest::TestExportAsImage_Should_ExportImage_When_ImageSet()
{
    QPixmap pixmap(QSize(400, 400));
    pixmap.fill(QColor(QStringLiteral("Green")));
    AnnotationArea annotationArea;
    annotationArea.setBackgroundImage(pixmap);

    auto resultImage = annotationArea.exportAsImage();

    auto expectedImage = pixmap.toImage().convertToFormat(QImage::Format_ARGB32);
    QCOMPARE(expectedImage, resultImage);
}

void AnnotationAreaTest::TestExportAsImage_Should_ExportEmptyImage_When_NoImageSet()
{
    AnnotationArea annotationArea;

    auto resultImage = annotationArea.exportAsImage();

    QCOMPARE(QImage(), resultImage);
}

QTEST_MAIN(AnnotationAreaTest);
