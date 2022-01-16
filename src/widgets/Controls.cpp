/*
 * Copyright (C) 2021 Antonio Prcela <antonio.prcela@gmail.com>
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

#include "Controls.h"

namespace kImageAnnotator {

Controls::Controls(QWidget *parent) :
	QWidget(parent),
	mLayout(new QHBoxLayout(this))
{
	initGui();
	setFocusPolicy(Qt::ClickFocus);
}

void Controls::initGui()
{
	auto undoAction = createAction(tr("Undo"), IconLoader::load(QLatin1String("undo.svg")));
	undoAction->setShortcut(Qt::Key_Undo);
	createButton(undoAction);
	auto redoAction = createAction(tr("Redo"), IconLoader::load(QLatin1String("redo.svg")));
	redoAction->setShortcut(Qt::Key_Redo);
	createButton(redoAction);

	auto cropAction = createAction(tr("Crop"), IconLoader::load(QLatin1String("crop.svg")));
	createButton(cropAction);
	auto scaleAction = createAction(tr("Scale"), IconLoader::load(QLatin1String("scale.svg")));
	createButton(scaleAction);
	auto rotateAction = createAction(tr("Rotate"), IconLoader::load(QLatin1String("rotate.svg")));
	createButton(rotateAction);
	auto modifyCanvasAction = createAction(tr("Modify canvas"), IconLoader::load(QLatin1String("modifycanvas.svg")));
	createButton(modifyCanvasAction);
	auto cutAction = createAction(tr("Cut"), IconLoader::load(QLatin1String("cut.svg")));
	createButton(cutAction);

	connect(undoAction, &QAction::triggered, this, &Controls::undo);
	connect(redoAction, &QAction::triggered, this, &Controls::redo);
	connect(cropAction, &QAction::triggered, this, &Controls::crop);
	connect(scaleAction, &QAction::triggered, this, &Controls::scale);
    connect(rotateAction, &QAction::triggered, this, &Controls::rotate);
	connect(modifyCanvasAction, &QAction::triggered, this, &Controls::modifyCanvas);
	connect(cutAction, &QAction::triggered, this, &Controls::cut);

	mLayout->setContentsMargins(0, 0, 0, 0);
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	setLayout(mLayout);
}

QAction *Controls::createAction(const QString &tooltip, const QIcon &icon)
{
	auto action = new CustomToolButtonAction(this);
	action->setIcon(icon);
	action->setToolTip(tooltip);
	action->updateDefaultWidget();
	return action;
}

CustomToolButton *Controls::createButton(QAction *defaultAction)
{
	auto button = new CustomToolButton(this);
	button->setAction(defaultAction);
	mLayout->addWidget(button);
	return button;
}

} // namespace kImageAnnotator
