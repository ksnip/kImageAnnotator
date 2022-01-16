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

#ifndef KIMAGEANNOTATOR_SELECTIONHANDLERTEST_H
#define KIMAGEANNOTATOR_SELECTIONHANDLERTEST_H

#include <QtTest>

#include "tests/utils/TestRunner.h"
#include "src/annotations/core/AnnotationArea.h"
#include "src/gui/selection/SelectionHandler.h"
#include "tests/mocks/MockDefaultParameters.h"
#include "tests/mocks/MockSelectionRestrictor.h"
#include "tests/mocks/gui/selection/SelectionHandlesMock.h"

using kImageAnnotator::AnnotationArea;
using kImageAnnotator::SelectionHandler;

class SelectionHandlerTest : public QObject
{
Q_OBJECT

private slots:
	void SetWidth_Should_EmitSelectionChangedSignal();
	void SetHeight_Should_EmitSelectionChangedSignal();
	void SetPositionX_Should_EmitSelectionChangedSignal();
	void SetPositionY_Should_EmitSelectionChangedSignal();
	void ResetSelection_Should_SetSelectionToProvidedRect();
	void IsInMotion_Should_ReturnTrue_WhenClickedOnSelection();
	void IsInMotion_Should_ReturnTrue_WhenClickedOnHandle();
	void IsInMotion_Should_ReturnFalse_WhenClickedOutsideSelectionAndHandle();
	void RestrictResize_Should_KeepCurrentSelection_When_NewSelectionHasNegativeWidthAndRestrictionDisabled();
	void RestrictResize_Should_KeepCurrentSelection_When_NewSelectionHasNegativeHeightAndRestrictionDisabled();
};

#endif // KIMAGEANNOTATOR_SELECTIONHANDLERTEST_H
