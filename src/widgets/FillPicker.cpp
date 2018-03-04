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

#include "FillPicker.h"

FillPicker::FillPicker()
{
    mFillList.append(FillTypes::NoFill);
    mFillList.append(FillTypes::SeperateFill);
    mFillList.append(FillTypes::SameFill);

    mIconSize = new QSize(48, 32);

    initGui();

    connect(mButtonGroup, static_cast<void (QButtonGroup::*)(QAbstractButton*)>(&QButtonGroup::buttonClicked), this, &FillPicker::buttonClicked);
}

FillPicker::~FillPicker()
{
    delete mIconSize;
    delete mLayout;
    delete mButtonGroup;
    for(auto button : mButtonToFill.keys()) {
        delete button;
    }
}

void FillPicker::setFill(FillTypes fill)
{
    auto button = mButtonToFill.key(fill);
    button->setChecked(true);
    setFillAndNotify(fill);
}

void FillPicker::initGui()
{
    mLayout = new QVBoxLayout(this);
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(0, 0, 0, 0);
    mButtonGroup = new QButtonGroup(this);

    for(auto fill : mFillList) {
        auto button = new QToolButton(this);
        button->setIcon(createIcon(fill));
        button->setCheckable(true);
        button->setAutoRaise(false);
        button->setIconSize(*mIconSize);
        button->setStyleSheet(QStringLiteral("QToolButton { border: 0px; padding-right: -1px; padding-bottom: -1px; margin: 0px }"
                                             "QToolButton:checked { border: 1px solid gray; background-color: paleturquoise}"));
        mButtonToFill[button] = fill;
        mButtonGroup->addButton(button);
        mLayout->addWidget(button, Qt::AlignTop);
    }

    setLayout(mLayout);
    setFixedSize(sizeHint());
}

QIcon FillPicker::createIcon(FillTypes fill) const
{
    QPixmap pixmap(*mIconSize);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(4);
    painter.setPen(pen);

    if (fill == FillTypes::SeperateFill) {
        painter.setBrush(Qt::gray);
    } else if (fill == FillTypes::SameFill){
        painter.setBrush(Qt::black);
    }

    painter.drawRect(QRectF(0, 7, mIconSize->width(), mIconSize->height() - 14));

    return QIcon(pixmap);
}

void FillPicker::buttonClicked(QAbstractButton* button)
{
    setFillAndNotify(mButtonToFill[button]);
}

void FillPicker::setFillAndNotify(FillTypes fill)
{
    mSelectedFill = fill;
    emit fillSelected(fill);
}

