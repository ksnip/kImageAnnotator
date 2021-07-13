/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
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

#include "ModifyCanvasWidget.h"

namespace kImageAnnotator {


ModifyCanvasWidget::ModifyCanvasWidget() :
	mAnnotationArea(nullptr),
	mSelectionHandler(new SelectionHandler(new ModifyCanvasSelectionRestrictor, new SelectionHandles)),
	mModifyCanvasView(new ModifyCanvasView(mSelectionHandler, mKeyHelper, this)),
	mKeyHelper(new KeyHelper()),
	mApplyButton(new QPushButton(this)),
	mCancelButton(new QPushButton(this)),
	mPanelLayout(new QHBoxLayout),
	mPositionXLabel(new QLabel(this)),
	mPositionYLabel(new QLabel(this)),
	mHeightLabel(new QLabel(this)),
	mWidthLabel(new QLabel(this)),
	mColorLabel(new QLabel(this)),
	mPositionXLineEdit(new QLineEdit(this)),
	mPositionYLineEdit(new QLineEdit(this)),
	mWidthLineEdit(new QLineEdit(this)),
	mHeightLineEdit(new QLineEdit(this)),
	mMainLayout(new QVBoxLayout(this)),
	mInputValidator(new QIntValidator(-9999, 9999, this)),
	mRestrictCheckBox(new QCheckBox(this)),
	mColorDialogButton(new ColorDialogButton(this)),
	mZoomPicker(new ZoomPicker(this))
{
	initSelectionHandler();
	initKeyHelper();
	initGui();
	initZoomPicker();
}

ModifyCanvasWidget::~ModifyCanvasWidget()
{
	delete mKeyHelper;
	delete mColorDialogButton;
	delete mZoomPicker;
	delete mSelectionHandler;
}

void ModifyCanvasWidget::activate(AnnotationArea *annotationArea)
{
	Q_ASSERT(annotationArea != nullptr);

	mAnnotationArea = annotationArea;
	mSelectionHandler->init(annotationArea);
	mModifyCanvasView->init(annotationArea);
	reset();
	setFocus();
}

void ModifyCanvasWidget::keyReleaseEvent(QKeyEvent *event)
{
	mKeyHelper->keyRelease(event);
	QWidget::keyReleaseEvent(event);
}

void ModifyCanvasWidget::initGui()
{
	mRestrictCheckBox->setText(tr("Restricted"));
	mRestrictCheckBox->setToolTip(tr("When enabled enforces the canvas\n"
									  		"to include the background image."));
	mRestrictCheckBox->setChecked(mSelectionHandler->restrictionEnabled());
	connect(mRestrictCheckBox, &QCheckBox::stateChanged, this, &ModifyCanvasWidget::restrictionChanged);

	auto width = ScaledSizeProvider::scaledWidth(80);

	mPositionXLabel->setText(tr("X:"));

	mPositionXLineEdit->setValidator(mInputValidator);
	mPositionXLineEdit->setFixedSize(width, mPositionXLineEdit->minimumSizeHint().height());
	connect(mPositionXLineEdit, &QLineEdit::textEdited, this, &ModifyCanvasWidget::xChanged);

	mPositionYLabel->setText(tr("Y:"));

	mPositionYLineEdit->setValidator(mInputValidator);
	mPositionYLineEdit->setFixedSize(width, mPositionYLineEdit->minimumSizeHint().height());
	connect(mPositionYLineEdit, &QLineEdit::textEdited, this, &ModifyCanvasWidget::yChanged);

	mWidthLabel->setText(tr("W:"));

	mWidthLineEdit->setValidator(mInputValidator);
	mWidthLineEdit->setFixedSize(width, mWidthLineEdit->minimumSizeHint().height());
	connect(mWidthLineEdit, &QLineEdit::textEdited, this, &ModifyCanvasWidget::widthChanged);

	mHeightLabel->setText(tr("H:"));

	mHeightLineEdit->setValidator(mInputValidator);
	mHeightLineEdit->setFixedSize(width, mHeightLineEdit->minimumSizeHint().height());
	connect(mHeightLineEdit, &QLineEdit::textEdited, this, &ModifyCanvasWidget::heightChanged);

	mColorLabel->setText(tr("Color:"));
	mColorLabel->setToolTip(tr("Canvas Background Color"));
	connect(mColorDialogButton, &ColorDialogButton::colorChanged, mModifyCanvasView, &ModifyCanvasView::setCanvasColor);

	mApplyButton->setText(tr("Apply"));
	connect(mApplyButton, &QPushButton::clicked, this, &ModifyCanvasWidget::apply);

	mCancelButton->setText(tr("Cancel"));
	connect(mCancelButton, &QPushButton::clicked, this, &ModifyCanvasWidget::closing);

	mPanelLayout->setAlignment(Qt::AlignCenter);
	mPanelLayout->addWidget(mZoomPicker);
	mPanelLayout->addStretch(1);
	mPanelLayout->addWidget(mRestrictCheckBox);
	mPanelLayout->addSpacing(10);
	mPanelLayout->addWidget(mColorLabel);
	mPanelLayout->addWidget(mColorDialogButton);
	mPanelLayout->addSpacing(10);
	mPanelLayout->addWidget(mPositionXLabel);
	mPanelLayout->addWidget(mPositionXLineEdit);
	mPanelLayout->addWidget(mPositionYLabel);
	mPanelLayout->addWidget(mPositionYLineEdit);
	mPanelLayout->addWidget(mWidthLabel);
	mPanelLayout->addWidget(mWidthLineEdit);
	mPanelLayout->addWidget(mHeightLabel);
	mPanelLayout->addWidget(mHeightLineEdit);
	mPanelLayout->addStretch(1);
	mPanelLayout->addWidget(mApplyButton);
	mPanelLayout->addWidget(mCancelButton);

	mMainLayout->addWidget(mModifyCanvasView);
	mMainLayout->addLayout(mPanelLayout);

	setLayout(mMainLayout);
}

void ModifyCanvasWidget::initKeyHelper()
{
	connect(mKeyHelper, &KeyHelper::escapeReleased, this, &ModifyCanvasWidget::closing);
	connect(mKeyHelper, &KeyHelper::returnReleased, this, &ModifyCanvasWidget::apply);
	connect(mKeyHelper, &KeyHelper::enterReleased, this, &ModifyCanvasWidget::apply);
}

void ModifyCanvasWidget::initSelectionHandler() const
{
	connect(mSelectionHandler, &SelectionHandler::selectionChanged, this, &ModifyCanvasWidget::selectionChanged);
	connect(mSelectionHandler, &SelectionHandler::selectionChanged, mModifyCanvasView, &ModifyCanvasView::setCanvasRect);
}

void ModifyCanvasWidget::reset()
{
	auto selection = mAnnotationArea->canvasRect();
	auto selectionLimit = mAnnotationArea->sceneRect();
	mSelectionHandler->resetSelection(selection, selectionLimit);
	mColorDialogButton->setColor(mAnnotationArea->canvasColor());
	mModifyCanvasView->setCanvasColor(mAnnotationArea->canvasColor());
	mModifyCanvasView->setCanvasRect(mAnnotationArea->canvasRect());
}

void ModifyCanvasWidget::initZoomPicker()
{
	auto zoomValueProvider = mModifyCanvasView->zoomValueProvider();
	connect(zoomValueProvider, &ZoomValueProvider::zoomValueChanged, mZoomPicker, &ZoomPicker::setZoomValue);
	connect(mZoomPicker, &ZoomPicker::zoomValueChanged, zoomValueProvider, &ZoomValueProvider::setZoomValue);
	mZoomPicker->setZoomValue(zoomValueProvider->zoomValue());
}

void ModifyCanvasWidget::apply()
{
	mAnnotationArea->modifyCanvas(mSelectionHandler->selection(), mColorDialogButton->color());
	emit closing();
}

void ModifyCanvasWidget::selectionChanged(const QRectF &rect)
{
	mPositionXLineEdit->setText(QString::number(rect.topLeft().x()));
	mPositionYLineEdit->setText(QString::number(rect.topLeft().y()));
	mWidthLineEdit->setText(QString::number(rect.width()));
	mHeightLineEdit->setText(QString::number(rect.height()));
}

void ModifyCanvasWidget::xChanged(const QString &text)
{
	auto x = text.toInt();
	mSelectionHandler->setPositionX(x);
}

void ModifyCanvasWidget::yChanged(const QString &text)
{
	auto y = text.toInt();
	mSelectionHandler->setPositionY(y);
}

void ModifyCanvasWidget::widthChanged(const QString &text)
{
	auto width = text.toInt();
	mSelectionHandler->setWidth(width);
}

void ModifyCanvasWidget::heightChanged(const QString &text)
{
	auto height = text.toInt();
	mSelectionHandler->setHeight(height);
}

void ModifyCanvasWidget::restrictionChanged()
{
	mSelectionHandler->setRestrictionEnabled(mRestrictCheckBox->isChecked());
}

} // kImageAnnotator namespace
