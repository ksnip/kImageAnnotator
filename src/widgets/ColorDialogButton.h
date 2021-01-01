/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KIMAGEANNOTATOR_COLORDIALOGBUTTON_H
#define KIMAGEANNOTATOR_COLORDIALOGBUTTON_H

#include <QPushButton>
#include <QColorDialog>
#include <QPainter>

namespace kImageAnnotator {

class ColorDialogButton : public QPushButton
{
Q_OBJECT
public:
	explicit ColorDialogButton(QWidget *parent);
	~ColorDialogButton() override = default;
	void setColor(const QColor &color);
	QColor color() const;

signals:
	void colorChanged(const QColor &color);

private:
	QColor mColor;

	QPixmap createPixmapFromColor(const QColor &color) const;

private slots:
	void openDialog();
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_COLORDIALOGBUTTON_H
