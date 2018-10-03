/*
 * Copyright (C) 2017 Damir Porobic <https://github.com/damirporobic>
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

#include "ScaleDialog.h"

namespace kImageAnnotator {

ScaleDialog::ScaleDialog(int width, int height, QWidget *parent) : QDialog(parent, Qt::WindowTitleHint | Qt::WindowCloseButtonHint)
{
	setWindowTitle(tr("Scale Image"));

	mSizeHandler.setSize(QSize(width, height));

	initGui();
}

ScaleDialog::~ScaleDialog()
{
	delete mKeepAspectRatioCheckBox;
	delete mWidthPixelLabel;
	delete mHeightPixelLabel;
	delete mWidthPercentLabel;
	delete mHeightPercentLabel;
	delete mWidthPixelSpinBox;
	delete mHeightPixelSpinBox;
	delete mWidthPercentSpinBox;
	delete mHeightPercentSpinBox;
	delete mOkButton;
	delete mCancelButton;
	delete mPixelGridLayout;
	delete mPercentGridLayout;
	delete mPixelGroupBox;
	delete mPercentGroupBox;
	delete mButtonRowLayout;
	delete mMainLayout;
}

void ScaleDialog::initGui()
{
	mKeepAspectRatioCheckBox = new QCheckBox;
	mKeepAspectRatioCheckBox->setText(tr("Keep Aspect Ratio"));
	connect(mKeepAspectRatioCheckBox, &QCheckBox::toggled, &mSizeHandler, &ScaleSizeHandler::setAspectRatio);
	mKeepAspectRatioCheckBox->setChecked(true);

	mWidthPixelLabel = new QLabel;
	mWidthPixelLabel->setText(tr("Width:"));

	mHeightPixelLabel = new QLabel;
	mHeightPixelLabel->setText(tr("Height:"));

	mWidthPercentLabel = new QLabel;
	mWidthPercentLabel->setText(tr("Width:"));

	mHeightPercentLabel = new QLabel;
	mHeightPercentLabel->setText(tr("Height:"));

	mWidthPixelSpinBox = new CustomSpinBox(this);
	mWidthPixelSpinBox->setSuffix(QStringLiteral("px"));
	mWidthPixelSpinBox->setMinimum(1);
	mWidthPixelSpinBox->setMaximum(4000);
	mWidthPixelSpinBox->setValueSilent(mSizeHandler.size().width());
	mWidthPixelSpinBox->setWrapping(false);
	connect(mWidthPixelSpinBox, &CustomSpinBox::valueChanged, &mSizeHandler, &ScaleSizeHandler::setWidthPixel);
	connect(&mSizeHandler, &ScaleSizeHandler::widthPixelChanged, mWidthPixelSpinBox, &CustomSpinBox::setValueSilent);

	mHeightPixelSpinBox = new CustomSpinBox(this);
	mHeightPixelSpinBox->setSuffix(QStringLiteral("px"));
	mHeightPixelSpinBox->setMinimum(1);
	mHeightPixelSpinBox->setMaximum(4000);
	mHeightPixelSpinBox->setValueSilent(mSizeHandler.size().height());
	mHeightPixelSpinBox->setWrapping(false);
	connect(mHeightPixelSpinBox, &CustomSpinBox::valueChanged, &mSizeHandler, &ScaleSizeHandler::setHeightPixcel);
	connect(&mSizeHandler, &ScaleSizeHandler::heightPixelChanged, mHeightPixelSpinBox, &CustomSpinBox::setValueSilent);

	mWidthPercentSpinBox = new CustomSpinBox(this);
	mWidthPercentSpinBox->setSuffix(QStringLiteral("%"));
	mWidthPercentSpinBox->setMinimum(1);
	mWidthPercentSpinBox->setMaximum(400);
	mWidthPercentSpinBox->setValueSilent(100);
	mWidthPercentSpinBox->setWrapping(false);
	connect(mWidthPercentSpinBox, &CustomSpinBox::valueChanged, &mSizeHandler, &ScaleSizeHandler::setWidthPercent);
	connect(&mSizeHandler, &ScaleSizeHandler::widthPercentChanged, mWidthPercentSpinBox, &CustomSpinBox::setValueSilent);

	mHeightPercentSpinBox = new CustomSpinBox(this);
	mHeightPercentSpinBox->setSuffix(QStringLiteral("%"));
	mHeightPercentSpinBox->setMinimum(1);
	mHeightPercentSpinBox->setMaximum(400);
	mHeightPercentSpinBox->setValueSilent(100);
	mHeightPercentSpinBox->setWrapping(false);
	connect(mHeightPercentSpinBox, &CustomSpinBox::valueChanged, &mSizeHandler, &ScaleSizeHandler::setHeightPercent);
	connect(&mSizeHandler, &ScaleSizeHandler::heightPercentChanged, mHeightPercentSpinBox, &CustomSpinBox::setValueSilent);

	mOkButton = new QPushButton;
	mOkButton->setText(tr("OK"));
	connect(mOkButton, &QPushButton::clicked, [this]()
	{
		emit finished(mWidthPixelSpinBox->value(), mHeightPixelSpinBox->value());
		close();
	});

	mCancelButton = new QPushButton;
	mCancelButton->setText(tr("Cancel"));
	connect(mCancelButton, &QPushButton::clicked, [this]()
	{
		close();
	});

	mPixelGridLayout = new QGridLayout;
	mPixelGridLayout->addWidget(mWidthPixelLabel, 0, 0);
	mPixelGridLayout->addWidget(mWidthPixelSpinBox, 0, 1);
	mPixelGridLayout->addWidget(mHeightPixelLabel, 1, 0);
	mPixelGridLayout->addWidget(mHeightPixelSpinBox, 1, 1);

	mPercentGridLayout = new QGridLayout;
	mPercentGridLayout->addWidget(mWidthPercentLabel, 0, 0);
	mPercentGridLayout->addWidget(mWidthPercentSpinBox, 0, 1);
	mPercentGridLayout->addWidget(mHeightPercentLabel, 1, 0);
	mPercentGridLayout->addWidget(mHeightPercentSpinBox, 1, 1);

	mPixelGroupBox = new QGroupBox;
	mPixelGroupBox->setTitle(tr("Pixel"));
	mPixelGroupBox->setLayout(mPixelGridLayout);

	mPercentGroupBox = new QGroupBox;
	mPercentGroupBox->setTitle(tr("Percent"));
	mPercentGroupBox->setLayout(mPercentGridLayout);

	mButtonRowLayout = new QHBoxLayout;
	mButtonRowLayout->addWidget(mOkButton);
	mButtonRowLayout->addWidget(mCancelButton);
	mButtonRowLayout->setAlignment(Qt::AlignRight);

	mMainLayout = new QVBoxLayout;
	mMainLayout->addWidget(mKeepAspectRatioCheckBox);
	mMainLayout->addWidget(mPixelGroupBox);
	mMainLayout->addWidget(mPercentGroupBox);
	mMainLayout->addLayout(mButtonRowLayout);

	setLayout(mMainLayout);
}

} // namespace kImageAnnotator