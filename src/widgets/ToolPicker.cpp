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

#include "ToolPicker.h"

ToolPicker::ToolPicker()
{
    initGui();

    connect(this, &QToolBar::actionTriggered, this, &ToolPicker::actionTriggered);
}

ToolPicker::~ToolPicker()
{
    delete mActionGroup;
}

void ToolPicker::selectTool(ToolTypes newTool)
{
    auto selectedAction = mActionToTool.key(newTool);
    selectedAction->setChecked(true);
    setToolAndNotify(newTool);
}

void ToolPicker::initGui()
{
    setOrientation(Qt::Vertical);

    mSelectAction = addAction(QStringLiteral("Select"));
    mSelectAction->setCheckable(true);
    mSelectAction->setIcon(QPixmap(QStringLiteral(":/icons/select")));
    mActionToTool[mSelectAction] = ToolTypes::Select;

    addSeparator();

    mLineAction = addAction(QStringLiteral("Line"));
    mLineAction->setCheckable(true);
    mLineAction->setIcon(QPixmap(QStringLiteral(":/icons/line")));
    mActionToTool[mLineAction] = ToolTypes::Line;

    mRectAction = addAction(QStringLiteral("Rect"));
    mRectAction->setCheckable(true);
    mRectAction->setIcon(QPixmap(QStringLiteral(":/icons/rect")));
    mActionToTool[mRectAction] = ToolTypes::Rect;

    mEllipseAction = addAction(QStringLiteral("Ellipse"));
    mEllipseAction->setCheckable(true);
    mEllipseAction->setIcon(QPixmap(QStringLiteral(":/icons/ellipse")));
    mActionToTool[mEllipseAction] = ToolTypes::Ellipse;

    mArrowAction = addAction(QStringLiteral("Arrow"));
    mArrowAction->setCheckable(true);
    mArrowAction->setIcon(QPixmap(QStringLiteral(":/icons/arrow")));
    mActionToTool[mArrowAction] = ToolTypes::Arrow;

    mActionGroup = new QActionGroup(this);
    mActionGroup->addAction(mSelectAction);
    mActionGroup->addAction(mLineAction);
    mActionGroup->addAction(mRectAction);
    mActionGroup->addAction(mEllipseAction);
    mActionGroup->addAction(mArrowAction);
}

void ToolPicker::actionTriggered(QAction* action)
{
    setToolAndNotify(mActionToTool.value(action));
}

void ToolPicker::setToolAndNotify(ToolTypes newTool)
{
    mSelectedToolType = newTool;
    emit toolSelected(mSelectedToolType);
}

