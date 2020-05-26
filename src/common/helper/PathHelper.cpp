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

#include "PathHelper.h"

namespace kImageAnnotator {

QString PathHelper::extractFilename(const QString& path)
{
	auto filename = extractFilenameWithFormat(path);
	if (filename.contains(QLatin1Char('.'))) {
		return filename.section(QLatin1Char('.'), 0, -2);
	} else {
		return filename;
	}
}

QString PathHelper::extractFilenameWithFormat(const QString &path)
{
	return path.section(QLatin1Char('/'), -1);
}

QString PathHelper::prettyFilename(const QString &filename)
{
	auto parts = filename.split(QLatin1Char('_'), QString::SkipEmptyParts);

	for (auto i = 0; i < parts.size() ; i++) {
		parts[i].replace(0, 1, parts[i][0].toUpper());
	}

	return parts.join(QLatin1Char(' '));
}

} // namespace kImageAnnotator
