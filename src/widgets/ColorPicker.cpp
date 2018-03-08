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

ColorPicker::ColorPicker()
{
    mColorList.append(QStringLiteral("White"));
    mColorList.append(QStringLiteral("Black"));
    mColorList.append(QStringLiteral("Gray"));
    mColorList.append(QStringLiteral("Light Gray"));
    mColorList.append(QStringLiteral("Red"));
    mColorList.append(QStringLiteral("Dark Red"));
    mColorList.append(QStringLiteral("Orange"));
    mColorList.append(QStringLiteral("Dark Orange"));
    mColorList.append(QStringLiteral("Yellow"));
    mColorList.append(QStringLiteral("Purple"));
    mColorList.append(QStringLiteral("Green"));
    mColorList.append(QStringLiteral("Dark Green"));
    mColorList.append(QStringLiteral("Blue"));
    mColorList.append(QStringLiteral("Dark Blue"));
    mColorList.append(QStringLiteral("Violet"));
    mColorList.append(QStringLiteral("Dark Violet"));

    mIconSize = new QSize(25, 25);

    initGui();

    connect(mButtonGroup, static_cast<void (QButtonGroup::*)(QAbstractButton*)>(&QButtonGroup::buttonClicked), this, &ColorPicker::buttonClicked);
}

ColorPicker::~ColorPicker()
{
    delete mIconSize;
    delete mLayout;
    delete mButtonGroup;
    for(auto button : mButtonToColor.keys()) {
        delete button;
    }
}

void ColorPicker::setColor(const QColor& color)
{
    auto button = mButtonToColor.key(color);
    if(button) {
        button->setChecked(true);
        setColorAndNotify(color);
    }
}

void ColorPicker::initGui()
{
    mLayout = new QGridLayout();
    mLayout->setSpacing(0);

    mButtonGroup = new QButtonGroup(this);

    auto column = 0;
    for(auto i = 0; i < mColorList.count(); i++) {
        QColor color(mColorList [i]);
        auto button = createButton(color);
        mButtonToColor[button] = color;
        mButtonGroup->addButton(button);
        mLayout->addWidget(button, i % 2, column);
        column += i % 2;
    }

    setLayout(mLayout);
    setFrameShape(QFrame::Panel);
    setFrameShadow(QFrame::Sunken);
    setFixedSize(sizeHint());
}

QAbstractButton* ColorPicker::createButton(const QColor& color)
{
    auto button = new QToolButton(this);
    auto icon = createColorIcon(color);
    button->setIcon(icon);
    button->setCheckable(true);
    button->setAutoRaise(true);
    button->setIconSize(*mIconSize);
    button->setStyleSheet(QStringLiteral("QToolButton { border: 0px; padding-left: -1px; padding-top: -1px; }"
                                         "QToolButton:checked { padding: 2px; margin: 1px; border: 1px solid gray; }"
                                         "QToolButton:hover:!checked {border: 1px solid lightblue; } "
                                         "QToolButton:hover:checked {background-color: lightblue; } "));
    return button;
}

QIcon ColorPicker::createColorIcon(const QColor& color) const
{
    QPixmap pixmap(*mIconSize);
    pixmap.fill(color);
    return QIcon(pixmap);
}

void ColorPicker::setColorAndNotify(const QColor& newColor)
{
    mSelectedColor = newColor;
    emit colorSelected(newColor);
}

void ColorPicker::buttonClicked(QAbstractButton* button)
{
    setColorAndNotify(mButtonToColor[button]);
}
