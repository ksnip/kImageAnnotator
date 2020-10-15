/*
 * Copyright (C) 2018 Damir Porobic <damir.porobic@gmx.com>
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

#include "ColorPicker.h"

namespace kImageAnnotator {

ColorPicker::ColorPicker(QWidget *parent) :
	QWidget(parent),
	mLayout(new QHBoxLayout(this)),
	mLabel(new QLabel(this)),
	mkColorPicker(new KColorPicker)
{
	initGui();

	connect(mkColorPicker, &KColorPicker::colorChanged, this, &ColorPicker::colorChanged);
}

ColorPicker::~ColorPicker()
{
	delete mLayout;
	delete mLabel;
	delete mkColorPicker;
}

void ColorPicker::setColor(const QColor &color)
{
	mkColorPicker->setColor(color);
	emit colorSelected(color);
}

QColor ColorPicker::color() const
{
	return mkColorPicker->color();
}

void ColorPicker::setToolTip(const QString &toolTip)
{
	mLabel->setToolTip(toolTip);
	mkColorPicker->setToolTip(toolTip);
}

void ColorPicker::setIcon(const QIcon &icon)
{
	mLabel->setPixmap(icon.pixmap(Constants::SettingsWidgetIconSize));
}

void ColorPicker::initGui()
{
	mLayout->setContentsMargins(0, 0, 0, 0);

	mLabel->setFixedSize(Constants::SettingsWidgetIconSize);

	mkColorPicker->setFixedSize(Constants::SettingsWidgetSize);
	mkColorPicker->setFocusPolicy(Qt::NoFocus);

	mLayout->addWidget(mLabel);
	mLayout->addWidget(mkColorPicker);

	setLayout(mLayout);
	setFixedSize(sizeHint());
}

void ColorPicker::colorChanged(const QColor &color)
{
	setColor(color);
}

} // namespace kImageAnnotator
