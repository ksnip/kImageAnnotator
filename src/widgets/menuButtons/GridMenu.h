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

#ifndef KIMAGEANNOTATOR_GRIDMENU_H
#define KIMAGEANNOTATOR_GRIDMENU_H

#include <QMenu>
#include <QButtonGroup>
#include <QGridLayout>
#include <QToolButton>

#include "GridMenuButton.h"
#include "src/common/provider/DevicePixelRatioScaler.h"

namespace kImageAnnotator {

class GridMenu : public QMenu
{
Q_OBJECT
public:
	explicit GridMenu(QWidget *parent);
	~GridMenu() override;
	void addItem(const QIcon &icon, const QString &toolTip, const QVariant &data);
	void setCurrentData(const QVariant &data);
	QIcon currentIcon() const;
	QVariant currentData() const;
	QString currentToolTip() const;
	void clear();

signals:
	void selectionChanged();

private:
	QButtonGroup *mButtonGroup;
	QGridLayout *mLayout;

	void buttonClicked();
	GridMenuButton *createButton(const QIcon &icon, const QString &toolTip, const QVariant &data) const;
	void addButtonToLayout(GridMenuButton *button);
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_GRIDMENU_H
