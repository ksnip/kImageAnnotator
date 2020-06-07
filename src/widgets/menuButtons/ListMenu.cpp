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

#include "ListMenu.h"

namespace kImageAnnotator {

ListMenu::ListMenu(QWidget *parent) :
	QMenu(parent),
	mLayout(new QVBoxLayout(this)),
	mListItemGroup(new ListItemGroup(this))
{
	setLayout(mLayout);

	mLayout->setContentsMargins(0, 0, 0, 0);
	mLayout->setSpacing(0);

	connect(mListItemGroup, &ListItemGroup::checkedItemChanged, this, &ListMenu::selectionChanged);
}

ListMenu::~ListMenu()
{
	delete mLayout;
	qDeleteAll(mListItemGroup->items());
	delete mListItemGroup;
}

void ListMenu::addItem(const QIcon &icon, const QString &text, const QVariant &data)
{
	auto item = new ListMenuItem(icon, text, data, this);
	mLayout->addWidget(item);
	mListItemGroup->addItem(item);
}

QVariant ListMenu::currentData() const
{
	auto item = mListItemGroup->checkedItem();
	return item != nullptr ? item->data() : QVariant();
}

void ListMenu::setCurrentData(const QVariant &data)
{
	for(auto item : mListItemGroup->items()) {
		if(item->data() == data){
			item->setIsChecked(true);
		}
	}
}

QIcon ListMenu::currentIcon() const
{
	auto item = mListItemGroup->checkedItem();
	return item != nullptr ? item->icon() : QIcon();
}

QString ListMenu::currentText() const
{
	auto item = mListItemGroup->checkedItem();
	return item != nullptr ? item->text() : QString();
}

void ListMenu::setDataVisible(const QVariant &data, bool isVisible)
{
	for(auto item : mListItemGroup->items()) {
		if(item->data() == data){
			item->setVisible(isVisible);
		}
	}
	setMinimumSize(mLayout->minimumSize());
}

} // namespace kImageAnnotator
