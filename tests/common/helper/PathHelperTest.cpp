/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
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

#include "PathHelperTest.h"

void PathHelperTest::TestExtractFilename_Should_ReturnOnlyFilename_When_FilenameHasFormat()
{
	auto expected = QStringLiteral("myFile");
	auto filename = PathHelper::extractFilename(QStringLiteral("/home/kimageannotator/") + expected + QStringLiteral(".png"));

	QCOMPARE(filename, expected);
}

void PathHelperTest::TestExtractFilename_Should_ReturnOnlyFilename_When_FilenameHasNoFormat()
{
	auto expected = QStringLiteral("myFile");
	auto filename = PathHelper::extractFilename(QStringLiteral("/home/kimageannotator/") + expected);

	QCOMPARE(filename, expected);
}

void PathHelperTest::TestExtractFilename_Should_ReturnOnlyFilename_When_FilenameWithoutPathWasProvided()
{
	auto expected = QStringLiteral("myFile");
	auto filename = PathHelper::extractFilename(expected);

	QCOMPARE(filename, expected);
}

void PathHelperTest::TestExtractFilenameWithFormat_Should_ReturnOnlyFilename_When_FilenameHasFormat()
{
	auto expected = QStringLiteral("myFile.png");
	auto filename = PathHelper::extractFilenameWithFormat(QStringLiteral("/home/kimageannotator/") + expected);

	QCOMPARE(filename, expected);
}

void PathHelperTest::TestExtractFilenameWithFormat_Should_ReturnOnlyFilename_When_FilenameWithoutPathWasProvided()
{
	auto expected = QStringLiteral("myFile.png");
	auto filename = PathHelper::extractFilenameWithFormat(expected);

	QCOMPARE(filename, expected);
}

void PathHelperTest::TestPrettyFilename_Should_ReplaceUnderscoresWithSpacesAndCapitalizeFirstLetters()
{
	auto input = QStringLiteral("my_test_File.png");
	auto expected = QStringLiteral("My Test File.png");
	auto filename = PathHelper::prettyFilename(input);

	QCOMPARE(filename, expected);
}

QTEST_MAIN(PathHelperTest);
