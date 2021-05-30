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

#include "FontPicker.h"

namespace kImageAnnotator {

FontPicker::FontPicker(QWidget *parent) :
	SettingsPickerWidget(parent),
	mLayout(new QBoxLayout(QBoxLayout::LeftToRight, this)),
	mButtonLayout(new QHBoxLayout),
	mFontComboBox(new CustomFontComboBox(this)),
	mSizeSpinBox(new CustomSpinBox(this)),
	mBoldToggle(new ToggleButton(this)),
	mItalicToggle(new ToggleButton(this)),
	mUnderlineToggle(new ToggleButton(this))
{
	initGui();
}

void FontPicker::setCurrentFont(const QFont &font)
{
	mBoldToggle->setChecked(font.bold());
	mItalicToggle->setChecked(font.italic());
	mUnderlineToggle->setChecked(font.underline());
	mSizeSpinBox->setValue(font.pointSize());
	mFontComboBox->setCurrentFont(font);
}

QFont FontPicker::currentFont() const
{
	auto font = mFontComboBox->currentFont();
	font.setPointSize(mSizeSpinBox->value());
	font.setBold(mBoldToggle->isChecked());
	font.setItalic(mItalicToggle->isChecked());
	font.setUnderline(mUnderlineToggle->isChecked());
	return font;
}

void FontPicker::setExpanding(bool enabled)
{
	mLayout->setDirection(enabled ? QBoxLayout::TopToBottom : QBoxLayout::LeftToRight);
	AbstractExpandingWidget::setExpanding(enabled);
}

QWidget *FontPicker::expandingWidget()
{
	return mFontComboBox;
}

void FontPicker::initGui()
{
	mLayout->setContentsMargins(0, 0, 0, 0);

	mFontComboBox->setFocusPolicy(Qt::NoFocus);
	mFontComboBox->setLayoutDirection(Qt::LeftToRight);
	mFontComboBox->setMinimumWidth(ScaledSizeProvider::scaledWidth(100));

	connect(mFontComboBox, &QFontComboBox::currentFontChanged, this, &FontPicker::selectionChanged);

	mSizeSpinBox->setSuffix(QLatin1String("pt"));
	mSizeSpinBox->setToolTip(tr("Font Size"));
	mSizeSpinBox->setRange(5, 50);
	connect(mSizeSpinBox, &CustomSpinBox::valueChanged, this, &FontPicker::selectionChanged);

	mBoldToggle->setIcon(IconLoader::load(QLatin1String("bold.svg")));
	mBoldToggle->setToolTip(tr("Bold"));
	connect(mBoldToggle, &ToggleButton::toggled, this, &FontPicker::selectionChanged);

	mItalicToggle->setIcon(IconLoader::load(QLatin1String("italic.svg")));
	mItalicToggle->setToolTip(tr("Italic"));
	connect(mItalicToggle, &ToggleButton::toggled, this, &FontPicker::selectionChanged);

	mUnderlineToggle->setIcon(IconLoader::load(QLatin1String("underline.svg")));
	mUnderlineToggle->setToolTip(tr("Underline"));
	connect(mUnderlineToggle, &ToggleButton::toggled, this, &FontPicker::selectionChanged);

	mButtonLayout->addWidget(mBoldToggle);
	mButtonLayout->addWidget(mItalicToggle);
	mButtonLayout->addWidget(mUnderlineToggle);

	mLayout->addWidget(mFontComboBox);
	mLayout->addWidget(mSizeSpinBox);
	mLayout->addLayout(mButtonLayout);

	mLayout->setAlignment(Qt::AlignLeft);

	setLayout(mLayout);
}

void FontPicker::selectionChanged()
{
	setToolTip(mFontComboBox->selectItemText());
	emit fontChanged(currentFont());
}

} // namespace kImageAnnotator