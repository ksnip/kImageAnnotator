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

#ifndef ICONCREATER_H
#define ICONCREATER_H

#include <QIcon>
#include <QColor>
#include <QPainter>

class IconCreater
{
public:
    IconCreater(QSize iconSize = QSize(25, 20));
    ~IconCreater() = default;
    void setIconSize(const QSize& iconSize);
    QSize iconSize() const;
    QIcon createColorIcon(const QColor& color) const;
    QIcon createSizeIcon(int size) const;
    QIcon createFillIcon(bool withFill) const;

private:
    QSize mIconSize;
};

#endif // ICONCREATER_H
