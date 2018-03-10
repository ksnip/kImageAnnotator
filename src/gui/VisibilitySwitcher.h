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

#ifndef VISIBILITYSWITCHER_H
#define VISIBILITYSWITCHER_H

#include <QWidget>

#include "../common/enum/ToolTypes.h"

class VisibilitySwitcher
{
public:
    explicit VisibilitySwitcher();
    ~VisibilitySwitcher() = default;
    void setCurrentTool(ToolTypes tool);
    void setColorWidget(QWidget* widget);
    void setSizeWidget(QWidget* widget);
    void setFillWidget(QWidget* widget);

private:
    ToolTypes mCurrentTool;
    QWidget*  mColorWidget;
    QWidget*  mSizeWidget;
    QWidget*  mFillWidget;

    void updateVisibility();
    void setColorWidgetVisibility(bool enabled);
    void setSizeWidgetVisibility(bool enabled);
    void setFillWidgetVisibility(bool enabled);
};

#endif // VISIBILITYSWITCHER_H
