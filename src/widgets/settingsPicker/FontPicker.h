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

#ifndef KIMAGEANNOTATOR_FONTPICKER_H
#define KIMAGEANNOTATOR_FONTPICKER_H

#include <QBoxLayout>

#include "SettingsPickerWidget.h"
#include "src/widgets/ToggleButton.h"
#include "src/widgets/CustomSpinBox.h"
#include "src/widgets/CustomFontComboBox.h"
#include "src/common/helper/IconLoader.h"

namespace kImageAnnotator {

class FontPicker : public SettingsPickerWidget
{
Q_OBJECT
public:
	explicit FontPicker(QWidget *parent);
	~FontPicker() override = default;
	void setCurrentFont(const QFont &font);
	QFont currentFont() const;
	void setExpanding(bool enabled) override;

signals:
	void fontChanged(const QFont &font) const;

protected:
	QWidget* expandingWidget() override;

private:
	QBoxLayout *mLayout;
	QHBoxLayout *mButtonLayout;
	CustomFontComboBox *mFontComboBox;
	CustomSpinBox *mSizeSpinBox;
	ToggleButton *mBoldToggle;
	ToggleButton *mItalicToggle;
	ToggleButton *mUnderlineToggle;

	void initGui();

private slots:
	void selectionChanged();
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_FONTPICKER_H
