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

#include "ZoomIndicator.h"

namespace kImageAnnotator {

ZoomIndicator::ZoomIndicator(QWidget *parent) :
	QWidget(parent),
	mLayout(new QHBoxLayout),
	mLabel(new QLabel(this)),
	mSpinBox(new QSpinBox(this))
{
	init();
}

void ZoomIndicator::init()
{
	mLayout->setContentsMargins(0, 0, 0, 0);
	
	auto icon = IconLoader::load(QLatin1String("zoom.svg"));
	mLabel->setPixmap(icon.pixmap(ScaledSizeProvider::settingsWidgetIconSize()));
	mLabel->setToolTip(tr("Zoom Level"));

	mSpinBox->setFixedSize(ScaledSizeProvider::settingsWidgetSize());
	mSpinBox->setFocusPolicy(Qt::NoFocus);
	mSpinBox->setReadOnly(true);
	mSpinBox->setRange(0, 800);
	mSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
	mSpinBox->setSuffix(QLatin1String("%"));
	mSpinBox->setToolTip(mLabel->toolTip());

	mLayout->addWidget(mLabel);
	mLayout->addWidget(mSpinBox);

	setLayout(mLayout);
	setFixedSize(sizeHint());
}

ZoomIndicator::~ZoomIndicator()
{
	delete mLabel;
	delete mSpinBox;
	delete mLayout;
}

void ZoomIndicator::setZoomLevel(double zoomLevel)
{
	auto zoomValue = qRound(zoomLevel * 100);
	mSpinBox->setValue(zoomValue);
}

} // namespace kImageAnnotator
