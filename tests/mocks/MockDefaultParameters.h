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

#ifndef KIMAGEANNOTATOR_MOCKDEFAULTPARAMETERS_H
#define KIMAGEANNOTATOR_MOCKDEFAULTPARAMETERS_H

#include "MockZoomValueProvider.h"
#include "MockSettingsProvider.h"
#include "MockDevicePixelRatioScaler.h"
#include "tests/mocks/backend/SettingsMock.h"

#include "src/backend/Config.h"

using kImageAnnotator::Config;

struct MockDefaultParameters
{
	MockDefaultParameters() :
			mSettings(new SettingsMock),
			config(QSharedPointer<ISettings>(mSettings))
	{
		EXPECT_CALL(*mSettings, value(testing::_, testing::_)).WillRepeatedly(testing::Return(QVariant()));
		EXPECT_CALL(*mSettings, setValue(testing::_, testing::_)).Times(testing::AnyNumber());
		EXPECT_CALL(*mSettings, sync()).Times(testing::AnyNumber());
	}

private:
	QSharedPointer<SettingsMock> mSettings;

public:
	Config config;
    MockSettingsProvider settingsProvider;
    MockZoomValueProvider zoomValueProvider;


};

#endif // KIMAGEANNOTATOR_MOCKDEFAULTPARAMETERS_H
