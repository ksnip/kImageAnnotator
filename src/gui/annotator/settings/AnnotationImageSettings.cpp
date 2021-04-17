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

#include "AnnotationImageSettings.h"

namespace kImageAnnotator {

AnnotationImageSettings::AnnotationImageSettings() :
	mMainLayout(new QBoxLayout(QBoxLayout::LeftToRight)),
	mEffectPicker(new ImageEffectPicker(this))
{
	initGui();
}

AnnotationImageSettings::~AnnotationImageSettings()
{
	delete mEffectPicker;
	delete mMainLayout;
}

ImageEffects AnnotationImageSettings::effect() const
{
	return mEffectPicker->effect();
}

void AnnotationImageSettings::setEffect(ImageEffects effect)
{
	mEffectPicker->setEffect(effect);
}

void AnnotationImageSettings::setOrientation(Qt::Orientation orientation)
{
	if(orientation == Qt::Horizontal) {
		mMainLayout->setDirection(QBoxLayout::LeftToRight);
		mMainLayout->setAlignment(Qt::AlignLeft | Qt::AlignCenter);
	} else {
		mMainLayout->setDirection(QBoxLayout::TopToBottom);
		mMainLayout->setAlignment(Qt::AlignTop | Qt::AlignCenter);
	}

	mEffectPicker->setExpanding(orientation != Qt::Horizontal);

	adjustSize();
}

QString AnnotationImageSettings::name() const
{
	return tr("Image Settings");
}

void AnnotationImageSettings::initGui()
{
	mMainLayout->addWidget(mEffectPicker);
	mMainLayout->setContentsMargins(3, 0, 3, 0);

	setLayout(mMainLayout);

	setFocusPolicy(Qt::ClickFocus);

	connect(mEffectPicker, &ImageEffectPicker::effectSelected, this, &AnnotationImageSettings::effectChanged);
}

} // namespace kImageAnnotator