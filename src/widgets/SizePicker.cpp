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

SizePicker::SizePicker()
{
    mSizeList.append(2);
    mSizeList.append(3);
    mSizeList.append(4);
    mSizeList.append(5);
    mSizeList.append(8);
    mSizeList.append(12);

    mIconSize = new QSize(48, 16);

    initGui();

    connect(mButtonGroup, static_cast<void (QButtonGroup::*)(QAbstractButton*)>(&QButtonGroup::buttonClicked), this, &SizePicker::buttonClicked);
}

SizePicker::~SizePicker()
{
    delete mIconSize;
    delete mLayout;
    delete mButtonGroup;
    for(auto button : mButtonToSize.keys()) {
        delete button;
    }
}

void SizePicker::setSize(int size)
{
    auto button = mButtonToSize.key(size);
    if(button) {
        button->setChecked(true);
        setSizeAndNotify(size);
    }
}

void SizePicker::initGui()
{
    mLayout = new QVBoxLayout(this);
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(0, 0, 0, 0);
    mButtonGroup = new QButtonGroup(this);

    for(auto size : mSizeList) {
        auto button = new QToolButton(this);
        button->setIcon(createIcon(size));
        button->setToolTip(QString::number(size) + QStringLiteral("px"));
        button->setCheckable(true);
        button->setAutoRaise(true);
        button->setIconSize(*mIconSize);
        button->setStyleSheet(QStringLiteral("QToolButton { padding-right: -1px; padding-bottom: -1px; margin: 0px }"));
        mButtonToSize[button] = size;
        mButtonGroup->addButton(button);
        mLayout->addWidget(button, Qt::AlignTop);
    }

    setLayout(mLayout);
    setFrameShape(QFrame::Panel);
    setFrameShadow(QFrame::Sunken);
    setFixedSize(sizeHint());
}

QIcon SizePicker::createIcon(int size) const
{
    QPixmap pixmap(*mIconSize);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    QPen pen;
    pen.setColor("#505050");
    pen.setWidth(size);
    painter.setPen(pen);
    painter.drawLine(QPointF(0, mIconSize->height() / 2), QPointF(mIconSize->width(), mIconSize->height() / 2));

    return QIcon(pixmap);
}

void SizePicker::setSizeAndNotify(int size)
{
    mSelectedSize = size;
    emit sizeSelected(size);
}


void SizePicker::buttonClicked(QAbstractButton* button)
{
    setSizeAndNotify(mButtonToSize[button]);
}
