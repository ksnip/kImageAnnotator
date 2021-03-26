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
	mArbitraryRotationSpinBox(new CustomSpinBox(this)),
	mOkButton(new QPushButton(this)),
	mCancelButton(new QPushButton(this)),
	mRadioButtonLayout(new QGridLayout),
	mButtonRowLayout(new QHBoxLayout),
	mMainLayout(new QVBoxLayout)
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
	delete mArbitraryRotationSpinBox;
	delete mOkButton;
	delete mCancelButton;
	delete mRadioButtonLayout;
	delete mButtonRowLayout;
	delete mMainLayout;
}

void RotateDialog::initGui()
{
	m180RadioButton->setText(tr("180°"));
	m180RadioButton->setChecked(true);
	connect(m180RadioButton, &QRadioButton::toggled, this, &RotateDialog::selectionChanged);

	m90ClockwiseRadioButton->setText(tr("90° Clockwise"));
	connect(m90ClockwiseRadioButton, &QRadioButton::toggled, this, &RotateDialog::selectionChanged);

	m90CounterClockwiseRadioButton->setText(tr("90° Counter Clockwise"));
	connect(m90CounterClockwiseRadioButton, &QRadioButton::toggled, this, &RotateDialog::selectionChanged);

	mArbitraryRotationRadioButton->setText(tr("Arbitrary"));
	connect(mArbitraryRotationRadioButton, &QRadioButton::toggled, this, &RotateDialog::selectionChanged);

	mArbitraryRotationSpinBox->setSuffix(QString::fromUtf8("°"));
	mArbitraryRotationSpinBox->setMinimum(-360);
	mArbitraryRotationSpinBox->setMaximum(360);

	mOkButton->setText(tr("OK"));
	connect(mOkButton, &QPushButton::clicked, this, &RotateDialog::rotate);

	mCancelButton->setText(tr("Cancel"));
	connect(mCancelButton, &QPushButton::clicked, this, &RotateDialog::cancel);

	mRadioButtonLayout->setColumnMinimumWidth(0, 20);
	mRadioButtonLayout->addWidget(m180RadioButton, 0, 0, 1, 2);
	mRadioButtonLayout->addWidget(m90ClockwiseRadioButton, 1, 0, 1, 2);
	mRadioButtonLayout->addWidget(m90CounterClockwiseRadioButton, 2, 0, 1, 2);
	mRadioButtonLayout->addWidget(mArbitraryRotationRadioButton, 3, 0, 1, 2);
	mRadioButtonLayout->addWidget(mArbitraryRotationSpinBox, 4, 1, 1, 1);

	mButtonRowLayout->addWidget(mOkButton);
	mButtonRowLayout->addWidget(mCancelButton);
	mButtonRowLayout->setAlignment(Qt::AlignRight);

	mMainLayout->addLayout(mRadioButtonLayout);
	mMainLayout->addLayout(mButtonRowLayout);

	setLayout(mMainLayout);
}

void RotateDialog::setDefault()
{
	m180RadioButton->setChecked(true);
	mArbitraryRotationSpinBox->setValue(45);

	selectionChanged();
}

void RotateDialog::rotate()
{
	if (m180RadioButton->isChecked()) {
		emit finished(180);
	} else if (m90ClockwiseRadioButton->isChecked()) {
		emit finished(90);
	} else if (m90CounterClockwiseRadioButton->isChecked()) {
		emit finished(-90);
	} else {
		emit finished(mArbitraryRotationSpinBox->value());
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