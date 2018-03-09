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

#ifndef FILLPICKER_H
#define FILLPICKER_H

#include <QFrame>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QToolButton>
#include <QPainter>

#include "../common/FillTypes.h"

class FillPicker : public QFrame
{
Q_OBJECT

public:
    FillPicker();
    ~FillPicker();
    void setFill(FillTypes fill);

signals:
    void fillSelected(FillTypes fill) const;

private:
    QVBoxLayout                  *mLayout;
    QButtonGroup                 *mButtonGroup;
    QHash<QAbstractButton*, FillTypes>  mButtonToFill;
    QSize                        *mIconSize;
    QList<FillTypes>              mFillList;
    FillTypes                     mSelectedFill;

    void initGui();
    QIcon createIcon(FillTypes fill) const;
    void setFillAndNotify(FillTypes fill);
    QString getFillTypeString(FillTypes fill) const;

private slots:
    void buttonClicked(QAbstractButton *button);
};

#endif // FILLPICKER_H
