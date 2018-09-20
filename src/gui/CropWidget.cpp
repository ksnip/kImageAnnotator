/*
 * Copyright (C) 2018 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
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

kImageAnnotator::CropWidget::CropWidget(kImageAnnotator::AnnotationArea *annotationArea)
{
	mAnnotationArea = annotationArea;
	mCropView = new CropView(annotationArea);

	initGui();
}

kImageAnnotator::CropWidget::~CropWidget()
{
	delete mMainLayout;
	delete mPanelLayout;
	delete mCropButton;
	delete mCancelButton;
	delete mPositionXLineEdit;
	delete mPositionYLineEdit;
	delete mWidthLineEdit;
	delete mHeightLineEdit;
}

void kImageAnnotator::CropWidget::initGui()
{
	mCropButton = new QPushButton();
	mCropButton->setText(tr("Crop"));
	connect(mCropButton, &QPushButton::clicked, this, &CropWidget::crop);

	mCancelButton = new QPushButton();
	mCancelButton->setText(tr("Cancel"));
	connect(mCancelButton, &QPushButton::clicked, this, &CropWidget::close);

	mPanelLayout = new QHBoxLayout();
	mPanelLayout->setAlignment(Qt::AlignCenter);

	auto label = new QLabel(tr("X:"));
	mPanelLayout->addWidget(label, 0, Qt::AlignCenter);

	mPositionXLineEdit = new QLineEdit();
	mPositionXLineEdit->setValidator(new QIntValidator(0, 9999, mPositionXLineEdit));
	mPositionXLineEdit->setFixedSize(40, mPositionXLineEdit->minimumSizeHint().height());
	connect(mPositionXLineEdit, &QLineEdit::textEdited, this, &CropWidget::xChanged);
	mPanelLayout->addWidget(mPositionXLineEdit, 0, Qt::AlignCenter);

	label = new QLabel(tr("Y:"));
	mPanelLayout->addWidget(label, 0, Qt::AlignCenter);

	mPositionYLineEdit = new QLineEdit();
	mPositionYLineEdit->setValidator(new QIntValidator(0, 9999, mPositionYLineEdit));
	mPositionYLineEdit->setFixedSize(40, mPositionYLineEdit->minimumSizeHint().height());
	connect(mPositionYLineEdit, &QLineEdit::textEdited, this, &CropWidget::yChanged);
	mPanelLayout->addWidget(mPositionYLineEdit, 0, Qt::AlignCenter);

	label = new QLabel(tr("W:"));
	mPanelLayout->addWidget(label, 0, Qt::AlignCenter);

	mWidthLineEdit = new QLineEdit();
	mWidthLineEdit->setValidator(new QIntValidator(0, 9999, mWidthLineEdit));
	mWidthLineEdit->setFixedSize(40, mWidthLineEdit->minimumSizeHint().height());
	connect(mWidthLineEdit, &QLineEdit::textEdited, this, &CropWidget::widthChanged);
	mPanelLayout->addWidget(mWidthLineEdit, 0, Qt::AlignCenter);

	label = new QLabel(tr("H:"));
	mPanelLayout->addWidget(label, 0, Qt::AlignCenter);

	mHeightLineEdit = new QLineEdit();
	mHeightLineEdit->setValidator(new QIntValidator(0, 9999, mHeightLineEdit));
	mHeightLineEdit->setFixedSize(40, mHeightLineEdit->minimumSizeHint().height());
	connect(mHeightLineEdit, &QLineEdit::textEdited, this, &CropWidget::heightChanged);
	mPanelLayout->addWidget(mHeightLineEdit, 0, Qt::AlignCenter);

	mPanelLayout->addWidget(mCropButton, 0, Qt::AlignCenter);
	mPanelLayout->addWidget(mCancelButton, 0, Qt::AlignCenter);

	mMainLayout = new QVBoxLayout();
	mMainLayout->addWidget(mCropView);
	mMainLayout->addLayout(mPanelLayout);

	setLayout(mMainLayout);
}

void kImageAnnotator::CropWidget::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Escape) {
		emit done();
	} else if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
		crop();
	}
	QWidget::keyPressEvent(event);
}

void kImageAnnotator::CropWidget::crop()
{
//	mAnnotationArea->crop(QRECT);
	emit done();
}

void kImageAnnotator::CropWidget::selectedRectChanged(const QRectF &rect)
{
	mPositionXLineEdit->setText(QString::number(rect.topLeft().x()));
	mPositionYLineEdit->setText(QString::number(rect.topLeft().y()));
	mWidthLineEdit->setText(QString::number(rect.width()));
	mHeightLineEdit->setText(QString::number(rect.height()));
}

void kImageAnnotator::CropWidget::xChanged(const QString &text)
{
//	auto x = text.toInt();
//	auto rect = mCaptureView->cropRect();
//
//	// Can't enter negative number
//	if ((x + rect.width()) <= mCaptureView->sceneRect().width()) {
//		rect.moveTo(x, rect.y());
//		mCaptureView->setCropRect(rect);
//	} else {
//		rect.moveTo(mCaptureView->sceneRect().width() - rect.width(), rect.y());
//		mCaptureView->setCropRect(rect);
//		selectedRectChanged(rect);
//	}
}

void kImageAnnotator::CropWidget::yChanged(const QString &text)
{
//	auto y = text.toInt();
//	auto rect = mCaptureView->cropRect();
//
//	// Can't enter negative number
//	if ((y + rect.height()) <= mCaptureView->sceneRect().height()) {
//		rect.moveTo(rect.x(), y);
//		mCaptureView->setCropRect(rect);
//	} else {
//		rect.moveTo(rect.x(), mCaptureView->sceneRect().height() - rect.height());
//		mCaptureView->setCropRect(rect);
//		selectedRectChanged(rect);
//	}
}

void kImageAnnotator::CropWidget::widthChanged(const QString &text)
{
//	auto width = text.toInt();
//	auto rect = mCaptureView->cropRect();
//
//	// Can't enter negative number
//	if ((rect.x() + width) <= mCaptureView->sceneRect().width()) {
//		rect.setWidth(width);
//		mCaptureView->setCropRect(rect);
//	} else {
//		rect.setWidth(mCaptureView->sceneRect().width() - rect.x());
//		mCaptureView->setCropRect(rect);
//		selectedRectChanged(rect);
//	}
}

void kImageAnnotator::CropWidget::heightChanged(const QString &text)
{
//	auto height = text.toInt();
//	auto rect = mCaptureView->cropRect();
//
//	// Can't enter negative number
//	if ((rect.y() + height) <= mCaptureView->sceneRect().height()) {
//		rect.setHeight(height);
//		mCaptureView->setCropRect(rect);
//	} else {
//		rect.setHeight(mCaptureView->sceneRect().height() - rect.y());
//		mCaptureView->setCropRect(rect);
//		selectedRectChanged(rect);
//	}
}
