/*
 * Copyright (C) 2018 Damir Porobic <damir.porobic@gmx.com>
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

#include "CropWidget.h"

namespace kImageAnnotator {

CropWidget::CropWidget() :
	mAnnotationArea(nullptr),
	mKeyHelper(new KeyHelper()),
	mSelectionHandler(new SelectionHandler(new CropSelectionRestrictor)),
	mCropView(new CropView(mSelectionHandler, mKeyHelper, this)),
	mCropButton(new QPushButton(this)),
	mCancelButton(new QPushButton(this)),
	mPanelLayout(new QHBoxLayout),
	mPositionXLabel(new QLabel(this)),
	mPositionYLabel(new QLabel(this)),
	mHeightLabel(new QLabel(this)),
	mWidthLabel(new QLabel(this)),
	mPositionXLineEdit(new QLineEdit(this)),
	mPositionYLineEdit(new QLineEdit(this)),
	mWidthLineEdit(new QLineEdit(this)),
	mHeightLineEdit(new QLineEdit(this)),
	mMainLayout(new QVBoxLayout(this)),
	mInputValidator(new QIntValidator(0, 9999, this)),
	mZoomPicker(new ZoomPicker(this))
{
	initSelectionHandler();
	initKeyHelper();
	initGui();
	initZoomPicker();
}

CropWidget::~CropWidget()
{
	delete mKeyHelper;
	delete mSelectionHandler;
	delete mCropView;
	delete mZoomPicker;
}

void CropWidget::activate(AnnotationArea *annotationArea)
{
	Q_ASSERT(annotationArea != nullptr);

	mAnnotationArea = annotationArea;
	mSelectionHandler->init(annotationArea);
	mCropView->init(annotationArea);
	reset();
	setFocus();
}

void CropWidget::initGui()
{
	mCropButton->setText(tr("Apply"));
	connect(mCropButton, &QPushButton::clicked, this, &CropWidget::crop);

	mCancelButton->setText(tr("Cancel"));
	connect(mCancelButton, &QPushButton::clicked, this, &CropWidget::closing);


	auto width = ScaledSizeProvider::scaledWidth(80);

	mPositionXLabel->setText(tr("X:"));

	mPositionXLineEdit->setValidator(mInputValidator);
	mPositionXLineEdit->setFixedSize(width, mPositionXLineEdit->minimumSizeHint().height());

	connect(mPositionXLineEdit, &QLineEdit::textEdited, this, &CropWidget::xChanged);

	mPositionYLabel->setText(tr("Y:"));

	mPositionYLineEdit->setValidator(mInputValidator);
	mPositionYLineEdit->setFixedSize(width, mPositionYLineEdit->minimumSizeHint().height());

	connect(mPositionYLineEdit, &QLineEdit::textEdited, this, &CropWidget::yChanged);

	mWidthLabel->setText(tr("W:"));

	mWidthLineEdit->setValidator(mInputValidator);
	mWidthLineEdit->setFixedSize(width, mWidthLineEdit->minimumSizeHint().height());

	connect(mWidthLineEdit, &QLineEdit::textEdited, this, &CropWidget::widthChanged);

	mHeightLabel->setText(tr("H:"));

	mHeightLineEdit->setValidator(mInputValidator);
	mHeightLineEdit->setFixedSize(width, mHeightLineEdit->minimumSizeHint().height());

	connect(mHeightLineEdit, &QLineEdit::textEdited, this, &CropWidget::heightChanged);

	mPanelLayout->setAlignment(Qt::AlignCenter);
	mPanelLayout->addWidget(mZoomPicker);
	mPanelLayout->addStretch(1);
	mPanelLayout->addWidget(mPositionXLabel);
	mPanelLayout->addWidget(mPositionXLineEdit);
	mPanelLayout->addWidget(mPositionYLabel);
	mPanelLayout->addWidget(mPositionYLineEdit);
	mPanelLayout->addWidget(mWidthLabel);
	mPanelLayout->addWidget(mWidthLineEdit);
	mPanelLayout->addWidget(mHeightLabel);
	mPanelLayout->addWidget(mHeightLineEdit);
	mPanelLayout->addStretch(1);
	mPanelLayout->addWidget(mCropButton);
	mPanelLayout->addWidget(mCancelButton);

	mMainLayout->addWidget(mCropView);
	mMainLayout->addLayout(mPanelLayout);

	setLayout(mMainLayout);
}

void CropWidget::keyReleaseEvent(QKeyEvent *event)
{
	mKeyHelper->keyRelease(event);
	QWidget::keyReleaseEvent(event);
}

void CropWidget::crop()
{
	Q_ASSERT(mAnnotationArea != nullptr);

	mAnnotationArea->crop(mSelectionHandler->selection());
	emit closing();
}

void CropWidget::selectionChanged(const QRectF &rect)
{
	mPositionXLineEdit->setText(QString::number(rect.topLeft().x()));
	mPositionYLineEdit->setText(QString::number(rect.topLeft().y()));
	mWidthLineEdit->setText(QString::number(rect.width()));
	mHeightLineEdit->setText(QString::number(rect.height()));
}

void kImageAnnotator::CropWidget::xChanged(const QString &text)
{
	auto x = text.toInt();
	mSelectionHandler->setPositionX(x);
}

void CropWidget::yChanged(const QString &text)
{
	auto y = text.toInt();
	mSelectionHandler->setPositionY(y);
}

void CropWidget::widthChanged(const QString &text)
{
	auto width = text.toInt();
	mSelectionHandler->setWidth(width);
}

void CropWidget::heightChanged(const QString &text)
{
	auto height = text.toInt();
	mSelectionHandler->setHeight(height);
}

void CropWidget::reset()
{
	auto selection = mAnnotationArea->backgroundImageRect();
	mSelectionHandler->resetSelection(selection, selection);
}

void CropWidget::initZoomPicker() const
{
	auto zoomValueProvider = mCropView->zoomValueProvider();
	connect(zoomValueProvider, &ZoomValueProvider::zoomValueChanged, mZoomPicker, &ZoomPicker::setZoomValue);
	connect(mZoomPicker, &ZoomPicker::zoomValueChanged, zoomValueProvider, &ZoomValueProvider::setZoomValue);
	mZoomPicker->setZoomValue(zoomValueProvider->zoomValue());
}

void CropWidget::initSelectionHandler() const
{
	connect(mSelectionHandler, &SelectionHandler::selectionChanged, this, &CropWidget::selectionChanged);
}

void CropWidget::initKeyHelper()
{
	connect(mKeyHelper, &KeyHelper::escapeReleased, this, &CropWidget::closing);
	connect(mKeyHelper, &KeyHelper::returnReleased, this, &CropWidget::crop);
	connect(mKeyHelper, &KeyHelper::enterReleased, this, &CropWidget::crop);
}

} // namespace kImageAnnotator
