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
    mOutlineColorWidget = nullptr;
    mFillColorWidget = nullptr;
    mForegroundColorWidget = nullptr;
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

void VisibilitySwitcher::setOutlineColorWidget(QWidget* widget)
{
    mOutlineColorWidget = widget;
    updateVisibility();
}

void VisibilitySwitcher::setFillColorWidget(QWidget* widget)
{
    mFillColorWidget = widget;
    updateVisibility();
}

void VisibilitySwitcher::setForegroundColorWidget(QWidget* widget)
{
    mForegroundColorWidget = widget;
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
            setOutlineColorWidgetVisibility(false);
            setFillColorWidgetVisibility(false);
            setForegroundColorWidgetVisibility(false);
            setSizeWidgetVisibility(false);
            setFillWidgetVisibility(false);
            break;
        case ToolTypes::Line:
        case ToolTypes::Arrow:
            setOutlineColorWidgetVisibility(true);
            setFillColorWidgetVisibility(false);
            setForegroundColorWidgetVisibility(false);
            setSizeWidgetVisibility(true);
            setFillWidgetVisibility(false);
            break;
        case ToolTypes::Ellipse:
        case ToolTypes::Rect:
            setOutlineColorWidgetVisibility(true);
            setFillColorWidgetVisibility(true);
            setForegroundColorWidgetVisibility(false);
            setSizeWidgetVisibility(true);
            setFillWidgetVisibility(true);
            break;
        case ToolTypes::Number:
            setOutlineColorWidgetVisibility(true);
            setFillColorWidgetVisibility(true);
            setForegroundColorWidgetVisibility(true);
            setSizeWidgetVisibility(true);
            setFillWidgetVisibility(false);
            break;
        default:
            qCritical("Unknown tooltype in VisibilitySwitcher");
    }
}

void VisibilitySwitcher::setOutlineColorWidgetVisibility(bool enabled)
{
    if(mOutlineColorWidget) {
        mOutlineColorWidget->setEnabled(enabled);
    }
}

void VisibilitySwitcher::setFillColorWidgetVisibility(bool enabled)
{
    if(mFillColorWidget) {
        mFillColorWidget->setEnabled(enabled);
    }
}

void VisibilitySwitcher::setForegroundColorWidgetVisibility(bool enabled)
{
    if(mForegroundColorWidget) {
        mForegroundColorWidget->setEnabled(enabled);
    }
}


void VisibilitySwitcher::setSizeWidgetVisibility(bool enabled)
{
    if(mSizeWidget) {
        mSizeWidget->setEnabled(enabled);
    }
}

void VisibilitySwitcher::setFillWidgetVisibility(bool enabled)
{
    if(mFillWidget) {
        mFillWidget->setEnabled(enabled);
    }
}

