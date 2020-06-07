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

#ifndef KIMAGEANNOTATOR_LISTITEMGROUP_H
#define KIMAGEANNOTATOR_LISTITEMGROUP_H

#include <QObject>
#include <QList>

#include "src/widgets/menuButtons/ListMenuItem.h"

namespace kImageAnnotator {

class ListItemGroup : public QObject
{
Q_OBJECT
public:
	explicit ListItemGroup(QObject *parent);
	~ListItemGroup() override = default;
	void addItem(ListMenuItem *item);
	ListMenuItem* checkedItem() const;
	QList<ListMenuItem*> items() const;

signals:
	void checkedItemChanged();

private:
	QList<ListMenuItem*> mItems;
	ListMenuItem *mCheckedItem;

private slots:
	void updateCheckedItem();
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_LISTITEMGROUP_H
