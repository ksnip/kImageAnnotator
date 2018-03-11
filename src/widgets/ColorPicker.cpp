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

ColorPicker::ColorPicker(const QString& name, int minLabelWidth)
{
    mIconCreater = new IconCreater();

    initGui(name, minLabelWidth);

    connect(mButton, &QPushButton::clicked, this, &ColorPicker::buttonClicked);
}

ColorPicker::~ColorPicker()
{
    delete mLayout;
    delete mButton;
    delete mLabel;
    delete mIconCreater;
}

void ColorPicker::setColor(const QColor& color)
{
    mSelectedColor = color;
    mButton->setIcon(mIconCreater->createColorIcon(color));
    emit colorSelected(color);
}

void ColorPicker::initGui(const QString& name, int minLabelWidth)
{
    mLayout = new QHBoxLayout();
    mLayout->setSpacing(0);

    mLabel = new QLabel(name + QStringLiteral(": "));
    if(minLabelWidth != -1) {
        mLabel->setMinimumWidth(minLabelWidth);
    }

    mButton = new QPushButton();
    mButton->setIcon(mIconCreater->createColorIcon(QColor(Qt::red)));
    mButton->setIconSize(mIconCreater->iconSize());

    mLayout->addWidget(mLabel);
    mLayout->addWidget(mButton);

    setLayout(mLayout);
    setFixedSize(sizeHint());
}

void ColorPicker::buttonClicked()
{
    auto color = QColorDialog::getColor(mSelectedColor, this, tr("Pick a Color"));
    setColor(color);
}
