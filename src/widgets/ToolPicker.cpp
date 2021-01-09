/*
 * Copyright (C) 2018 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
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

ToolPicker::ToolPicker(QWidget *parent) : QWidget(parent)
{
	initGui();

	setFocusPolicy(Qt::ClickFocus);
}

ToolPicker::~ToolPicker()
{
	delete mActionGroup;
	delete mLayout;
}

void ToolPicker::setTool(Tools newTool)
{
	auto action = mActionToTool.key(newTool);
	auto button = mActionToButton[action];
	button->setDefaultAction(action);
	action->setChecked(true);
	setToolAndNotify(newTool);
}

Tools ToolPicker::tool()
{
	return mSelectedToolType;
}

void ToolPicker::initGui()
{
	mLayout = new QGridLayout(this);
	mLayout->setContentsMargins(0, 0, 0, 0);
	mActionGroup = new QActionGroup(this);
	connect(mActionGroup, &QActionGroup::triggered, this, &ToolPicker::actionTriggered);

	auto action = createAction(tr("Select"), IconLoader::load(QStringLiteral("select.svg")), Qt::Key_S, Tools::Select);
	auto button = createButton(action);
	mLayout->addWidget(button, 0, 0);

	action = createAction(tr("Duplicate"), IconLoader::load(QStringLiteral("duplicate.svg")), Qt::Key_U, Tools::Duplicate);
	button = createButton(action);
	mLayout->addWidget(button, 0, 1);

	auto menu = new QMenu();
	action = createAction(tr("Arrow"), IconLoader::load(QStringLiteral("arrow.svg")), Qt::Key_A, Tools::Arrow);
	menu->addAction(action);
	action = createAction(tr("Double Arrow"), IconLoader::load(QStringLiteral("doubleArrow.svg")), Qt::Key_D, Tools::DoubleArrow);
	menu->addAction(action);
	action = createAction(tr("Line"), IconLoader::load(QStringLiteral("line.svg")), Qt::Key_L, Tools::Line);
	menu->addAction(action);
	button = createButton(menu);
	mLayout->addWidget(button, 1, 0);

	action = createAction(tr("Pen"), IconLoader::load(QStringLiteral("pen.svg")), Qt::Key_P, Tools::Pen);
	button = createButton(action);
	mLayout->addWidget(button, 1, 1);

	menu = new QMenu();
	action = createAction(tr("Marker Rectangle"), IconLoader::load(QStringLiteral("markerRect.svg")), Qt::Key_J, Tools::MarkerRect);
	menu->addAction(action);
	action = createAction(tr("Marker Ellipse"), IconLoader::load(QStringLiteral("markerEllipse.svg")), Qt::Key_K, Tools::MarkerEllipse);
	menu->addAction(action);
	action = createAction(tr("Marker Pen"), IconLoader::load(QStringLiteral("markerPen.svg")), Qt::Key_M, Tools::MarkerPen);
	menu->addAction(action);
	button = createButton(menu);
	mLayout->addWidget(button, 2, 0);

	menu = new QMenu();
	action = createAction(tr("Text"), IconLoader::load(QStringLiteral("text.svg")), Qt::Key_T, Tools::Text);
	menu->addAction(action);
	action = createAction(tr("Text Pointer"), IconLoader::load(QStringLiteral("textPointer.svg")), Qt::Key_C, Tools::TextPointer);
	menu->addAction(action);
	action = createAction(tr("Text Arrow"), IconLoader::load(QStringLiteral("textArrow.svg")), Qt::Key_H, Tools::TextArrow);
	menu->addAction(action);
	button = createButton(menu);
	mLayout->addWidget(button, 2, 1);

	menu = new QMenu();
	action = createAction(tr("Number"), IconLoader::load(QStringLiteral("number.svg")), Qt::Key_N, Tools::Number);
	menu->addAction(action);
	action = createAction(tr("Number Pointer"), IconLoader::load(QStringLiteral("numberPointer.svg")), Qt::Key_O, Tools::NumberPointer);
	menu->addAction(action);
	action = createAction(tr("Number Arrow"), IconLoader::load(QStringLiteral("numberArrow.svg")), Qt::Key_W, Tools::NumberArrow);
	menu->addAction(action);
	button = createButton(menu);
	mLayout->addWidget(button, 3, 0);

	menu = new QMenu();
	action = createAction(tr("Blur"), IconLoader::load(QStringLiteral("blur.svg")), Qt::Key_B, Tools::Blur);
	menu->addAction(action);
	action = createAction(tr("Pixelate"), IconLoader::load(QStringLiteral("pixelate.svg")), Qt::Key_X, Tools::Pixelate);
	menu->addAction(action);
	button = createButton(menu);
	mLayout->addWidget(button, 3, 1);

	menu = new QMenu();
	action = createAction(tr("Rectangle"), IconLoader::load(QStringLiteral("rect.svg")), Qt::Key_R, Tools::Rect);
	menu->addAction(action);
	action = createAction(tr("Ellipse"), IconLoader::load(QStringLiteral("ellipse.svg")), Qt::Key_E, Tools::Ellipse);
	menu->addAction(action);
	button = createButton(menu);
	mLayout->addWidget(button, 4, 0);

	action = createAction(tr("Sticker"), IconLoader::load(QStringLiteral("sticker.svg")), Qt::Key_I, Tools::Sticker);
	button = createButton(action);
	mLayout->addWidget(button, 4, 1);

	setLayout(mLayout);
	setFixedSize(sizeHint());
}

QAction *ToolPicker::createAction(const QString &tooltip, const QIcon &icon, Qt::Key shortcut, Tools toolType)
{
	auto action = new CustomToolButtonAction(this);
	action->setCheckable(true);
	action->setIcon(icon);
	action->setShortcut(shortcut);
	action->setToolTip(tooltip + QLatin1String(" (") + shortcut + QLatin1String(")"));
	action->updateDefaultWidget();
	mActionToTool[action] = toolType;
	mActionGroup->addAction(action);
	return action;
}

CustomToolButton *ToolPicker::createButton(QAction *defaultAction)
{
	auto button = new CustomToolButton(this);
	button->setAction(defaultAction);
	mActionToButton[defaultAction] = button;
	return button;
}

CustomToolButton *ToolPicker::createButton(QMenu *menu)
{
	auto button = new CustomToolButton(this);
	button->setMenu(menu);
	for(auto action : menu->actions()) {
		mActionToButton[action] = button;
	}
	return button;
}

void ToolPicker::actionTriggered(QAction *action)
{
	auto newTool = mActionToTool.value(action);
	setToolAndNotify(newTool);
}

void ToolPicker::setToolAndNotify(Tools newTool)
{
	mSelectedToolType = newTool;
	emit toolSelected(mSelectedToolType);
}

} // namespace kImageAnnotator
