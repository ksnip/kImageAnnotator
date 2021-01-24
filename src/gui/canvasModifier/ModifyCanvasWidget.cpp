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
	mSelectionHandler(new SelectionHandler(new ModifyCanvasSelectionRestrictor)),
	mModifyCanvasView(new ModifyCanvasView(mSelectionHandler, mKeyHelper)),
	mKeyHelper(new KeyHelper()),
	mApplyButton(new QPushButton),
	mCancelButton(new QPushButton),
	mPanelLayout(new QHBoxLayout),
	mPositionXLabel(new QLabel),
	mPositionYLabel(new QLabel),
	mHeightLabel(new QLabel),
	mWidthLabel(new QLabel),
	mColorLabel(new QLabel),
	mPositionXLineEdit(new QLineEdit),
	mPositionYLineEdit(new QLineEdit),
	mWidthLineEdit(new QLineEdit),
	mHeightLineEdit(new QLineEdit),
	mMainLayout(new QVBoxLayout),
	mInputValidator(new QIntValidator(-9999, 9999, this)),
	mRestrictCheckBox(new QCheckBox),
	mColorDialogButton(new ColorDialogButton(this))
{
	initSelectionHandler();
	initKeyHelper();
	initGui();
}

ModifyCanvasWidget::~ModifyCanvasWidget()
{
	delete mKeyHelper;
	delete mMainLayout;
	delete mApplyButton;
	delete mCancelButton;
	delete mPositionXLineEdit;
	delete mPositionYLineEdit;
	delete mWidthLineEdit;
	delete mHeightLineEdit;
	delete mPositionXLabel;
	delete mPositionYLabel;
	delete mWidthLabel;
	delete mHeightLabel;
	delete mColorLabel;
	delete mInputValidator;
	delete mRestrictCheckBox;
	delete mColorDialogButton;
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

	auto width = ScaledSizeProvider::scaledWidth(40);

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
	mPanelLayout->addWidget(mRestrictCheckBox, 0, Qt::AlignCenter);
	mPanelLayout->addSpacing(10);
	mPanelLayout->addWidget(mColorLabel, 0, Qt::AlignCenter);
	mPanelLayout->addWidget(mColorDialogButton, 0, Qt::AlignCenter);
	mPanelLayout->addSpacing(10);
	mPanelLayout->addWidget(mPositionXLabel, 0, Qt::AlignCenter);
	mPanelLayout->addWidget(mPositionXLineEdit, 0, Qt::AlignCenter);
	mPanelLayout->addWidget(mPositionYLabel, 0, Qt::AlignCenter);
	mPanelLayout->addWidget(mPositionYLineEdit, 0, Qt::AlignCenter);
	mPanelLayout->addWidget(mWidthLabel, 0, Qt::AlignCenter);
	mPanelLayout->addWidget(mWidthLineEdit, 0, Qt::AlignCenter);
	mPanelLayout->addWidget(mHeightLabel, 0, Qt::AlignCenter);
	mPanelLayout->addWidget(mHeightLineEdit, 0, Qt::AlignCenter);
	mPanelLayout->addWidget(mApplyButton, 0, Qt::AlignCenter);
	mPanelLayout->addWidget(mCancelButton, 0, Qt::AlignCenter);

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
