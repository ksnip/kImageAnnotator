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

#ifndef KIMAGEANNOTATOR_COLORPICKER_H
#define KIMAGEANNOTATOR_COLORPICKER_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>

#include "kColorPicker/KColorPicker.h"

#include "SettingsPickerWidget.h"
#include "src/common/provider/ScaledSizeProvider.h"

using kColorPicker::KColorPicker;

namespace kImageAnnotator {

class ColorPicker : public SettingsPickerWidget
{
Q_OBJECT
public:
	explicit ColorPicker(QWidget *parent);
	~ColorPicker() override = default;
	void setColor(const QColor &color);
	QColor color() const;
	void setToolTip(const QString &toolTip);
	void setIcon(const QIcon &icon);
	void setShowAlphaChannel(bool showAlphaChannel);

signals:
	void colorSelected(const QColor &color);

protected:
	QWidget* expandingWidget() override;

private:
	QHBoxLayout *mLayout;
	QLabel *mLabel;
	KColorPicker *mkColorPicker;

	void initGui();

private slots:
	void colorChanged(const QColor &color);
};

} // namespace kImageAnnotator

#endif // KIMAGEANNOTATOR_COLORPICKER_H
