/*
 * Copyright (C) 2021 Damir Porobic <damir.porobic@gmx.com>
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

#include "BoolPicker.h"

namespace kImageAnnotator {

BoolPicker::BoolPicker(QWidget *parent) :
		SettingsPickerWidget(parent),
		mToolButton(new ListMenuToolButton(this)),
		mLayout(new QHBoxLayout(this)),
		mLabel(new QLabel(this))
{
	initGui();
}

BoolPicker::~BoolPicker()
{
	delete mLayout;
	delete mLabel;
	delete mToolButton;
}

void BoolPicker::setEnabledState(bool enabled)
{
	mToolButton->setCurrentData(static_cast<bool>(enabled));
}

bool BoolPicker::enabledState() const
{
	return mToolButton->currentData().value<bool>();
}

void BoolPicker::setToolTip(const QString &toolTip)
{
	mLabel->setToolTip(toolTip);
	QWidget::setToolTip(toolTip);
}

void BoolPicker::setIcon(const QIcon &icon)
{
	mLabel->setPixmap(icon.pixmap(ScaledSizeProvider::settingsWidgetIconSize()));
}

QWidget *BoolPicker::expandingWidget()
{
	return mToolButton;
}

void BoolPicker::initGui()
{
	mLayout->setContentsMargins(0, 0, 0, 0);

	insertItem(true, QLatin1String("check.svg"), tr("Enabled"));
	insertItem(false, QLatin1String("disabled.svg"), tr("Disabled"));

	mToolButton->setFocusPolicy(Qt::NoFocus);
	connect(mToolButton, &ListMenuToolButton::selectionChanged, this, &BoolPicker::selectionChanged);

	mLayout->addWidget(mLabel);
	mLayout->addWidget(mToolButton);
	mLayout->setAlignment(Qt::AlignLeft);

	setLayout(mLayout);
}

void BoolPicker::insertItem(bool enabled, const QString &iconName, const QString &text)
{
	auto icon = IconLoader::load(iconName);
	mToolButton->addItem(icon, text, static_cast<bool>(enabled));
}

void BoolPicker::selectionChanged()
{
	auto enabled = mToolButton->currentData().value<bool>();
	emit enabledStateChanged(enabled);
}

} // namespace kImageAnnotator
