/*
 * Copyright (C) 2018 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
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

ColorPicker::ColorPicker(const QIcon &icon, const QString &tooltip)
{
    initGui(icon, tooltip);

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
    mkColorPicker->selectColor(color);
    emit colorSelected(color);
}

void ColorPicker::initGui(const QIcon &icon, const QString &tooltip)
{
    mLayout = new QHBoxLayout();
    mLayout->setContentsMargins(0, 0, 0, 0);

    mLabel = new QLabel();
    mLabel->setPixmap(icon.pixmap(QSize(20, 20)));
    mLabel->setToolTip(tooltip);

    mkColorPicker = new KColorPicker();
    mkColorPicker->setFixedSize(QSize(55, mkColorPicker->sizeHint().height()));
    mkColorPicker->setFocusPolicy(Qt::NoFocus);
    mkColorPicker->setToolTip(tooltip);

    mLayout->addWidget(mLabel);
    mLayout->addWidget(mkColorPicker);

    setLayout(mLayout);
    setFixedSize(sizeHint());
}

void ColorPicker::colorChanged(const QColor &color)
{
    setColor(color);
}
