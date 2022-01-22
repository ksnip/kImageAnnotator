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


#include "ConfigTest.h"

void ConfigTest::TestSetSelectedTool_Should_NotSaveSelection_When_SaveToolSelectionDisabled()
{
	// arrange
	qRegisterMetaType<Tools>("ToolTypes");
	auto defaultTool = Tools::Pen;
	auto settingsMock = QSharedPointer<SettingsMock>(new SettingsMock);

	EXPECT_CALL(*settingsMock, value(testing::_, testing::_))
			.WillRepeatedly(testing::Return((int)defaultTool));
	EXPECT_CALL(*settingsMock, setValue(testing::_, testing::_)).Times(0);

	Config config(settingsMock);
	config.setSaveToolSelection(false);

	// act & assert
	config.setSelectedToolType(Tools::Ellipse);
}

void ConfigTest::TestSetSelectedTool_Should_SaveSelection_When_SaveToolSelectionEnabled()
{
	// arrange
	qRegisterMetaType<Tools>("ToolTypes");
	auto defaultTool = Tools::Pen;
	auto selectedTool = Tools::Ellipse;
	auto settingsMock = QSharedPointer<SettingsMock>(new SettingsMock);

	EXPECT_CALL(*settingsMock, value(testing::_, testing::_))
			.WillRepeatedly(testing::Return((int)defaultTool));
	EXPECT_CALL(*settingsMock, setValue(ConfigNameHelper::toolType(), QVariant((int)selectedTool))).Times(1);
	EXPECT_CALL(*settingsMock, sync()).Times(testing::AnyNumber());

	Config config(settingsMock);
	config.setSaveToolSelection(true);

	// act & assert
	config.setSelectedToolType(selectedTool);
}

TEST_MAIN(ConfigTest);
