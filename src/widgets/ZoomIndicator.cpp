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
	mZoomOutAction(new QAction(this)),
	mResetZoomAction(new QAction(this))
{
	initGui();
}

ZoomIndicator::~ZoomIndicator()
{
	delete mLabel;
	delete mSpinBox;
	delete mLayout;
	delete mZoomInAction;
	delete mZoomOutAction;
	delete mResetZoomAction;
}

QWidget *ZoomIndicator::expandingWidget()
{
	return mSpinBox;
}

void ZoomIndicator::initGui()
{
	mLayout->setContentsMargins(1, 0, 0, 0);

	auto icon = IconLoader::load(QLatin1String("zoom.svg"));
	mLabel->setPixmap(icon.pixmap(ScaledSizeProvider::settingsWidgetIconSize()));

	mSpinBox->setFocusPolicy(Qt::NoFocus);
	mSpinBox->setRange(10, 800);
	mSpinBox->setSingleStep(10);
	mSpinBox->setSuffix(QLatin1String("%"));
	mSpinBox->setWrapping(false);

	mZoomInAction->setShortcut(QKeySequence::ZoomIn);
	mZoomOutAction->setShortcut(QKeySequence::ZoomOut);
	mResetZoomAction->setShortcut(Qt::CTRL + Qt::Key_0);

	setToolTip(getToolTip());

	connect(mZoomInAction, &QAction::triggered, this, &ZoomIndicator::zoomIn);
	connect(mZoomOutAction, &QAction::triggered, this, &ZoomIndicator::zoomOut);
	connect(mResetZoomAction, &QAction::triggered, this, &ZoomIndicator::resetZoomOut);

	addAction(mZoomInAction);
	addAction(mZoomOutAction);
	addAction(mResetZoomAction);

	connect(mSpinBox, &CustomSpinBox::valueChanged, this, &ZoomIndicator::notifyZoomValueChanged);

	mLayout->addWidget(mLabel);
	mLayout->addWidget(mSpinBox);
	mLayout->setAlignment(Qt::AlignLeft);

	setLayout(mLayout);
}

QString ZoomIndicator::getToolTip() const
{
	auto newLine = QLatin1String("\n");
	auto zoomIn = tr("Zoom In (%1)").arg(mZoomInAction->shortcut().toString());
	auto zoomOut = tr("Zoom Out (%1)").arg(mZoomOutAction->shortcut().toString());
	auto resetZoom = tr("Reset Zoom (%1)").arg(mResetZoomAction->shortcut().toString());
	return zoomIn + newLine + zoomOut + newLine + resetZoom;
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

void ZoomIndicator::resetZoomOut()
{
	notifyZoomValueChanged(100);
}

} // namespace kImageAnnotator
