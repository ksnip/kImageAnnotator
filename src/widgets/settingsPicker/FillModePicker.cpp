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

#include "FillModePicker.h"

namespace kImageAnnotator {

FillModePicker::FillModePicker(QWidget *parent) :
		SettingsPickerWidget(parent),
		mToolButton(new ListMenuToolButton(this)),
		mLayout(new QHBoxLayout(this)),
		mLabel(new QLabel(this))
{
	initGui();
}

FillModePicker::~FillModePicker()
{
	delete mLayout;
	delete mLabel;
	delete mToolButton;
}

void FillModePicker::setFillType(FillModes fillType)
{
	mToolButton->setCurrentData(static_cast<int>(fillType));
}

void FillModePicker::addNoFillAndNoBorderToList()
{
	mToolButton->setDataVisible(static_cast<int>(FillModes::NoBorderAndNoFill), true);
}

void FillModePicker::removeNoFillAndNoBorderToList()
{
	mToolButton->setDataVisible(static_cast<int>(FillModes::NoBorderAndNoFill), false);
}

FillModes FillModePicker::fillType() const
{
	return mToolButton->currentData().value<FillModes>();
}

QWidget *FillModePicker::expandingWidget()
{
	return mToolButton;
}

void FillModePicker::initGui()
{
	mLayout->setContentsMargins(0, 0, 0, 0);

	auto icon = IconLoader::load(QLatin1String("fillType.svg"));
	mLabel->setPixmap(icon.pixmap(ScaledSizeProvider::settingsWidgetIconSize()));
	mLabel->setToolTip(tr("Border And Fill Visibility"));

	insertItem(FillModes::BorderAndFill, QLatin1String("fillType_borderAndFill.svg"), tr("Border and Fill"));
	insertItem(FillModes::BorderAndNoFill, QLatin1String("fillType_borderAndNoFill.svg"), tr("Border and No Fill"));
	insertItem(FillModes::NoBorderAndNoFill, QLatin1String("fillType_noBorderAndNoFill.svg"), tr("No Border and No Fill"));

	mToolButton->setFocusPolicy(Qt::NoFocus);
	connect(mToolButton, &ListMenuToolButton::selectionChanged, this, &FillModePicker::selectionChanged);

	mLayout->addWidget(mLabel);
	mLayout->addWidget(mToolButton);
	mLayout->setAlignment(Qt::AlignLeft);

	setLayout(mLayout);
}

void FillModePicker::insertItem(FillModes fillType, const QString &iconName, const QString &text)
{
	auto icon = IconLoader::load(iconName);
	mToolButton->addItem(icon, text, static_cast<int>(fillType));
}

void FillModePicker::selectionChanged()
{
	auto fillType = mToolButton->currentData().value<FillModes>();
	emit fillSelected(fillType);
}

} // namespace kImageAnnotator
