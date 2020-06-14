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

#ifndef KIMAGEANNOTATOR_LISTMENU_H
#define KIMAGEANNOTATOR_LISTMENU_H

#include <QMenu>
#include <QVBoxLayout>

#include "src/widgets/menuButtons/ListMenuItem.h"
#include "src/widgets/menuButtons/ListItemGroup.h"
#include "src/common/provider/DevicePixelRatioScaler.h"


namespace kImageAnnotator {

class ListMenu : public QMenu
{
Q_OBJECT
public:
	explicit ListMenu(QWidget *parent);
	~ListMenu() override;
	void addItem(const QIcon &icon, const QString &text, const QVariant &data);
	QVariant currentData() const;
	void setCurrentData(const QVariant &data);
	QIcon currentIcon() const;
	QString currentText() const;
	void setDataVisible(const QVariant &data, bool isVisible);

signals:
	void selectionChanged();

private:
	QVBoxLayout *mLayout;
	ListItemGroup *mListItemGroup;
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_LISTMENU_H
