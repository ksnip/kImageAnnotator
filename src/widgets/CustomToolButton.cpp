/*
 * Copyright (C) 2019 Damir Porobic <damir.porobic@gmx.com>
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

#include "CustomToolButton.h"

namespace kImageAnnotator {

CustomToolButton::CustomToolButton(QWidget *parent) : QToolButton(parent)
{
	setCheckable(true);
	setAutoRaise(true);
	setIconSize(ScaledSizeProvider::getScaledSize(QSize(24, 24)));
	setFocusPolicy(Qt::NoFocus);
	connect(this, &CustomToolButton::triggered, this, &CustomToolButton::setActiveAction);
}

void CustomToolButton::setButtonText(const QString &text)
{
	mButtonText = text;
	refreshText();
}

void CustomToolButton::setActiveAction(QAction *action)
{
	QToolButton::setDefaultAction(action);
	refreshText();
}

void CustomToolButton::trigger()
{
	if (defaultAction() != nullptr) {
		defaultAction()->trigger();
	}
}

void CustomToolButton::refreshText()
{
	QToolButton::setText(mButtonText);
}

void CustomToolButton::setMenu(QMenu *menu)
{
	setPopupMode(QToolButton::MenuButtonPopup);
	QToolButton::setMenu(menu);
	setActiveAction(menu->actions().first());
}

void CustomToolButton::setAction(QAction *action)
{
	setPopupMode(QToolButton::DelayedPopup);
	setDefaultAction(action);
}

} // namespace kImageAnnotator