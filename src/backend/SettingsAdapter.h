/*
 * Copyright (C) 2022 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
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

#ifndef KIMAGEANNOTATOR_SETTINGSADAPTER_H
#define KIMAGEANNOTATOR_SETTINGSADAPTER_H

#include <QSettings>

#include "ISettings.h"

namespace kImageAnnotator {

class SettingsAdapter : public ISettings
{
public:
	explicit SettingsAdapter() = default;
	~SettingsAdapter() override = default;
	void sync() override;
	void setValue(const QString &key, const QVariant &value) override;
	QVariant value(const QString &key, const QVariant &defaultValue) const override;

private:
	QSettings mSettings;
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_SETTINGSADAPTER_H
