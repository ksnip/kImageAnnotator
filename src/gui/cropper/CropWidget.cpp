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
	mCropView(new CropView(mSelectionHandler, mKeyHelper)),
	mCropButton(new QPushButton),
	mCancelButton(new QPushButton),
	mPanelLayout(new QHBoxLayout),
	mPositionXLabel(new QLabel),
	mPositionYLabel(new QLabel),
	mHeightLabel(new QLabel),
	mWidthLabel(new QLabel),
	mPositionXLineEdit(new QLineEdit),
	mPositionYLineEdit(new QLineEdit),
	mWidthLineEdit(new QLineEdit),
	mHeightLineEdit(new QLineEdit),
	mMainLayout(new QVBoxLayout),
	mInputValidator(new QIntValidator(0, 9999, this))
{
	initSelectionHandler();
	initKeyHelper();
	initGui();
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

CropWidget::~CropWidget()
{
	delete mKeyHelper;
	delete mSelectionHandler;
	delete mCropView;
	delete mMainLayout;
	delete mCropButton;
	delete mCancelButton;
	delete mPositionXLineEdit;
	delete mPositionYLineEdit;
	delete mWidthLineEdit;
	delete mHeightLineEdit;
	delete mPositionXLabel;
	delete mPositionYLabel;
	delete mWidthLabel;
	delete mHeightLabel;
	delete mInputValidator;
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
	mCropButton->setText(tr("Crop"));
	connect(mCropButton, &QPushButton::clicked, this, &CropWidget::crop);

	mCancelButton->setText(tr("Cancel"));
	connect(mCancelButton, &QPushButton::clicked, this, &CropWidget::closing);

	mPanelLayout->setAlignment(Qt::AlignCenter);

	auto width = ScaledSizeProvider::scaledWidth(40);

	mPositionXLabel->setText(tr("X:"));
	mPanelLayout->addWidget(mPositionXLabel, 0, Qt::AlignCenter);


	mPositionXLineEdit->setValidator(mInputValidator);
	mPositionXLineEdit->setFixedSize(width, mPositionXLineEdit->minimumSizeHint().height());

	connect(mPositionXLineEdit, &QLineEdit::textEdited, this, &CropWidget::xChanged);
	mPanelLayout->addWidget(mPositionXLineEdit, 0, Qt::AlignCenter);

	mPositionYLabel->setText(tr("Y:"));
	mPanelLayout->addWidget(mPositionYLabel, 0, Qt::AlignCenter);

	mPositionYLineEdit->setValidator(mInputValidator);
	mPositionYLineEdit->setFixedSize(width, mPositionYLineEdit->minimumSizeHint().height());

	connect(mPositionYLineEdit, &QLineEdit::textEdited, this, &CropWidget::yChanged);
	mPanelLayout->addWidget(mPositionYLineEdit, 0, Qt::AlignCenter);

	mWidthLabel->setText(tr("W:"));
	mPanelLayout->addWidget(mWidthLabel, 0, Qt::AlignCenter);

	mWidthLineEdit->setValidator(mInputValidator);
	mWidthLineEdit->setFixedSize(width, mWidthLineEdit->minimumSizeHint().height());

	connect(mWidthLineEdit, &QLineEdit::textEdited, this, &CropWidget::widthChanged);
	mPanelLayout->addWidget(mWidthLineEdit, 0, Qt::AlignCenter);

	mHeightLabel->setText(tr("H:"));
	mPanelLayout->addWidget(mHeightLabel, 0, Qt::AlignCenter);

	mHeightLineEdit->setValidator(mInputValidator);
	mHeightLineEdit->setFixedSize(width, mHeightLineEdit->minimumSizeHint().height());

	connect(mHeightLineEdit, &QLineEdit::textEdited, this, &CropWidget::heightChanged);
	mPanelLayout->addWidget(mHeightLineEdit, 0, Qt::AlignCenter);

	mPanelLayout->addWidget(mCropButton, 0, Qt::AlignCenter);
	mPanelLayout->addWidget(mCancelButton, 0, Qt::AlignCenter);

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
	auto selection = mAnnotationArea->sceneRect();
	mSelectionHandler->resetSelection(selection, selection);
}

} // namespace kImageAnnotator
