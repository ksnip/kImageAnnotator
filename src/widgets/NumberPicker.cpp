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

#include "NumberPicker.h"

namespace kImageAnnotator {

NumberPicker::NumberPicker(QWidget *parent) :
	QWidget(parent),
	mLayout(new QHBoxLayout(this)),
	mLabel(new QLabel()),
	mSpinBox(new CustomSpinBox(this))
{
	initGui();

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
	auto oldState = mSpinBox->blockSignals(true);
	mSpinBox->setValue(number);
	mSpinBox->blockSignals(oldState);
}

void NumberPicker::initGui()
{
	mLayout->setContentsMargins(0, 0, 0, 0);

	mLabel->setFixedSize(ScaledSizeProvider::settingsWidgetIconSize());

	mSpinBox->setFixedSize(ScaledSizeProvider::settingsWidgetSize());
	mSpinBox->setMinimum(1);
	mSpinBox->setMaximum(20);
	mSpinBox->setFocusPolicy(Qt::NoFocus);

	mLayout->addWidget(mLabel);
	mLayout->addWidget(mSpinBox);

	setLayout(mLayout);
	setFixedSize(sizeHint());
}

void NumberPicker::setNumberAndNotify(int number) const
{
	emit numberSelected(number);
}

void NumberPicker::selectionChanged()
{
	setNumberAndNotify(mSpinBox->value());
}

void NumberPicker::setRange(int min, int max)
{
	auto oldState = mSpinBox->blockSignals(true);
	if (min > 0 && max >= min) {
		mSpinBox->setMinimum(min);
		mSpinBox->setMaximum(max);
	}
	mSpinBox->blockSignals(oldState);
}

int NumberPicker::number() const
{
	return mSpinBox->value();
}

void NumberPicker::setToolTip(const QString &toolTip)
{
	mLabel->setToolTip(toolTip);
	mSpinBox->setToolTip(toolTip);
}

void NumberPicker::setIcon(const QIcon &icon)
{
	mLabel->setPixmap(icon.pixmap(ScaledSizeProvider::settingsWidgetIconSize()));
}

} // namespace kImageAnnotator
