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

#include "FillTypePicker.h"

namespace kImageAnnotator {

FillTypePicker::FillTypePicker(const QIcon &icon, const QString &tooltip)
{
    mFillList.append(FillTypes::Fill);
    mFillList.append(FillTypes::NoFill);

    mIconCreator = new IconCreater();

    initGui(icon, tooltip);

    connect(mComboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::activated), this, &FillTypePicker::selectionChanged);
}

FillTypePicker::~FillTypePicker()
{
    delete mLayout;
    delete mLabel;
    delete mComboBox;
}

void FillTypePicker::setFill(FillTypes fill)
{
    auto index = mComboBox->findData(mFillList.indexOf(fill));
    if (index != -1) {
        mComboBox->setCurrentIndex(index);
        setFillAndNotify(fill);
    }
}

void FillTypePicker::initGui(const QIcon &icon, const QString &tooltip)
{
    mLayout = new QHBoxLayout(this);
    mLayout->setContentsMargins(0, 0, 0, 0);

    mLabel = new QLabel();
    mLabel->setPixmap(icon.pixmap(QSize(20, 20)));
    mLabel->setToolTip(tooltip);

    mComboBox = new QComboBox(this);

    mComboBox->addItem(mIconCreator->createFillIcon(true), QString(), mFillList.indexOf(FillTypes::Fill));
    mComboBox->addItem(mIconCreator->createFillIcon(false), QString(), mFillList.indexOf(FillTypes::NoFill));
    mComboBox->setFixedSize(QSize(55, mComboBox->sizeHint().height()));
    mComboBox->setIconSize(mIconCreator->iconSize());
    mComboBox->setToolTip(tooltip);
    mComboBox->setFocusPolicy(Qt::NoFocus);

    mLayout->addWidget(mLabel);
    mLayout->addWidget(mComboBox);

    setLayout(mLayout);
    setFixedSize(sizeHint());
}

void FillTypePicker::setFillAndNotify(FillTypes fill)
{
    emit fillSelected(fill);
}

void FillTypePicker::selectionChanged()
{
    auto fill = mFillList[mComboBox->currentData().toInt()];
    setFillAndNotify(fill);
}

} // namespace kImageAnnotator
