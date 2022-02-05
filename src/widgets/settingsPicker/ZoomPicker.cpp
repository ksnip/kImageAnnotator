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

#include "ZoomPicker.h"

namespace kImageAnnotator {

ZoomPicker::ZoomPicker(QWidget *parent) :
	SettingsPickerWidget(parent),
	mLayout(new QHBoxLayout),
	mLabel(new QLabel(this)),
	mSpinBox(new CustomSpinBox(this)),
	mZoomInAction(new QAction(this)),
	mZoomOutAction(new QAction(this)),
	mResetZoomAction(new QAction(this)),
	mFitImageAction(new QAction(this))
{
	initGui();
}

QWidget *ZoomPicker::expandingWidget()
{
	return mSpinBox;
}

void ZoomPicker::initGui()
{
	mLayout->setContentsMargins(1, 0, 0, 0);

	auto icon = IconLoader::load(QLatin1String("zoom.svg"));
	mLabel->setPixmap(icon.pixmap(ScaledSizeProvider::settingsWidgetIconSize()));

	mSpinBox->setFocusPolicy(Qt::NoFocus);
	mSpinBox->setRange(10, 800);
	mSpinBox->setSingleStep(10);
	mSpinBox->setSuffix(QLatin1String("%"));
	mSpinBox->setWrapping(false);

	mFitImageAction = createAction(tr("Fit Image"), IconLoader::load(QLatin1String("fitImage.svg")));
	connect(mFitImageAction, &QAction::triggered, this, &ZoomPicker::fitImageToView);
	mFitImageButton = createButton(mFitImageAction);

	mZoomInAction->setShortcut(QKeySequence::ZoomIn);
	mZoomOutAction->setShortcut(QKeySequence::ZoomOut);
	mResetZoomAction->setShortcut(Qt::CTRL + Qt::Key_0);
	mFitImageAction->setShortcut(Qt::CTRL + Qt::Key_F);

	setToolTip(getToolTip());

	connect(mZoomInAction, &QAction::triggered, this, &ZoomPicker::zoomIn);
	connect(mZoomOutAction, &QAction::triggered, this, &ZoomPicker::zoomOut);
	connect(mResetZoomAction, &QAction::triggered, this, &ZoomPicker::resetZoomOut);

	addAction(mZoomInAction);
	addAction(mZoomOutAction);
	addAction(mResetZoomAction);

	connect(mSpinBox, &CustomSpinBox::valueChanged, this, &ZoomPicker::notifyZoomValueChanged);

	mLayout->addWidget(mLabel);
	mLayout->addWidget(mSpinBox);
	mLayout->addWidget(mFitImageButton);
	mLayout->setAlignment(Qt::AlignLeft);

	setLayout(mLayout);
}

QString ZoomPicker::getToolTip() const
{
	auto newLine = QLatin1String("\n");
	auto zoomIn = tr("Zoom In (%1)").arg(mZoomInAction->shortcut().toString());
	auto zoomOut = tr("Zoom Out (%1)").arg(mZoomOutAction->shortcut().toString());
	auto resetZoom = tr("Reset Zoom (%1)").arg(mResetZoomAction->shortcut().toString());
	auto fitZoom = tr("Fit image to view (%1)").arg(mFitImageAction->shortcut().toString());
	return zoomIn + newLine + zoomOut + newLine + resetZoom + newLine + fitZoom;
}

QAction *ZoomPicker::createAction(const QString &tooltip, const QIcon &icon)
{
	auto action = new CustomToolButtonAction(this);
	action->setIcon(icon);
	action->setToolTip(tooltip);
	action->updateDefaultWidget();
	return action;
}

CustomToolButton *ZoomPicker::createButton(QAction *defaultAction)
{
	auto button = new CustomToolButton(this);
	button->setAction(defaultAction);
	return button;
}

void ZoomPicker::setZoomValue(double value)
{
	auto zoomValue = qRound(value * 100);
	mSpinBox->setValueSilent(zoomValue);
}

void ZoomPicker::fitImageToCurrentView()
{
	emit fitImageToView();
}

void ZoomPicker::notifyZoomValueChanged(double value)
{
	emit zoomValueChanged(value / 100.0);
}

void ZoomPicker::zoomIn()
{
	int currentZoom = mSpinBox->value();
	notifyZoomValueChanged(currentZoom + 10);
}

void ZoomPicker::zoomOut()
{
	auto currentZoom = mSpinBox->value();
	notifyZoomValueChanged(currentZoom - 10);
}

void ZoomPicker::resetZoomOut()
{
	notifyZoomValueChanged(100);
}

} // namespace kImageAnnotator
