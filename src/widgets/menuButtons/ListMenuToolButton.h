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

#ifndef KIMAGEANNOTATOR_LISTMENUTOOLBUTTON_H
#define KIMAGEANNOTATOR_LISTMENUTOOLBUTTON_H

#include <QToolButton>

#include "src/widgets/menuButtons/ListMenu.h"

namespace kImageAnnotator {

class ListMenuToolButton : public QToolButton
{
Q_OBJECT
public:
	explicit ListMenuToolButton(QWidget *parent);
	~ListMenuToolButton() override;
	void addItem(const QIcon &icon, const QString &text, const QVariant &data);
	QVariant currentData() const;
	void setCurrentData(const QVariant &data);
	void setDataVisible(const QVariant &data, bool isVisible);

signals:
	void selectionChanged();

private:
	ListMenu *mMenu;

private slots:
	void updateIconAndToolTip();
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_LISTMENUTOOLBUTTON_H
