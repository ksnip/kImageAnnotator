/*
 * Copyright (C) 2019 Damir Porobic <damir.porobic@gmx.com>
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

#include "CustomToolButtonMenu.h"

namespace kImageAnnotator {

CustomToolButtonMenu::CustomToolButtonMenu(QWidget *parent) : QMenu(parent)
{
	if (auto customToolButton = dynamic_cast<CustomToolButton *>(parent)) {
		connect(this, &CustomToolButtonMenu::triggered, customToolButton, &CustomToolButton::setActiveAction);
	}
}

void CustomToolButtonMenu::showEvent(QShowEvent *event)
{
	QMenu::showEvent(event);

	// Workaround for Qt bug where on first time opening the button text is
	// changed to the default action, introduced with Qt5
	if (auto customToolButton = dynamic_cast<CustomToolButton *>(parent())) {
		customToolButton->refreshText();
	}
}

} // namespace kImageAnnotator