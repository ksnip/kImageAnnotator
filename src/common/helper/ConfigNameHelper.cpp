/*
 * Copyright (C) 2018 Damir Porobic <damir.porobic@gmx.com>
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

#include "ConfigNameHelper.h"

namespace kImageAnnotator {

QString ConfigNameHelper::annotator()
{
	return QLatin1Literal("KImageAnnotator/");
}

QString ConfigNameHelper::toolType()
{
	return annotator() + QLatin1Literal("ToolType");
}

QString ConfigNameHelper::toolWidth(Tools tool)
{
	return annotator() + QLatin1Literal("ToolWidth_") + QString::number(static_cast<int>(tool));
}

QString ConfigNameHelper::toolColor(Tools tool)
{
	return annotator() + QLatin1Literal("ToolColor_") + QString::number(static_cast<int>(tool));
}

QString ConfigNameHelper::toolTextColor(Tools tool)
{
	return annotator() + QLatin1Literal("ToolTextColor_") + QString::number(static_cast<int>(tool));
}

QString ConfigNameHelper::toolFillType(Tools tool)
{
	return annotator() + QLatin1Literal("ToolFillType_") + QString::number(static_cast<int>(tool));
}

QString ConfigNameHelper::toolFontSize(Tools tool)
{
	return annotator() + QLatin1Literal("ToolFontSize_") + QString::number(static_cast<int>(tool));
}

QString ConfigNameHelper::obfuscateFactor(Tools tool)
{
	return annotator() + QLatin1Literal("ToolObfuscateFactor_") + QString::number(static_cast<int>(tool));
}

}