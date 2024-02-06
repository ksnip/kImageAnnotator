/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "StickerPickerTest.h"

void StickerPickerTest::TestSelectSticker_Should_EmitSignal_When_StickerChanged()
{
	StickerPicker stickerPicker(nullptr);
	QSignalSpy spy(&stickerPicker, &StickerPicker::stickerSelected);
	auto expectedStickerPath = QStringLiteral(":/stickers/nerd_face.svg");

	stickerPicker.setSticker(expectedStickerPath);

	QCOMPARE(spy.count(), 1);
	auto resultSize = qvariant_cast<QString>(spy.at(0).at(0));
	QCOMPARE(resultSize, expectedStickerPath);
}

TEST_MAIN(StickerPickerTest);
