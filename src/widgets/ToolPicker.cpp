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

namespace kImageAnnotator {

ToolPicker::ToolPicker()
{
	initGui();

	setFocusPolicy(Qt::ClickFocus);
}

ToolPicker::~ToolPicker()
{
	delete mActionGroup;
	delete mLayout;
}

void ToolPicker::setTool(ToolTypes newTool)
{
	auto selectedAction = mActionToTool.key(newTool);
	selectedAction->setChecked(true);
	setToolAndNotify(newTool);
}

ToolTypes ToolPicker::tool()
{
	return mSelectedToolType;
}

void ToolPicker::initGui()
{
	mLayout = new QGridLayout(this);
	mLayout->setContentsMargins(0, 0, 0, 0);
	mActionGroup = new QActionGroup(this);
	connect(mActionGroup, &QActionGroup::triggered, this, &ToolPicker::actionTriggered);

	auto action = createAction(tr("Select"), QIcon(QStringLiteral(":/icons/select")), Qt::Key_S, ToolTypes::Select);
	auto button = createButton(action);
	mLayout->addWidget(button, 0, 0);

	action = createAction(tr("Pen"), QIcon(QStringLiteral(":/icons/pen")), Qt::Key_P, ToolTypes::Pen);
	button = createButton(action);
	mLayout->addWidget(button, 0, 1);

	action = createAction(tr("Number"), QIcon(QStringLiteral(":/icons/number")), Qt::Key_N, ToolTypes::Number);
	button = createButton(action);
	mLayout->addWidget(button, 2, 0);

	auto menu = new QMenu();
	action = createAction(tr("Marker Rectangle"), QIcon(QStringLiteral(":/icons/markerRect")), Qt::Key_J, ToolTypes::MarkerRect);
	menu->addAction(action);
	action = createAction(tr("Marker Pen"), QIcon(QStringLiteral(":/icons/markerPen")), Qt::Key_M, ToolTypes::MarkerPen);
	menu->addAction(action);
	button = createButton(menu);
	mLayout->addWidget(button, 2, 1);

	action = createAction(tr("Text"), QIcon(QStringLiteral(":/icons/text")), Qt::Key_T, ToolTypes::Text);
	button = createButton(action);
	mLayout->addWidget(button, 3, 0);

	menu = new QMenu();
	action = createAction(tr("Arrow"), QIcon(QStringLiteral(":/icons/arrow")), Qt::Key_A, ToolTypes::Arrow);
	menu->addAction(action);
	action = createAction(tr("Line"), QIcon(QStringLiteral(":/icons/line")), Qt::Key_L, ToolTypes::Line);
	menu->addAction(action);
	button = createButton(menu);
	mLayout->addWidget(button, 3, 1);

	action = createAction(tr("Blur"), QIcon(QStringLiteral(":/icons/blur")), Qt::Key_B, ToolTypes::Blur);
	button = createButton(action);
	mLayout->addWidget(button, 4, 0);

	menu = new QMenu();
	action = createAction(tr("Rectangle"), QIcon(QStringLiteral(":/icons/rect")), Qt::Key_R, ToolTypes::Rect);
	menu->addAction(action);
	action = createAction(tr("Ellipse"), QIcon(QStringLiteral(":/icons/ellipse")), Qt::Key_E, ToolTypes::Ellipse);
	menu->addAction(action);
	button = createButton(menu);
	mLayout->addWidget(button, 4, 1);

	setLayout(mLayout);
	setFixedSize(sizeHint());
}

QAction *ToolPicker::createAction(const QString &tooltip, const QIcon &icon, Qt::Key shortcut, ToolTypes toolType)
{
	auto action = new CustomToolButtonAction(this);
	action->setCheckable(true);
	action->setIcon(icon);
	action->setShortcut(shortcut);
	action->setToolTip(tooltip + QStringLiteral(" (") + shortcut + QStringLiteral(")"));
	action->updateDefaultWidget();
	mActionToTool[action] = toolType;
	mActionGroup->addAction(action);
	return action;
}

CustomToolButton *ToolPicker::createButton(QAction *defaultAction)
{
	auto button = new CustomToolButton(this);
	button->setDefaultAction(defaultAction);
	return button;
}

CustomToolButton *ToolPicker::createButton(QMenu *menu)
{
	auto button = new CustomToolButton(this);
	button->setMenu(menu);
	button->setActiveAction(menu->actions().first());
	return button;
}

void ToolPicker::actionTriggered(QAction *action)
{
	auto newTool = mActionToTool.value(action);
	setToolAndNotify(newTool);
}

void ToolPicker::setToolAndNotify(ToolTypes newTool)
{
	mSelectedToolType = newTool;
	emit toolSelected(mSelectedToolType);
}

} // namespace kImageAnnotator
