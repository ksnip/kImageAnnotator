/*
 * Copyright (C) 2021 Damir Porobic <damir.porobic@gmx.com>
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

#include "AbstractAnnotationDockWidgetContent.h"

namespace kImageAnnotator {

void AbstractAnnotationDockWidgetContent::setOrientation(Qt::Orientation orientation)
{
	auto mainLayout = dynamic_cast<QBoxLayout*>(layout());

	if(mainLayout != nullptr) {
		if(orientation == Qt::Horizontal) {
			mainLayout->setDirection(QBoxLayout::LeftToRight);
			mainLayout->setAlignment(Qt::AlignLeft | Qt::AlignCenter);
		} else {
			mainLayout->setDirection(QBoxLayout::TopToBottom);
			mainLayout->setAlignment(Qt::AlignTop | Qt::AlignCenter);
		}

		for (auto widget : mExpandingWidget) {
			widget->setExpanding(orientation != Qt::Horizontal);
		}

		adjustSize();
	}
}

void AbstractAnnotationDockWidgetContent::addExpandingWidget(AbstractExpandingWidget *widget)
{
	mExpandingWidget.append(widget);
}

} // namespace kImageAnnotator