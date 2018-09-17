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

#include "WidgetVisibilitySwitcher.h"

namespace kImageAnnotator {

WidgetVisibilitySwitcher::WidgetVisibilitySwitcher()
{
    mColorWidget = nullptr;
    mTextColorWidget = nullptr;
    mWidthWidget = nullptr;
    mFillWidget = nullptr;

    mCurrentTool = ToolTypes::Select;
}

void WidgetVisibilitySwitcher::setCurrentTool(ToolTypes tool)
{
    if (mCurrentTool == tool) {
        return;
    }

    mCurrentTool = tool;
    updateVisibility();
}

void WidgetVisibilitySwitcher::setOutlineColorWidget(QWidget *widget)
{
    mColorWidget = widget;
    updateVisibility();
}

void WidgetVisibilitySwitcher::setForegroundColorWidget(QWidget *widget)
{
    mTextColorWidget = widget;
    updateVisibility();
}

void WidgetVisibilitySwitcher::setSizeWidget(QWidget *widget)
{
    mWidthWidget = widget;
    updateVisibility();
}

void WidgetVisibilitySwitcher::setFillWidget(QWidget *widget)
{
    mFillWidget = widget;
    updateVisibility();
}

void WidgetVisibilitySwitcher::updateVisibility()
{
    switch (mCurrentTool) {
        case ToolTypes::Select:
            setColorWidgetVisibility(false);
            setTextColorWidgetVisibility(false);
            setSizeWidgetVisibility(false);
            setFillWidgetVisibility(false);
            break;
        case ToolTypes::Pen:
        case ToolTypes::Marker:
            setColorWidgetVisibility(true);
            setTextColorWidgetVisibility(false);
            setSizeWidgetVisibility(true);
            setFillWidgetVisibility(false);
            break;
        case ToolTypes::Line:
        case ToolTypes::Arrow:
            setColorWidgetVisibility(true);
            setTextColorWidgetVisibility(false);
            setSizeWidgetVisibility(true);
            setFillWidgetVisibility(false);
            break;
        case ToolTypes::Ellipse:
        case ToolTypes::Rect:
            setColorWidgetVisibility(true);
            setTextColorWidgetVisibility(false);
            setSizeWidgetVisibility(true);
            setFillWidgetVisibility(true);
            break;
        case ToolTypes::Number:
            setColorWidgetVisibility(true);
            setTextColorWidgetVisibility(true);
            setSizeWidgetVisibility(true);
            setFillWidgetVisibility(false);
        case ToolTypes::Text:
            setColorWidgetVisibility(true);
            setTextColorWidgetVisibility(true);
            setSizeWidgetVisibility(true);
            setFillWidgetVisibility(true);
            break;
        default:
            qCritical("Unknown tooltype in WidgetVisibilitySwitcher");
    }
}

void WidgetVisibilitySwitcher::setColorWidgetVisibility(bool enabled)
{
    if (mColorWidget) {
        mColorWidget->setEnabled(enabled);
    }
}

void WidgetVisibilitySwitcher::setTextColorWidgetVisibility(bool enabled)
{
    if (mTextColorWidget) {
        mTextColorWidget->setEnabled(enabled);
    }
}

void WidgetVisibilitySwitcher::setSizeWidgetVisibility(bool enabled)
{
    if (mWidthWidget) {
        mWidthWidget->setEnabled(enabled);
    }
}

void WidgetVisibilitySwitcher::setFillWidgetVisibility(bool enabled)
{
    if (mFillWidget) {
        mFillWidget->setEnabled(enabled);
    }
}

} // namespace kImageAnnotator
