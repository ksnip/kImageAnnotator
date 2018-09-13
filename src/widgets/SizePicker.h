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

#ifndef KIMAGEANNOTATOR_SIZEPICKER_H
#define KIMAGEANNOTATOR_SIZEPICKER_H

#include <QWidget>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QLabel>
#include <QIcon>

namespace kImageAnnotator {

class SizePicker : public QWidget
{
Q_OBJECT

public:
    SizePicker(const QIcon &icon, const QString &tooltip);
    ~SizePicker();
    void setSize(int size);

signals:
    void sizeSelected(int size) const;

private:
    QHBoxLayout *mLayout;
    QSpinBox *mSpinBox;
    QLabel *mLabel;
    int mSelectedSize;

    void initGui(const QIcon &icon, const QString &tooltip);
    void setSizeAndNotify(int size);

private slots:
    void selectionChanged();
};

} // namespace kImageAnnotator

#endif // KIMAGEANNOTATOR_SIZEPICKER_H
