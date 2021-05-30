/*
 * Copyright (C) 2017 Damir Porobic <https://github.com/damirporobic>
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

#include "ScaleDialog.h"

namespace kImageAnnotator {

ScaleDialog::ScaleDialog(const QSize &imageSize, QWidget *parent) :
	QDialog(parent, Qt::WindowTitleHint | Qt::WindowCloseButtonHint),
	mKeepAspectRatioCheckBox(new QCheckBox),
	mWidthPixelLabel(new QLabel(this)),
	mHeightPixelLabel(new QLabel(this)),
	mWidthPercentLabel(new QLabel(this)),
	mHeightPercentLabel(new QLabel(this)),
	mWidthPixelSpinBox(new CustomSpinBox(this)),
	mHeightPixelSpinBox(new CustomSpinBox(this)),
	mWidthPercentSpinBox(new CustomSpinBox(this)),
	mOkButton(new QPushButton(this)),
	mCancelButton(new QPushButton(this)),
	mHeightPercentSpinBox(new CustomSpinBox(this)),
	mPixelGridLayout(new QGridLayout),
	mPercentGridLayout(new QGridLayout),
	mPixelGroupBox(new QGroupBox(this)),
	mPercentGroupBox(new QGroupBox(this)),
	mButtonRowLayout(new QHBoxLayout),
	mMainLayout(new QVBoxLayout(this))
{
	setWindowTitle(tr("Scale Image"));

	mSizeHandler.setSize(imageSize);

	initGui();
}

void ScaleDialog::initGui()
{
	mKeepAspectRatioCheckBox->setText(tr("Keep Aspect Ratio"));
	connect(mKeepAspectRatioCheckBox, &QCheckBox::toggled, &mSizeHandler, &ScaleSizeHandler::setAspectRatio);
	mKeepAspectRatioCheckBox->setChecked(true);

	mWidthPixelLabel->setText(tr("Width:"));

	mHeightPixelLabel->setText(tr("Height:"));

	mWidthPercentLabel->setText(tr("Width:"));

	mHeightPercentLabel->setText(tr("Height:"));

	mWidthPixelSpinBox->setSuffix(QLatin1String("px"));
	mWidthPixelSpinBox->setMinimum(1);
	mWidthPixelSpinBox->setMaximum(4000);
	mWidthPixelSpinBox->setValueSilent(mSizeHandler.size().width());
	mWidthPixelSpinBox->setWrapping(false);
	connect(mWidthPixelSpinBox, &CustomSpinBox::valueChanged, &mSizeHandler, &ScaleSizeHandler::setWidthPixel);
	connect(&mSizeHandler, &ScaleSizeHandler::widthPixelChanged, mWidthPixelSpinBox, &CustomSpinBox::setValueSilent);

	mHeightPixelSpinBox->setSuffix(QLatin1String("px"));
	mHeightPixelSpinBox->setMinimum(1);
	mHeightPixelSpinBox->setMaximum(4000);
	mHeightPixelSpinBox->setValueSilent(mSizeHandler.size().height());
	mHeightPixelSpinBox->setWrapping(false);
	connect(mHeightPixelSpinBox, &CustomSpinBox::valueChanged, &mSizeHandler, &ScaleSizeHandler::setHeightPixel);
	connect(&mSizeHandler, &ScaleSizeHandler::heightPixelChanged, mHeightPixelSpinBox, &CustomSpinBox::setValueSilent);

	mWidthPercentSpinBox->setSuffix(QLatin1String("%"));
	mWidthPercentSpinBox->setMinimum(1);
	mWidthPercentSpinBox->setMaximum(400);
	mWidthPercentSpinBox->setValueSilent(100);
	mWidthPercentSpinBox->setWrapping(false);
	connect(mWidthPercentSpinBox, &CustomSpinBox::valueChanged, &mSizeHandler, &ScaleSizeHandler::setWidthPercent);
	connect(&mSizeHandler, &ScaleSizeHandler::widthPercentChanged, mWidthPercentSpinBox, &CustomSpinBox::setValueSilent);

	mHeightPercentSpinBox->setSuffix(QLatin1String("%"));
	mHeightPercentSpinBox->setMinimum(1);
	mHeightPercentSpinBox->setMaximum(400);
	mHeightPercentSpinBox->setValueSilent(100);
	mHeightPercentSpinBox->setWrapping(false);
	connect(mHeightPercentSpinBox, &CustomSpinBox::valueChanged, &mSizeHandler, &ScaleSizeHandler::setHeightPercent);
	connect(&mSizeHandler, &ScaleSizeHandler::heightPercentChanged, mHeightPercentSpinBox, &CustomSpinBox::setValueSilent);

	mOkButton->setText(tr("OK"));
	connect(mOkButton, &QPushButton::clicked, this, &ScaleDialog::scale);

	mCancelButton->setText(tr("Cancel"));
	connect(mCancelButton, &QPushButton::clicked, this, &ScaleDialog::cancel);

	mPixelGridLayout->addWidget(mWidthPixelLabel, 0, 0);
	mPixelGridLayout->addWidget(mWidthPixelSpinBox, 0, 1);
	mPixelGridLayout->addWidget(mHeightPixelLabel, 1, 0);
	mPixelGridLayout->addWidget(mHeightPixelSpinBox, 1, 1);

	mPercentGridLayout->addWidget(mWidthPercentLabel, 0, 0);
	mPercentGridLayout->addWidget(mWidthPercentSpinBox, 0, 1);
	mPercentGridLayout->addWidget(mHeightPercentLabel, 1, 0);
	mPercentGridLayout->addWidget(mHeightPercentSpinBox, 1, 1);

	mPixelGroupBox->setTitle(tr("Pixel"));
	mPixelGroupBox->setLayout(mPixelGridLayout);

	mPercentGroupBox->setTitle(tr("Percent"));
	mPercentGroupBox->setLayout(mPercentGridLayout);

	mButtonRowLayout->addWidget(mOkButton);
	mButtonRowLayout->addWidget(mCancelButton);
	mButtonRowLayout->setAlignment(Qt::AlignRight);

	mMainLayout->addWidget(mKeepAspectRatioCheckBox);
	mMainLayout->addWidget(mPixelGroupBox);
	mMainLayout->addWidget(mPercentGroupBox);
	mMainLayout->addLayout(mButtonRowLayout);

	setLayout(mMainLayout);
}

void ScaleDialog::scale()
{
	QSize newSize(mWidthPixelSpinBox->value(), mHeightPixelSpinBox->value());
	emit finished(newSize);
	close();
}

void ScaleDialog::cancel()
{
	close();
}

} // namespace kImageAnnotator