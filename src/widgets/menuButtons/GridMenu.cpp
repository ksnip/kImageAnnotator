/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "GridMenu.h"

namespace kImageAnnotator {

GridMenu::GridMenu(QWidget *parent) : 
	QMenu(parent),
	mLayout(new QGridLayout(this)),
	mButtonGroup(new QButtonGroup(this))
{
	setLayout(mLayout);

	mLayout->setSpacing(0);
	mLayout->setContentsMargins(4, 4, 4, 4);
}

GridMenu::~GridMenu()
{
	qDeleteAll(mButtonGroup->buttons());
	delete mButtonGroup;
	delete mLayout;
}

void GridMenu::addItem(const QIcon &icon, const QString &toolTip, const QVariant &data)
{
	auto button = createButton(icon, toolTip, data);
	addButtonToLayout(button);

	if(mLayout->count() == 1) {
		button->setChecked(true);
		emit selectionChanged();
	}
}

void GridMenu::addButtonToLayout(GridMenuButton *button)
{
	auto itemCount = mLayout->count();
	auto row = itemCount / 4;
	auto column = (itemCount % 4) + 1;

	mLayout->addWidget(button, row, column);
}

GridMenuButton *GridMenu::createButton(const QIcon &icon, const QString &toolTip, const QVariant &data) const
{
	auto button = new GridMenuButton(icon, toolTip, data);

	connect(button, &QToolButton::clicked, this, &GridMenu::buttonClicked);
	mButtonGroup->addButton(button);
	return button;
}

void kImageAnnotator::GridMenu::setCurrentData(const QVariant &data)
{
	for(auto button : mButtonGroup->buttons()) {
		auto gridMenuButton = dynamic_cast<GridMenuButton *>(button);
		if(gridMenuButton != nullptr && gridMenuButton->data() == data) {
			gridMenuButton->setChecked(true);
			emit selectionChanged();
			return;
		}
	}
}

QIcon kImageAnnotator::GridMenu::currentIcon() const
{
	auto button = mButtonGroup->checkedButton();
	return button != nullptr ? button->icon() : QIcon();
}

QVariant kImageAnnotator::GridMenu::currentData() const
{
	auto button = dynamic_cast<GridMenuButton*>(mButtonGroup->checkedButton());
	return button != nullptr ? button->data() : QVariant();
}

QString kImageAnnotator::GridMenu::currentToolTip() const
{
	auto button = mButtonGroup->checkedButton();
	return button != nullptr ? button->toolTip() : QString();
}

void GridMenu::clear()
{
	auto buttons = mButtonGroup->buttons();
	for(auto button : buttons) {
		mButtonGroup->removeButton(button);
		mLayout->removeWidget(button);
	}
	qDeleteAll(buttons);
	QMenu::clear();
	emit selectionChanged();
}

QSize GridMenu::sizeHint() const
{
	return mLayout->sizeHint();
}

void kImageAnnotator::GridMenu::buttonClicked()
{
	close();
	emit selectionChanged();
}

} // namespace kImageAnnotator