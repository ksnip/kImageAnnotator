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

ColorPicker::ColorPicker(const QIcon& icon)
{
    initGui(icon);

    connect(mColorCombo, &KColorCombo::activated, this, &ColorPicker::colorActivated);
}

ColorPicker::~ColorPicker()
{
    delete mLayout;
    delete mLabel;
    delete mColorCombo;
}

void ColorPicker::setColor(const QColor& color)
{
    mSelectedColor = color;
    mColorCombo->setColor(color);
    emit colorSelected(color);
}

void ColorPicker::initGui(const QIcon& icon)
{
    mLayout = new QHBoxLayout();
    mLayout->setContentsMargins(0, 0, 0, 0);

    mLabel = new QLabel();
    mLabel->setPixmap(icon.pixmap(QSize(20, 20)));

    mColorCombo = new KColorCombo();
    mColorCombo->setFixedSize(QSize(55, mColorCombo->sizeHint().height()));
    mColorCombo->setFocusPolicy(Qt::NoFocus);

    mLayout->addWidget(mLabel);
    mLayout->addWidget(mColorCombo);

    setLayout(mLayout);
    setFixedSize(sizeHint());
}

void ColorPicker::colorActivated(const QColor& color)
{
    setColor(color);
}
