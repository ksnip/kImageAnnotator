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

#include "CustomFontComboBox.h"

namespace kImageAnnotator {

CustomFontComboBox::CustomFontComboBox(QWidget *parent) : QFontComboBox(parent)
{
	connect(this, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CustomFontComboBox::elideCurrentText);

	elideCurrentText();
}

QString CustomFontComboBox::selectItemText() const
{
	return itemText(currentIndex());
}

void CustomFontComboBox::resizeEvent(QResizeEvent *event)
{
	elideCurrentText();
	QComboBox::resizeEvent(event);
}

void CustomFontComboBox::elideCurrentText()
{
	auto buttonsWidth = ScaledSizeProvider::scaledWidth(30);
	auto elidedText = fontMetrics().elidedText(selectItemText(), Qt::ElideRight, width() - buttonsWidth);

	setCurrentText(elidedText);
}

} // namespace kImageAnnotator
