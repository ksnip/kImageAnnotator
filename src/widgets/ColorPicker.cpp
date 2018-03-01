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
    mColorList.append(QStringLiteral("Red"));
    mColorList.append(QStringLiteral("Blue"));
    mColorList.append(QStringLiteral("Green"));
    mColorList.append(QStringLiteral("Gray"));
    mColorList.append(QStringLiteral("Yellow"));
    mColorList.append(QStringLiteral("Black"));

    initGui();

    connect(this, &QToolBar::actionTriggered, this, &ColorPicker::actionTriggered);
}

void ColorPicker::setColor(const QColor& color)
{
    auto action = mActionToColor.key(color);
    action->setChecked(true);
    setColorAndNotify(color);
}

void ColorPicker::initGui()
{
    setOrientation(Qt::Vertical);

    mActionGroup = new QActionGroup(this);

    for(auto colorString : mColorList) {
        QColor color(colorString);
        auto action = addAction(colorString);
        action->setIcon(createColorIcon(color));
        action->setCheckable(true);
        mActionToColor[action] = color;
        mActionGroup->addAction(action);
    }
}

QIcon ColorPicker::createColorIcon(const QColor& color) const
{
    QPixmap pixmap(50,50);
    pixmap.fill(color);
    return QIcon(pixmap);
}

void ColorPicker::actionTriggered(QAction* action)
{
    setColorAndNotify(mActionToColor[action]);
}

void ColorPicker::setColorAndNotify(const QColor& newColor)
{
    mSelectedColor = newColor;
    emit colorSelected(newColor);
}
