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

#include "ListItemGroup.h"

namespace kImageAnnotator {

ListItemGroup::ListItemGroup(QObject *parent) :
	QObject(parent),
	mCheckedItem(nullptr)
{

}

void ListItemGroup::addItem(ListMenuItem *item)
{
	mItems.append(item);
	connect(item, &ListMenuItem::toggled, this, &ListItemGroup::updateCheckedItem);

	if(mCheckedItem == nullptr) {
		mCheckedItem = item;
		mCheckedItem->setIsChecked(true);
	}
}

ListMenuItem *ListItemGroup::checkedItem() const
{
	return mCheckedItem;
}

QList<ListMenuItem *> ListItemGroup::items() const
{
	return mItems;
}

void ListItemGroup::updateCheckedItem()
{
	auto item = dynamic_cast<ListMenuItem*>(sender());
	if(item != nullptr && item != mCheckedItem && item->isChecked()) {
		mCheckedItem->setIsChecked(false);
		mCheckedItem = item;
		emit checkedItemChanged();
	}
}

} // namespace kImageAnnotator