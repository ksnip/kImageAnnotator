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

#ifndef KIMAGEANNOTATOR_GRIDMENUBUTTON_H
#define KIMAGEANNOTATOR_GRIDMENUBUTTON_H

#include <QToolButton>
#include <QVariant>
#include <QStyleOption>
#include <QPainter>
#include <QPaintEvent>

#include "src/common/provider/ScaledSizeProvider.h"

namespace kImageAnnotator {

class GridMenuButton : public QToolButton
{
Q_OBJECT
public:
	GridMenuButton(const QIcon &icon, const QString &toolTip, QVariant data);
	~GridMenuButton() override = default;
	QVariant data() const;

protected slots:
	void paintEvent(QPaintEvent *event) override;

private:
	QVariant mData;
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_GRIDMENUBUTTON_H
