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

#include "RotateDialog.h"

namespace kImageAnnotator {

RotateDialog::RotateDialog(QWidget *parent) :
	QDialog(parent, Qt::WindowTitleHint | Qt::WindowCloseButtonHint),
	m180RadioButton(new QRadioButton(this)),
	m90ClockwiseRadioButton(new QRadioButton(this)),
	m90CounterClockwiseRadioButton(new QRadioButton(this)),
	mArbitraryRotationRadioButton(new QRadioButton(this)),
	mFlipHorizontalRadioButton(new QRadioButton(this)),
	mFlipVerticalRadioButton(new QRadioButton(this)),
	mArbitraryRotationSpinBox(new CustomSpinBox(this)),
	mOkButton(new QPushButton(this)),
	mCancelButton(new QPushButton(this)),
	mRotateRadioButtonLayout(new QGridLayout),
	mFlipRadioButtonLayout(new QGridLayout),
	mRotateButtonGroupBox(new QGroupBox(this)),
	mFlipButtonGroupBox(new QGroupBox(this)),
	mButtonRowLayout(new QHBoxLayout),
	mMainLayout(new QVBoxLayout),
	mButtonGroup(new QButtonGroup(this))
{
	setWindowTitle(tr("Rotate Image"));

	initGui();

	setDefault();
}

RotateDialog::~RotateDialog()
{
	delete m180RadioButton;
	delete m90ClockwiseRadioButton;
	delete m90CounterClockwiseRadioButton;
	delete mArbitraryRotationRadioButton;
	delete mFlipHorizontalRadioButton;
	delete mFlipVerticalRadioButton;
	delete mArbitraryRotationSpinBox;
	delete mOkButton;
	delete mCancelButton;
	delete mRotateRadioButtonLayout;
	delete mFlipRadioButtonLayout;
	delete mRotateButtonGroupBox;
	delete mFlipButtonGroupBox;
	delete mButtonRowLayout;
	delete mMainLayout;
	delete mButtonGroup;
}

void RotateDialog::initGui()
{
	m180RadioButton->setText(tr("180°"));
	m180RadioButton->setChecked(true);
	mButtonGroup->addButton(m180RadioButton);

	m90ClockwiseRadioButton->setText(tr("90° Clockwise"));
	mButtonGroup->addButton(m90ClockwiseRadioButton);

	m90CounterClockwiseRadioButton->setText(tr("90° Counter Clockwise"));
	mButtonGroup->addButton(m90CounterClockwiseRadioButton);

	mArbitraryRotationRadioButton->setText(tr("Arbitrary"));
	mArbitraryRotationRadioButton->setToolTip(tr("Positive values rotate clockwise, negative values counter clockwise.\n"
											        "Rotating by non 90° multipliers might introduce loss of quality."));
	mButtonGroup->addButton(mArbitraryRotationRadioButton);

	mArbitraryRotationSpinBox->setSuffix(QString::fromUtf8("°"));
	mArbitraryRotationSpinBox->setToolTip(mArbitraryRotationRadioButton->toolTip());
	mArbitraryRotationSpinBox->setMinimum(-360);
	mArbitraryRotationSpinBox->setMaximum(360);

	mFlipHorizontalRadioButton->setText(tr("Horizontal"));
	mButtonGroup->addButton(mFlipHorizontalRadioButton);

	mFlipVerticalRadioButton->setText(tr("Vertical"));
	mButtonGroup->addButton(mFlipVerticalRadioButton);

	mOkButton->setText(tr("OK"));
	connect(mOkButton, &QPushButton::clicked, this, &RotateDialog::finish);

	mCancelButton->setText(tr("Cancel"));
	connect(mCancelButton, &QPushButton::clicked, this, &RotateDialog::cancel);

	connect(mButtonGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked), this, &RotateDialog::selectionChanged);

	mRotateRadioButtonLayout->setColumnMinimumWidth(0, 20);
	mRotateRadioButtonLayout->addWidget(m180RadioButton, 0, 0, 1, 2);
	mRotateRadioButtonLayout->addWidget(m90ClockwiseRadioButton, 1, 0, 1, 2);
	mRotateRadioButtonLayout->addWidget(m90CounterClockwiseRadioButton, 2, 0, 1, 2);
	mRotateRadioButtonLayout->addWidget(mArbitraryRotationRadioButton, 3, 0, 1, 2);
	mRotateRadioButtonLayout->addWidget(mArbitraryRotationSpinBox, 4, 1, 1, 1);

	mFlipRadioButtonLayout->addWidget(mFlipHorizontalRadioButton, 0, 0);
	mFlipRadioButtonLayout->addWidget(mFlipVerticalRadioButton, 1, 0);

	mRotateButtonGroupBox->setTitle(tr("Rotate"));
	mRotateButtonGroupBox->setLayout(mRotateRadioButtonLayout);

	mFlipButtonGroupBox->setTitle(tr("Flip"));
	mFlipButtonGroupBox->setLayout(mFlipRadioButtonLayout);

	mButtonRowLayout->addWidget(mOkButton);
	mButtonRowLayout->addWidget(mCancelButton);
	mButtonRowLayout->setAlignment(Qt::AlignRight);

	mMainLayout->addWidget(mRotateButtonGroupBox);
	mMainLayout->addWidget(mFlipButtonGroupBox);
	mMainLayout->addLayout(mButtonRowLayout);

	setLayout(mMainLayout);
}

void RotateDialog::setDefault()
{
	m180RadioButton->setChecked(true);
	mArbitraryRotationSpinBox->setValue(45);

	selectionChanged();
}

void RotateDialog::finish()
{
	if (m180RadioButton->isChecked()) {
		emit rotate(180);
	} else if (m90ClockwiseRadioButton->isChecked()) {
		emit rotate(90);
	} else if (m90CounterClockwiseRadioButton->isChecked()) {
		emit rotate(-90);
	} else if (mArbitraryRotationRadioButton->isChecked()) {
		emit rotate(mArbitraryRotationSpinBox->value());
	} else if (mFlipHorizontalRadioButton->isChecked()) {
		emit flip(FlipDirection::Horizontal);
	} else if (mFlipVerticalRadioButton->isChecked()) {
		emit flip(FlipDirection::Vertical);
	}

	close();
}

void RotateDialog::cancel()
{
	close();
}

void RotateDialog::selectionChanged()
{
	mArbitraryRotationSpinBox->setEnabled(mArbitraryRotationRadioButton->isChecked());
}

} // namespace kImageAnnotator