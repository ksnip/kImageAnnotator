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
    setDefaults();

    connect(this, &QToolBar::actionTriggered, this, &ToolPicker::actionTriggered);
}

ToolPicker::~ToolPicker()
{
    delete mActionGroup;
}

void ToolPicker::initGui()
{
    setOrientation(Qt::Vertical);

    mSelectAction = addAction("S");
    mSelectAction->setCheckable(true);

    addSeparator();

    mLineItemAction = addAction("L");
    mLineItemAction->setCheckable(true);

    mRectItemAction = addAction("R");
    mRectItemAction->setCheckable(true);

    mEllipseItemAction = addAction("L");
    mEllipseItemAction->setCheckable(true);

    mArrowItemAction = addAction("A");
    mArrowItemAction->setCheckable(true);

    mActionGroup = new QActionGroup(this);
    mActionGroup->addAction(mSelectAction);
    mActionGroup->addAction(mLineItemAction);
    mActionGroup->addAction(mRectItemAction);
    mActionGroup->addAction(mEllipseItemAction);
    mActionGroup->addAction(mArrowItemAction);

    // Only used for easy matching
    mListOfItemActions.append(mLineItemAction);
    mListOfItemActions.append(mRectItemAction);
    mListOfItemActions.append(mEllipseItemAction);
    mListOfItemActions.append(mArrowItemAction);
}

void ToolPicker::setDefaults()
{
    mLineItemAction->setChecked(true);
    mSelectedItemType = AnnotationItemTypes::Line;
    mSelectedToolType = AnnotationToolTypes::Annotation;
}

void ToolPicker::notifyIfToolChanged(QAction* action)
{
    if(action == mSelectAction && mSelectedToolType != AnnotationToolTypes::Select) {
        mSelectedToolType = AnnotationToolTypes::Select;
        emit toolChanged(mSelectedToolType);
    } else if(mListOfItemActions.contains(action) && mSelectedToolType != AnnotationToolTypes::Annotation) {
        mSelectedToolType = AnnotationToolTypes::Annotation;
        emit toolChanged(mSelectedToolType);
    }
}

void ToolPicker::notifyIfItemChanged(QAction* action)
{
    if(mListOfItemActions.contains(action)) {
        if(action == mLineItemAction && mSelectedItemType != AnnotationItemTypes::Line) {
            mSelectedItemType = AnnotationItemTypes::Line;
            emit itemChanged(mSelectedItemType);
        } else if(action == mRectItemAction && mSelectedItemType != AnnotationItemTypes::Rect) {
            mSelectedItemType = AnnotationItemTypes::Rect;
            emit itemChanged(mSelectedItemType);
        } else if(action == mEllipseItemAction && mSelectedItemType != AnnotationItemTypes::Ellipse) {
            mSelectedItemType = AnnotationItemTypes::Ellipse;
            emit itemChanged(mSelectedItemType);
        } else if(action == mArrowItemAction && mSelectedItemType != AnnotationItemTypes::Arrow) {
            mSelectedItemType = AnnotationItemTypes::Arrow;
            emit itemChanged(mSelectedItemType);
        }
    }
}


void ToolPicker::actionTriggered(QAction* action)
{
    notifyIfToolChanged(action);
    notifyIfItemChanged(action);
}
