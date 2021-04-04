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

#include "AnnotationGeneralSettings.h"

namespace kImageAnnotator {

AnnotationGeneralSettings::AnnotationGeneralSettings() :
	mMainLayout(new QBoxLayout(QBoxLayout::LeftToRight)),
	mEffectPicker(new ImageEffectPicker(this)),
	mZoomIndicator(new ZoomIndicator(this))
{
	initGui();
}

AnnotationGeneralSettings::~AnnotationGeneralSettings()
{
	delete mEffectPicker;
	delete mZoomIndicator;
	delete mMainLayout;
}

void AnnotationGeneralSettings::initGui()
{
	mMainLayout->addWidget(mZoomIndicator);
	mMainLayout->addWidget(mEffectPicker);
	mMainLayout->setContentsMargins(0, 0, 0, 0);

	setLayout(mMainLayout);

	setFocusPolicy(Qt::ClickFocus);

	connect(mEffectPicker, &ImageEffectPicker::effectSelected, this, &AnnotationGeneralSettings::effectChanged);
	connect(mZoomIndicator, &ZoomIndicator::zoomValueChanged, this, &AnnotationGeneralSettings::zoomValueChanged);
}

ImageEffects AnnotationGeneralSettings::effect() const
{
	return mEffectPicker->effect();
}

void AnnotationGeneralSettings::setEffect(ImageEffects effect)
{
	mEffectPicker->setEffect(effect);
}

void AnnotationGeneralSettings::updateZoomLevel(double value)
{
	mZoomIndicator->setZoomValue(value);
}

void AnnotationGeneralSettings::setOrientation(Qt::Orientation orientation)
{
	if(orientation == Qt::Horizontal) {
		mMainLayout->setDirection(QBoxLayout::LeftToRight);
		mMainLayout->setAlignment(Qt::AlignLeft | Qt::AlignCenter);
	} else {
		mMainLayout->setDirection(QBoxLayout::TopToBottom);
		mMainLayout->setAlignment(Qt::AlignTop | Qt::AlignCenter);
	}
	adjustSize();
}

QString AnnotationGeneralSettings::name() const
{
	return tr("General Settings");
}

} // namespace kImageAnnotator
