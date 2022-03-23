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

#include "CutWidget.h"

namespace kImageAnnotator {

CutWidget::CutWidget(QWidget *parent) :
	QWidget(parent),
	mAnnotationArea(nullptr),
	mKeyHelper(new KeyHelper()),
	mSelectionHandler(new SelectionHandler(new CutSelectionRestrictor, QSharedPointer<ISelectionHandles>(new SelectionHandlesVertical))),
	mCutView(new CutView(mSelectionHandler, mKeyHelper, this)),
	mZoomPicker(new ZoomPicker(this)),
	mApplyButton(new QPushButton(this)),
	mCancelButton(new QPushButton(this)),
	mOrientationGroupBox(new QGroupBox(this)),
	mVerticalOrientationRadioButton(new QRadioButton(this)),
	mHorizontalOrientationRadioButton(new QRadioButton(this)),
	mPanelLayout(new QHBoxLayout),
	mOrientationLayout(new QHBoxLayout),
	mMainLayout(new QVBoxLayout(this)),
	mDefaultSelectionWidth(100)
{
	initKeyHelper();
	initGui();
	initZoomPicker();
}

void CutWidget::activate(AnnotationArea *annotationArea)
{
	Q_ASSERT(annotationArea != nullptr);

	mAnnotationArea = annotationArea;
	mSelectionHandler->init(annotationArea);
	mCutView->init(annotationArea);
	reset();
	setFocus();
}

void CutWidget::initGui()
{
	mVerticalOrientationRadioButton->setText(tr("Vertical"));
	connect(mVerticalOrientationRadioButton, &QRadioButton::clicked, this, &CutWidget::orientationChanged);
	mVerticalOrientationRadioButton->setChecked(true);
	
	mHorizontalOrientationRadioButton->setText(tr("Horizontal"));
	connect(mHorizontalOrientationRadioButton, &QRadioButton::clicked, this, &CutWidget::orientationChanged);

	mApplyButton->setText(tr("Apply"));
	connect(mApplyButton, &QPushButton::clicked, this, &CutWidget::cut);

	mCancelButton->setText(tr("Cancel"));
	connect(mCancelButton, &QPushButton::clicked, this, &CutWidget::closing);

	mOrientationLayout->addWidget(mVerticalOrientationRadioButton);
	mOrientationLayout->addWidget(mHorizontalOrientationRadioButton);
	mOrientationLayout->addStretch(1);

	mOrientationGroupBox->setLayout(mOrientationLayout);
	mOrientationGroupBox->setFlat(true);

	mPanelLayout->setAlignment(Qt::AlignCenter);
	mPanelLayout->addWidget(mZoomPicker);
	mPanelLayout->addStretch(1);
	mPanelLayout->addWidget(mOrientationGroupBox);
	mPanelLayout->addStretch(1);
	mPanelLayout->addWidget(mApplyButton);
	mPanelLayout->addWidget(mCancelButton);

	mMainLayout->addWidget(mCutView);
	mMainLayout->addLayout(mPanelLayout);

	setLayout(mMainLayout);
}

void CutWidget::initKeyHelper()
{
	connect(mKeyHelper, &KeyHelper::escapeReleased, this, &CutWidget::closing);
	connect(mKeyHelper, &KeyHelper::returnReleased, this, &CutWidget::cut);
	connect(mKeyHelper, &KeyHelper::enterReleased, this, &CutWidget::cut);
}

void CutWidget::reset()
{
	auto selectionLimit = mAnnotationArea->backgroundImageRect();
	auto selection = selectionLimit;

	if (isVerticalOrientation()) {
		selection.setWidth(mDefaultSelectionWidth);
		selection.moveLeft(selectionLimit.center().x() - mDefaultSelectionWidth / 2);
	} else {
		selection.setHeight(mDefaultSelectionWidth);
		selection.moveTop(selectionLimit.center().y() - mDefaultSelectionWidth / 2);
	}

	mSelectionHandler->resetSelection(selection, selectionLimit);
}

void CutWidget::initZoomPicker() const
{
	auto zoomValueProvider = mCutView->zoomValueProvider();
	connect(zoomValueProvider, &ZoomValueProvider::zoomValueChanged, mZoomPicker, &ZoomPicker::setZoomValue);
	connect(mZoomPicker, &ZoomPicker::zoomValueChanged, zoomValueProvider, &ZoomValueProvider::setZoomValue);
	connect(mZoomPicker, &ZoomPicker::fitImageToView, zoomValueProvider, &ZoomValueProvider::fitImageToView);
	mZoomPicker->setZoomValue(zoomValueProvider->zoomValue());
}

void CutWidget::cut()
{
	Q_ASSERT(mAnnotationArea != nullptr);

	mAnnotationArea->cut(mSelectionHandler->selection());
	emit closing();
}

void CutWidget::orientationChanged()
{
	if(isVerticalOrientation()) {
		mSelectionHandler->replaceHandles(QSharedPointer<ISelectionHandles>(new SelectionHandlesVertical));
	} else {
		mSelectionHandler->replaceHandles(QSharedPointer<ISelectionHandles>(new SelectionHandlesHorizontal));
	}
	reset();
}

bool CutWidget::isVerticalOrientation() const
{
	return mVerticalOrientationRadioButton->isChecked();
}

} // kImageAnnotator namespace
