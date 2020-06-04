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

#include "GridMenuButton.h"

#include <utility>

namespace kImageAnnotator {

GridMenuButton::GridMenuButton(const QIcon &icon, const QString &toolTip, QVariant data) :
	mData(std::move(data))
{
	setIcon(icon);
	setToolTip(toolTip);

	setIconSize(ScaledSizeProvider::getScaledSize(QSize(32,32)));
	setCheckable(true);
	setFixedSize(iconSize() + ScaledSizeProvider::getScaledSize(QSize(4,4)));
}

QVariant kImageAnnotator::GridMenuButton::data() const
{
	return mData;
}

void GridMenuButton::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	QStyleOption styleOption;
	styleOption.initFrom(this);
	auto buttonRect = event->rect();

	painter.drawPixmap(buttonRect.topLeft() + QPointF(2, 2), icon().pixmap(iconSize()));

	if(isChecked()) {
		auto selectionRect = getSelectionRect(buttonRect);
		painter.drawRect(selectionRect);
	}

	if(styleOption.state & QStyle::State_MouseOver)
	{
		auto hoverRect = getHoverRect(buttonRect);
		painter.setPen(QColor(QStringLiteral("#add8e6")));
		painter.drawRect(hoverRect);
	}
}

QRect GridMenuButton::getHoverRect(const QRect &buttonRect) const
{
	auto topLeft = buttonRect.topLeft();
	return { topLeft.x() + 1, topLeft.y() + 1, iconSize().width() + 1, iconSize().height() + 1 };
}

QRect GridMenuButton::getSelectionRect(const QRect &buttonRect) const
{
	auto topLeft = buttonRect.topLeft();
	return { topLeft.x(), topLeft.y(), iconSize().width() + 3, iconSize().height() + 3 };
}

} // namespace kImageAnnotator