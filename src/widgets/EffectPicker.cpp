/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "EffectPicker.h"

namespace kImageAnnotator {

EffectPicker::EffectPicker(QWidget *parent) :
	QWidget(parent),
	mToolButton(new ListMenuToolButton(this)),
	mLayout(new QHBoxLayout(this)),
	mLabel(new QLabel(this))
{
	initGui();
}

EffectPicker::~EffectPicker()
{
	delete mLayout;
	delete mLabel;
	delete mToolButton;
}

void EffectPicker::setEffect(Effects effect)
{
	mToolButton->setCurrentData(static_cast<int>(effect));
}

Effects EffectPicker::effect() const
{
	return mToolButton->currentData().value<Effects>();
}

void EffectPicker::initGui()
{
	mLayout->setContentsMargins(0, 0, 0, 0);

	auto icon = IconLoader::load(QLatin1Literal("effect.svg"));
	mLabel->setPixmap(icon.pixmap(Constants::SettingsWidgetIconSize));
	mLabel->setToolTip(tr("Image Effects"));

	insertItem(Effects::NoEffect, QLatin1Literal("noEffect.svg"), tr("No Effect"));
	insertItem(Effects::DropShadow, QLatin1Literal("dropShadow.svg"), tr("Drop Shadow"));

	mToolButton->setFixedSize(Constants::SettingsWidgetSize);
	mToolButton->setIconSize(Constants::ToolButtonIconSize);
	mToolButton->setFocusPolicy(Qt::NoFocus);
	connect(mToolButton, &ListMenuToolButton::selectionChanged, this, &EffectPicker::selectionChanged);

	mLayout->addWidget(mLabel);
	mLayout->addWidget(mToolButton);

	setLayout(mLayout);
	setFixedSize(sizeHint());
}

void EffectPicker::insertItem(Effects effects, const QString &iconName, const QString &text)
{
	auto icon = IconLoader::load(iconName);
	mToolButton->addItem(icon, text, static_cast<int>(effects));
}

void EffectPicker::selectionChanged()
{
	auto effect = mToolButton->currentData().value<Effects>();
	emit effectSelected(effect);
}

} // namespace kImageAnnotator