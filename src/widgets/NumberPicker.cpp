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

#include "NumberPicker.h"

namespace kImageAnnotator {

NumberPicker::NumberPicker(const QIcon &icon, const QString &tooltip)
{
	initGui(icon, tooltip);

	connect(mSpinBox, &CustomSpinBox::valueChanged, this, &NumberPicker::selectionChanged);
}

NumberPicker::~NumberPicker()
{
	delete mLayout;
	delete mSpinBox;
	delete mLabel;
}

void NumberPicker::setNumber(int number)
{
	mSpinBox->setValue(number);
}

void NumberPicker::initGui(const QIcon &icon, const QString &tooltip)
{
	mLayout = new QHBoxLayout(this);
	mLayout->setContentsMargins(0, 0, 0, 0);

	mLabel = new QLabel();
	mLabel->setPixmap(icon.pixmap(QSize(20, 20)));
	mLabel->setToolTip(tooltip);

	mSpinBox = new CustomSpinBox(this);
	mSpinBox->setFixedSize(Constants::SettingsWidgetSize);
	mSpinBox->setMinimum(1);
	mSpinBox->setMaximum(20);
	mSpinBox->setFocusPolicy(Qt::NoFocus);
	mSpinBox->setToolTip(tooltip);

	mLayout->addWidget(mLabel);
	mLayout->addWidget(mSpinBox);

	setLayout(mLayout);
	setFixedSize(sizeHint());
}

void NumberPicker::setNumberAndNotify(int number)
{
	emit numberSelected(number);
}

void NumberPicker::selectionChanged()
{
	setNumberAndNotify(mSpinBox->value());
}

void NumberPicker::setRange(int min, int max)
{
	if (min > 0 && max >= min) {
		mSpinBox->setMinimum(min);
		mSpinBox->setMaximum(max);
	}
}

int NumberPicker::number() const
{
	return mSpinBox->value();
}

} // namespace kImageAnnotator
