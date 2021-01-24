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
	mSpinBox(new CustomSpinBox(this)),
	mZoomInAction(new QAction(this)),
	mZoomOutAction(new QAction(this))
{
	init();
}

void ZoomIndicator::init()
{
	mLayout->setContentsMargins(0, 0, 0, 0);

	auto icon = IconLoader::load(QStringLiteral("zoom.svg"));
	mLabel->setPixmap(icon.pixmap(ScaledSizeProvider::settingsWidgetIconSize()));
	mLabel->setToolTip(tr("Zoom Level"));

	mSpinBox->setFixedSize(ScaledSizeProvider::settingsWidgetSize());
	mSpinBox->setFocusPolicy(Qt::NoFocus);
	mSpinBox->setRange(10, 800);
	mSpinBox->setSingleStep(10);
	mSpinBox->setSuffix(QLatin1String("%"));
	mSpinBox->setToolTip(mLabel->toolTip());
	mSpinBox->setWrapping(false);

	mZoomInAction->setShortcut(Qt::Key_Plus + Qt::CTRL);
	mZoomOutAction->setShortcut(Qt::Key_Minus + Qt::CTRL);

	connect(mZoomInAction, &QAction::triggered, this, &ZoomIndicator::zoomIn);
	connect(mZoomOutAction, &QAction::triggered, this, &ZoomIndicator::zoomOut);

	addAction(mZoomInAction);
	addAction(mZoomOutAction);

	connect(mSpinBox, &CustomSpinBox::valueChanged, this, &ZoomIndicator::notifyZoomValueChanged);

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
	delete mZoomInAction;
	delete mZoomOutAction;
}

void ZoomIndicator::setZoomValue(double value)
{
	auto zoomValue = qRound(value * 100);
	mSpinBox->setValueSilent(zoomValue);
}

void ZoomIndicator::notifyZoomValueChanged(double value)
{
	emit zoomValueChanged(value / 100.0);
}

void ZoomIndicator::zoomIn()
{
	int currentZoom = mSpinBox->value();
	notifyZoomValueChanged(currentZoom + 10);
}

void ZoomIndicator::zoomOut()
{
	auto currentZoom = mSpinBox->value();
	notifyZoomValueChanged(currentZoom - 10);
}

} // namespace kImageAnnotator
