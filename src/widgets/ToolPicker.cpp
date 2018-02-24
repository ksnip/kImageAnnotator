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
    switch(newTool) {
        case ToolTypes::Select:
            mSelectAction->setChecked(true);
        break;
        case ToolTypes::Line:
            mLineAction->setChecked(true);
        break;
        case ToolTypes::Rect:
            mRectAction->setChecked(true);
        break;
        case ToolTypes::Ellipse:
            mEllipseAction->setChecked(true);
        break;
        case ToolTypes::Arrow:
            mArrowAction->setChecked(true);
        break;
    }
    setToolAndNotify(newTool);
}

void ToolPicker::initGui()
{
    setOrientation(Qt::Vertical);

    mSelectAction = addAction(QStringLiteral("Select"));
    mSelectAction->setCheckable(true);
    mSelectAction->setIcon(QPixmap(QStringLiteral(":/icons/select")));

    addSeparator();

    mLineAction = addAction(QStringLiteral("Line"));
    mLineAction->setCheckable(true);
    mLineAction->setIcon(QPixmap(QStringLiteral(":/icons/line")));

    mRectAction = addAction(QStringLiteral("Rect"));
    mRectAction->setCheckable(true);
    mRectAction->setIcon(QPixmap(QStringLiteral(":/icons/rect")));

    mEllipseAction = addAction(QStringLiteral("Ellipse"));
    mEllipseAction->setCheckable(true);
    mEllipseAction->setIcon(QPixmap(QStringLiteral(":/icons/ellipse")));

    mArrowAction = addAction(QStringLiteral("Arrow"));
    mArrowAction->setCheckable(true);
    mArrowAction->setIcon(QPixmap(QStringLiteral(":/icons/arrow")));

    mActionGroup = new QActionGroup(this);
    mActionGroup->addAction(mSelectAction);
    mActionGroup->addAction(mLineAction);
    mActionGroup->addAction(mRectAction);
    mActionGroup->addAction(mEllipseAction);
    mActionGroup->addAction(mArrowAction);

    // Only used for easy matching
    mListOfItemActions.append(mLineAction);
    mListOfItemActions.append(mRectAction);
    mListOfItemActions.append(mEllipseAction);
    mListOfItemActions.append(mArrowAction);
}

void ToolPicker::actionTriggered(QAction* action)
{
    ToolTypes selectedTool;
    if(action == mSelectAction) {
        selectedTool = ToolTypes::Select;
    } else if(action == mLineAction) {
        selectedTool = ToolTypes::Line;
    } else if(action == mSelectAction) {
        selectedTool = ToolTypes::Rect;
    } else if(action == mSelectAction) {
        selectedTool = ToolTypes::Ellipse;
    } else if(action == mSelectAction) {
        selectedTool = ToolTypes::Arrow;
    } else {
        qCritical("Unknown action in tool picker.");
    }

    setToolAndNotify(selectedTool);
}

void ToolPicker::setToolAndNotify(ToolTypes newTool)
{
    mSelectedToolType = newTool;
    emit toolSelected(mSelectedToolType);
}

