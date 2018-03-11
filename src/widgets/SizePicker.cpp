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

SizePicker::SizePicker(const QString& name, int minLabelWidth)
{
    mSizeList.append(2);
    mSizeList.append(3);
    mSizeList.append(4);
    mSizeList.append(5);
    mSizeList.append(8);
    mSizeList.append(12);

    mIconCreater = new IconCreater();

    initGui(name, minLabelWidth);

    connect(mComboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::activated), this, &SizePicker::selectionChanged);
}

SizePicker::~SizePicker()
{
    delete mLayout;
    delete mComboBox;
    delete mLabel;
    delete mIconCreater;
}

void SizePicker::setSize(int size)
{
    auto index = mComboBox->findData(size);
    if(index != -1) {
        mComboBox->setCurrentIndex(index);
        setSizeAndNotify(size);
    }
}

void SizePicker::initGui(const QString& name, int minLabelWidth)
{
    mLayout = new QHBoxLayout(this);
    mLayout->setContentsMargins(0, 0, 0, 0);

    mLabel = new QLabel(name + QStringLiteral(": "));
    if(minLabelWidth != -1) {
        mLabel->setMinimumWidth(minLabelWidth);
    }

    mComboBox = new QComboBox(this);
    mComboBox->setIconSize(mIconCreater->iconSize());

    for(auto size : mSizeList) {
        mComboBox->addItem(mIconCreater->createSizeIcon(size), QString::number(size) + QStringLiteral("px"), size);
    }

    mLayout->addWidget(mLabel);
    mLayout->addWidget(mComboBox);

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
    auto size = mComboBox->currentData().toInt();
    setSizeAndNotify(size);
}
