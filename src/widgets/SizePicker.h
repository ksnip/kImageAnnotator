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

#ifndef SIZEPICKER_H
#define SIZEPICKER_H

#include <QWidget>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QToolButton>
#include <QPainter>

class SizePicker : public QWidget
{
    Q_OBJECT

public:
    SizePicker();
    ~SizePicker();
    void setSize(int size);

signals:
    void sizeSelected(int size) const;

private:
    QVBoxLayout                  *mLayout;
    QButtonGroup                 *mButtonGroup;
    QHash<QAbstractButton*, int>  mButtonToSize;
    QList<int>                    mSizeList;
    QSize                        *mIconSize;
    int                           mSelectedSize;

    void initGui();
    QIcon createIcon(int size) const;
    void setSizeAndNotify(int size);

private slots:
    void buttonClicked(QAbstractButton *button);
};

#endif // SIZEPICKER_H
