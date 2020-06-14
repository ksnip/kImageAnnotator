/*
 * Copyright (C) 2019 Damir Porobic <damir.porobic@gmx.com>
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

#include "CustomToolButtonAction.h"

namespace kImageAnnotator {

CustomToolButtonAction::CustomToolButtonAction(QObject *parent) : QWidgetAction(parent)
{
	initDefaultWidget();
}

CustomToolButtonAction::~CustomToolButtonAction()
{
	delete mText;
	delete mImage;
	delete mLayout;
	delete mMenuItem;
}

void CustomToolButtonAction::updateDefaultWidget()
{
	mText->setText(toolTip());
	mImage->setPixmap(icon().pixmap(Constants::MenuItemIconSize));
	mMenuItem->setToolTip(toolTip());

	setDefaultWidget(mMenuItem);
}

void CustomToolButtonAction::initDefaultWidget()
{
	mMenuItem = new QWidget;
	mText = new QLabel(mMenuItem);
	mImage = new QLabel(mMenuItem);
	mLayout = new QHBoxLayout(mMenuItem);
	mLayout->setAlignment(Qt::AlignLeft);
	mLayout->addWidget(mImage);
	mLayout->addWidget(mText);
	mMenuItem->setLayout(mLayout);
	mMenuItem->setStyleSheet(QStringLiteral(":hover{background-color:palette(highlight);}"));
}

}
