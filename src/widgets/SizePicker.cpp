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

#include "SizePicker.h"

namespace kImageAnnotator {

SizePicker::SizePicker(const QIcon &icon, const QString &tooltip)
{
    initGui(icon, tooltip);

    connect(mSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &SizePicker::selectionChanged);
}

SizePicker::~SizePicker()
{
    delete mLayout;
    delete mSpinBox;
    delete mLabel;
}

void SizePicker::setSize(int size)
{
    mSpinBox->setValue(size);
}

void SizePicker::initGui(const QIcon &icon, const QString &tooltip)
{
    mLayout = new QHBoxLayout(this);
    mLayout->setContentsMargins(0, 0, 0, 0);

    mLabel = new QLabel();
    mLabel->setPixmap(icon.pixmap(QSize(20, 20)));
    mLabel->setToolTip(tooltip);

    mSpinBox = new QSpinBox(this);
    mSpinBox->setFixedSize(QSize(55, mSpinBox->sizeHint().height()));
    mSpinBox->setMinimum(1);
    mSpinBox->setMaximum(20);
    mSpinBox->setFocusPolicy(Qt::NoFocus);
    mSpinBox->setToolTip(tooltip);

    mLayout->addWidget(mLabel);
    mLayout->addWidget(mSpinBox);

    setLayout(mLayout);
    setFixedSize(sizeHint());
}

void SizePicker::setSizeAndNotify(int size)
{
    mSelectedSize = size;
    emit sizeSelected(size);
}

void SizePicker::selectionChanged()
{
    setSizeAndNotify(mSpinBox->value());
}

} // namespace kImageAnnotator
