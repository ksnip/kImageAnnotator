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

void ConfigTest::initTestCase()
{
	QSettings::setPath(QSettings::NativeFormat, QSettings::UserScope, QStringLiteral("/tmp"));
}

void ConfigTest::cleanupTestCase()
{
	QSettings::setPath(QSettings::NativeFormat, QSettings::UserScope, QStringLiteral("$HOME/.config"));
}

void ConfigTest::TestSetSelectedTool_Should_EmitSignal_When_ToolChanged()
{
	qRegisterMetaType<ToolTypes>("ToolTypes");
	auto config = new Config;
	config->setSaveToolSelection(false);
	QSignalSpy spy(config, &Config::toolChanged);

	config->setSelectedTool(ToolTypes::Arrow);

	QCOMPARE(spy.count(), 1);
	auto type = qvariant_cast<ToolTypes>(spy.at(0).at(0));
	QCOMPARE(type, ToolTypes::Arrow);
}

void ConfigTest::TestSetSelectedTool_Should_NotSaveSelection_When_SaveToolSelectionDisabled()
{
	qRegisterMetaType<ToolTypes>("ToolTypes");
	auto defaultTool = ToolTypes::Pen;
	QSettings settings;
	settings.remove(ConfigNameHelper::toolType());
	auto config = new Config;
	config->setSaveToolSelection(false);

	config->setSelectedTool(ToolTypes::Ellipse);

	auto saveTool = settings.value(ConfigNameHelper::toolType(), static_cast<int>(defaultTool)).value<ToolTypes>();
	QCOMPARE(saveTool, defaultTool);
}

void ConfigTest::TestSetSelectedTool_Should_SaveSelection_When_SaveToolSelectionEnabled()
{
	qRegisterMetaType<ToolTypes>("ToolTypes");
	auto defaultTool = ToolTypes::Pen;
	auto selectedTool = ToolTypes::Ellipse;
	QSettings settings;
	auto config = new Config;
	config->setSaveToolSelection(true);

	config->setSelectedTool(selectedTool);

	auto saveTool = settings.value(ConfigNameHelper::toolType(), static_cast<int>(defaultTool)).value<ToolTypes>();
	QCOMPARE(saveTool, selectedTool);
}

QTEST_MAIN(ConfigTest);
