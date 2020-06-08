/*
 * Copyright (C) 2018 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
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

FillTypePicker::FillTypePicker(const QIcon &icon, const QString &tooltip) :
	mToolButton(new ListMenuToolButton(this)),
	mLayout(new QHBoxLayout(this)),
	mLabel(new QLabel(this))
{
	initGui(icon, tooltip);
}

FillTypePicker::~FillTypePicker()
{
	delete mLayout;
	delete mLabel;
	delete mToolButton;
}

void FillTypePicker::setFillType(FillTypes fillType)
{
	mToolButton->setCurrentData(static_cast<int>(fillType));
	emit fillSelected(fillType);
}

void FillTypePicker::addNoFillAndNoBorderToList()
{
	mToolButton->setDataVisible(static_cast<int>(FillTypes::NoBorderAndNoFill), true);
}

void FillTypePicker::removeNoFillAndNoBorderToList()
{
	mToolButton->setDataVisible(static_cast<int>(FillTypes::NoBorderAndNoFill), false);
}

FillTypes FillTypePicker::fillType() const
{
	return mToolButton->currentData().value<FillTypes>();
}

void FillTypePicker::initGui(const QIcon &icon, const QString &tooltip)
{
	mLayout->setContentsMargins(0, 0, 0, 0);

	mLabel->setPixmap(icon.pixmap(ScaledSizeProvider::getScaledSize(Constants::SettingsWidgetIconSize)));
	mLabel->setToolTip(tooltip);

	insertItem(FillTypes::BorderAndFill, QStringLiteral("fillType_borderAndFill.svg"), tr("Border and Fill"));
	insertItem(FillTypes::BorderAndNoFill, QStringLiteral("fillType_borderAndNoFill.svg"), tr("Border and No Fill"));
	insertItem(FillTypes::NoBorderAndNoFill, QStringLiteral("fillType_noBorderAndNoFill.svg"), tr("No Border and No Fill"));

	mToolButton->setFixedSize(ScaledSizeProvider::getScaledSize(Constants::SettingsWidgetSize));
	mToolButton->setIconSize(ScaledSizeProvider::getScaledSize(Constants::ToolButtonIconSize));
	mToolButton->setFocusPolicy(Qt::NoFocus);
	connect(mToolButton, &ListMenuToolButton::selectionChanged, this, &FillTypePicker::selectionChanged);

	mLayout->addWidget(mLabel);
	mLayout->addWidget(mToolButton);

	setLayout(mLayout);
	setFixedSize(sizeHint());
}

void FillTypePicker::insertItem(FillTypes fillType, const QString &iconName, const QString &text)
{
	auto icon = IconLoader::load(iconName);
	mToolButton->addItem(icon, text, static_cast<int>(fillType));
}

void FillTypePicker::selectionChanged()
{
	auto fillType = mToolButton->currentData().value<FillTypes>();
	emit fillSelected(fillType);
}

} // namespace kImageAnnotator
