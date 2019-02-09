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
	mFillList.append(FillTypes::BorderAndFill);
	mFillList.append(FillTypes::BorderAndNoFill);
	mFillList.append(FillTypes::NoBorderAndNoFill);

	initGui(icon, tooltip);

	connect(mComboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::activated), this, &FillTypePicker::selectionChanged);
}

FillTypePicker::~FillTypePicker()
{
	delete mLayout;
	delete mLabel;
	delete mComboBox;
}

void FillTypePicker::setFillType(FillTypes fillType)
{
	auto index = mComboBox->findData(mFillList.indexOf(fillType));
	if (index != -1) {
		mComboBox->setCurrentIndex(index);
		setFillAndNotify(fillType);
	}
}

void FillTypePicker::addNoFillAndNoBorderToList()
{
	auto index = mComboBox->findData(mFillList.indexOf(FillTypes::NoBorderAndNoFill));
	if (index == -1) {
		insertItem(FillTypes::NoBorderAndNoFill, QStringLiteral("fillType_NoBorderAndNoFill.svg"), tr("No Border and No Fill"));
	}
}

void FillTypePicker::removeNoFillAndNoBorderToList()
{
	auto index = mFillList.indexOf(FillTypes::NoBorderAndNoFill);
	mComboBox->removeItem(index);
}

void FillTypePicker::initGui(const QIcon &icon, const QString &tooltip)
{
	mLayout = new QHBoxLayout(this);
	mLayout->setContentsMargins(0, 0, 0, 0);

	mLabel = new QLabel();
	mLabel->setPixmap(icon.pixmap(QSize(20, 20)));
	mLabel->setToolTip(tooltip);

	mComboBox = new QComboBox(this);

	insertItem(FillTypes::BorderAndFill, QStringLiteral("fillType_borderAndFill.svg"), tr("Border and Fill"));
	insertItem(FillTypes::BorderAndNoFill, QStringLiteral("fillType_borderAndNoFill.svg"), tr("Border and No Fill"));
	mComboBox->setFixedSize(Constants::SettingsWidgetSize);
	mComboBox->setIconSize(QSize(25, 25));
	mComboBox->setToolTip(tooltip);
	mComboBox->setFocusPolicy(Qt::NoFocus);

	mLayout->addWidget(mLabel);
	mLayout->addWidget(mComboBox);

	setLayout(mLayout);
	setFixedSize(sizeHint());
}

void FillTypePicker::insertItem(FillTypes fillType, const QString &iconName, const QString &text) const
{
	auto index = mFillList.indexOf(fillType);
	auto icon = IconLoader::load(iconName);
	mComboBox->insertItem(index, icon, text, index);
	mComboBox->setItemData(index, text, Qt::ToolTipRole);
}

void FillTypePicker::setFillAndNotify(FillTypes fill)
{
	emit fillSelected(fill);
}

void FillTypePicker::selectionChanged()
{
	auto fill = mFillList[mComboBox->currentIndex()];
	setFillAndNotify(fill);
}

} // namespace kImageAnnotator
