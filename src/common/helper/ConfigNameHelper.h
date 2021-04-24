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

#ifndef KIMAGEANNOTATOR_CONFIGNAMEFORMATTER_H
#define KIMAGEANNOTATOR_CONFIGNAMEFORMATTER_H

#include <QString>

#include "src/common/enum/Tools.h"

namespace kImageAnnotator {

class ConfigNameHelper
{
public:
	static QString kImageAnnotator();
	static QString toolType();
	static QString toolWidth(Tools tool);
	static QString toolColor(Tools tool);
	static QString toolTextColor(Tools tool);
	static QString toolFillType(Tools tool);
	static QString toolFont(Tools tool);
	static QString obfuscateFactor(Tools tool);
	static QString shadowEnabled(Tools tool);
	static QString annotatorDockWidgetsState();
};

}

#endif //KIMAGEANNOTATOR_CONFIGNAMEFORMATTER_H
