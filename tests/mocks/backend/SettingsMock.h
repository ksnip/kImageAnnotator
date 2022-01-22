/*
 * Copyright (C) 2022 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KIMAGEANNOTATOR_SETTINGSMOCK_H
#define KIMAGEANNOTATOR_SETTINGSMOCK_H

#include "src/backend/ISettings.h"

using kImageAnnotator::ISettings;

class SettingsMock : public ISettings
{
public:
	explicit SettingsMock() = default;
	~SettingsMock() override = default;

	MOCK_METHOD(void, sync, (), (override));
	MOCK_METHOD(void, setValue, (const QString &key, const QVariant &value), (override));
	MOCK_METHOD(QVariant, value, (const QString &key, const QVariant &defaultValue), (const, override));
};

#endif //KIMAGEANNOTATOR_SETTINGSMOCK_H
