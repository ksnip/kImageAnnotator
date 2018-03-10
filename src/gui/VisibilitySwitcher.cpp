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

#include "VisibilitySwitcher.h"

VisibilitySwitcher::VisibilitySwitcher()
{
    mColorWidget = nullptr;
    mSizeWidget = nullptr;
    mFillWidget = nullptr;

    mCurrentTool = ToolTypes::Select;
}

void VisibilitySwitcher::setCurrentTool(ToolTypes tool)
{
    if(mCurrentTool == tool) {
        return;
    }

    mCurrentTool = tool;
    updateVisibility();
}

void VisibilitySwitcher::setColorWidget(QWidget* widget)
{
    mColorWidget = widget;
    updateVisibility();
}

void VisibilitySwitcher::setSizeWidget(QWidget* widget)
{
    mSizeWidget = widget;
    updateVisibility();
}

void VisibilitySwitcher::setFillWidget(QWidget* widget)
{
    mFillWidget = widget;
    updateVisibility();
}

void VisibilitySwitcher::updateVisibility()
{
    switch(mCurrentTool) {
        case ToolTypes::Select:
            setColorWidgetVisibility(false);
            setSizeWidgetVisibility(false);
            setFillWidgetVisibility(false);
            break;
        case ToolTypes::Line:
        case ToolTypes::Arrow:
            setColorWidgetVisibility(true);
            setSizeWidgetVisibility(true);
            setFillWidgetVisibility(false);
            break;
        case ToolTypes::Ellipse:
        case ToolTypes::Rect:
            setColorWidgetVisibility(true);
            setSizeWidgetVisibility(true);
            setFillWidgetVisibility(true);
            break;
        case ToolTypes::Number:
            setColorWidgetVisibility(true);
            setSizeWidgetVisibility(false);
            setFillWidgetVisibility(false);
            break;
        default:
            qCritical("Unknown tooltype in VisibilitySwitcher");
    }
}

void VisibilitySwitcher::setColorWidgetVisibility(bool enabled)
{
    if(mColorWidget) {
        mColorWidget->setVisible(enabled);
    }
}

void VisibilitySwitcher::setSizeWidgetVisibility(bool enabled)
{
    if(mSizeWidget) {
        mSizeWidget->setVisible(enabled);
    }
}

void VisibilitySwitcher::setFillWidgetVisibility(bool enabled)
{
    if(mFillWidget) {
        mFillWidget->setVisible(enabled);
    }
}

