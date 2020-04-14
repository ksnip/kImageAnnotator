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

namespace kImageAnnotator {

CropWidget::CropWidget() :
	mAnnotationArea(nullptr),
    mKeyHelper(new KeyHelper()),
    mCropSelectionHandler(new CropSelectionHandler()),
    mCropView(new CropView(mCropSelectionHandler, mKeyHelper))
{
	initCropSelectionHandler();
	initKeyHelper();
	initGui();
}

void CropWidget::initCropSelectionHandler() const
{
	connect(mCropSelectionHandler, &CropSelectionHandler::selectionChanged, this, &CropWidget::selectionChanged);
}

void CropWidget::initKeyHelper()
{
	connect(mKeyHelper, &KeyHelper::escapeReleased, this, &CropWidget::closing);
	connect(mKeyHelper, &KeyHelper::returnReleased, this, &CropWidget::crop);
	connect(mKeyHelper, &KeyHelper::enterReleased, this, &CropWidget::crop);
}

CropWidget::~CropWidget()
{
	delete mKeyHelper;
	delete mCropSelectionHandler;
	delete mCropView;
	delete mMainLayout;
	delete mCropButton;
	delete mCancelButton;
	delete mPositionXLineEdit;
	delete mPositionYLineEdit;
	delete mWidthLineEdit;
	delete mHeightLineEdit;
}

void CropWidget::activate(AnnotationArea *annotationArea)
{
	Q_ASSERT(annotationArea != nullptr);

	mAnnotationArea = annotationArea;
	mCropSelectionHandler->init(annotationArea);
	mCropView->init(annotationArea);
	reset();
	setFocus();
}

void CropWidget::initGui()
{
	mCropButton = new QPushButton();
	mCropButton->setText(tr("Crop"));
	connect(mCropButton, &QPushButton::clicked, this, &CropWidget::crop);

	mCancelButton = new QPushButton();
	mCancelButton->setText(tr("Cancel"));
	connect(mCancelButton, &QPushButton::clicked, this, &CropWidget::closing);

	mPanelLayout = new QHBoxLayout();
	mPanelLayout->setAlignment(Qt::AlignCenter);

	auto label = new QLabel(tr("X:"));
	mPanelLayout->addWidget(label, 0, Qt::AlignCenter);

	mPositionXLineEdit = new QLineEdit();
	mPositionXLineEdit->setValidator(new QIntValidator(0, 9999, mPositionXLineEdit));
	mPositionXLineEdit->setFixedSize(ScaledSizeProvider::getScaledWidth(40), mPositionXLineEdit->minimumSizeHint().height());
	connect(mPositionXLineEdit, &QLineEdit::textEdited, this, &CropWidget::xChanged);
	mPanelLayout->addWidget(mPositionXLineEdit, 0, Qt::AlignCenter);

	label = new QLabel(tr("Y:"));
	mPanelLayout->addWidget(label, 0, Qt::AlignCenter);

	mPositionYLineEdit = new QLineEdit();
	mPositionYLineEdit->setValidator(new QIntValidator(0, 9999, mPositionYLineEdit));
	mPositionYLineEdit->setFixedSize(ScaledSizeProvider::getScaledWidth(40), mPositionYLineEdit->minimumSizeHint().height());
	connect(mPositionYLineEdit, &QLineEdit::textEdited, this, &CropWidget::yChanged);
	mPanelLayout->addWidget(mPositionYLineEdit, 0, Qt::AlignCenter);

	label = new QLabel(tr("W:"));
	mPanelLayout->addWidget(label, 0, Qt::AlignCenter);

	mWidthLineEdit = new QLineEdit();
	mWidthLineEdit->setValidator(new QIntValidator(0, 9999, mWidthLineEdit));
	mWidthLineEdit->setFixedSize(ScaledSizeProvider::getScaledWidth(40), mWidthLineEdit->minimumSizeHint().height());
	connect(mWidthLineEdit, &QLineEdit::textEdited, this, &CropWidget::widthChanged);
	mPanelLayout->addWidget(mWidthLineEdit, 0, Qt::AlignCenter);

	label = new QLabel(tr("H:"));
	mPanelLayout->addWidget(label, 0, Qt::AlignCenter);

	mHeightLineEdit = new QLineEdit();
	mHeightLineEdit->setValidator(new QIntValidator(0, 9999, mHeightLineEdit));
	mHeightLineEdit->setFixedSize(ScaledSizeProvider::getScaledWidth(40), mHeightLineEdit->minimumSizeHint().height());
	connect(mHeightLineEdit, &QLineEdit::textEdited, this, &CropWidget::heightChanged);
	mPanelLayout->addWidget(mHeightLineEdit, 0, Qt::AlignCenter);

	mPanelLayout->addWidget(mCropButton, 0, Qt::AlignCenter);
	mPanelLayout->addWidget(mCancelButton, 0, Qt::AlignCenter);

	mMainLayout = new QVBoxLayout();
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

	mAnnotationArea->crop(mCropSelectionHandler->selection());
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
	mCropSelectionHandler->setPositionX(x);
}

void CropWidget::yChanged(const QString &text)
{
	auto y = text.toInt();
	mCropSelectionHandler->setPositionY(y);
}

void CropWidget::widthChanged(const QString &text)
{
	auto width = text.toInt();
	mCropSelectionHandler->setWidth(width);
}

void CropWidget::heightChanged(const QString &text)
{
	auto height = text.toInt();
	mCropSelectionHandler->setHeight(height);
}

void CropWidget::reset()
{
	mCropSelectionHandler->resetSelection();
}

} // namespace kImageAnnotator
