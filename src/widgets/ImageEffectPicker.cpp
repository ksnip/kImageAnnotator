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

#include "ImageEffectPicker.h"

namespace kImageAnnotator {

ImageEffectPicker::ImageEffectPicker(QWidget *parent) :
	QWidget(parent),
	mToolButton(new ListMenuToolButton(this)),
	mLayout(new QHBoxLayout(this)),
	mLabel(new QLabel(this))
{
	initGui();
}

ImageEffectPicker::~ImageEffectPicker()
{
	delete mLayout;
	delete mLabel;
	delete mToolButton;
}

void ImageEffectPicker::setEffect(ImageEffects effect)
{
	mToolButton->setCurrentData(static_cast<int>(effect));
}

ImageEffects ImageEffectPicker::effect() const
{
	return mToolButton->currentData().value<ImageEffects>();
}

void ImageEffectPicker::initGui()
{
	mLayout->setContentsMargins(0, 0, 0, 0);

	auto icon = IconLoader::load(QLatin1String("effect.svg"));
	mLabel->setPixmap(icon.pixmap(Constants::SettingsWidgetIconSize));
	mLabel->setToolTip(tr("Image Effects"));

	insertItem(ImageEffects::NoEffect, QLatin1String("noImageEffect.svg"), tr("No Effect"));
	insertItem(ImageEffects::DropShadow, QLatin1String("dropShadowImageEffect.svg"), tr("Drop Shadow"));
	insertItem(ImageEffects::Grayscale, QLatin1String("grayscaleImageEffect.svg"), tr("Grayscale"));
	insertItem(ImageEffects::Border, QLatin1String("borderImageEffect.svg"), tr("Border"));

	mToolButton->setFixedSize(Constants::SettingsWidgetSize);
	mToolButton->setIconSize(Constants::ToolButtonIconSize);
	mToolButton->setFocusPolicy(Qt::NoFocus);
	connect(mToolButton, &ListMenuToolButton::selectionChanged, this, &ImageEffectPicker::selectionChanged);

	mLayout->addWidget(mLabel);
	mLayout->addWidget(mToolButton);

	setLayout(mLayout);
	setFixedSize(sizeHint());
}

void ImageEffectPicker::insertItem(ImageEffects effects, const QString &iconName, const QString &text)
{
	auto icon = IconLoader::load(iconName);
	mToolButton->addItem(icon, text, static_cast<int>(effects));
}

void ImageEffectPicker::selectionChanged()
{
	auto effect = mToolButton->currentData().value<ImageEffects>();
	emit effectSelected(effect);
}

} // namespace kImageAnnotator