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

#ifndef KIMAGEANNOTATOR_CUSTOMFONTCOMBOBOX_H
#define KIMAGEANNOTATOR_CUSTOMFONTCOMBOBOX_H

#include <QFontComboBox>
#include <QStylePainter>

#include "src/common/provider/ScaledSizeProvider.h"

namespace kImageAnnotator {

class CustomFontComboBox : public QFontComboBox
{
Q_OBJECT
public:
	explicit CustomFontComboBox(QWidget *parent);
	~CustomFontComboBox() override = default;
	QString selectItemText() const;

protected:
	void resizeEvent(QResizeEvent *event) override;

private slots:
	void elideCurrentText();
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_CUSTOMFONTCOMBOBOX_H
