/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "ListMenuToolButton.h"

namespace kImageAnnotator {

ListMenuToolButton::ListMenuToolButton(QWidget *parent) :
	QToolButton(parent),
	mMenu(new ListMenu(this))
{
	setPopupMode(QToolButton::InstantPopup);
	setMenu(mMenu);

	connect(mMenu, &ListMenu::selectionChanged, this, &ListMenuToolButton::selectionChanged);
	connect(mMenu, &ListMenu::selectionChanged, this, &ListMenuToolButton::updateIconAndToolTip);
}

ListMenuToolButton::~ListMenuToolButton()
{
	delete mMenu;
}

void ListMenuToolButton::addItem(const QIcon &icon, const QString &text, const QVariant &data)
{
	mMenu->addItem(icon, text, data);
}

QVariant ListMenuToolButton::currentData() const
{
	return mMenu->currentData();
}

void ListMenuToolButton::setCurrentData(const QVariant &data)
{
	mMenu->setCurrentData(data);
}

void ListMenuToolButton::setDataVisible(const QVariant &data, bool isVisible)
{
	mMenu->setDataVisible(data, isVisible);
}

void ListMenuToolButton::updateIconAndToolTip()
{
	setIcon(mMenu->currentIcon());
	setToolTip(mMenu->currentText());
}

} // namespace kImageAnnotator
