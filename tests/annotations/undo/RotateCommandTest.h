/*
 * Copyright (C) 2021 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KIMAGEANNOTATOR_ROTATECOMMANDTEST_H
#define KIMAGEANNOTATOR_ROTATECOMMANDTEST_H

#include <QtTest>

#include "src/annotations/undo/RotateCommand.h"
#include "tests/mocks/MockSettingsProvider.h"
#include "tests/mocks/MockDevicePixelRatioScaler.h"

using kImageAnnotator::RotateCommand;
using kImageAnnotator::AnnotationArea;

class RotateCommandTest : public QObject
{
Q_OBJECT
private slots:
	void Redo_Should_RotatePixmapByProvidedAngel();
	void Redo_Should_TrimPixmapAndRemoveTransparentPart_WhenRotatedBy45DegreeTwice();
};


#endif //KIMAGEANNOTATOR_ROTATECOMMANDTEST_H
