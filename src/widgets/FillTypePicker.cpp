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

#include "FillTypePicker.h"

namespace kImageAnnotator {

FillTypePicker::FillTypePicker(const QIcon &icon, const QString &tooltip) :
	mToolButton(new QToolButton(this)),
	mLayout(new QHBoxLayout(this)),
	mLabel(new QLabel(this)),
	mMenu(new QMenu(this))
{
	initGui(icon, tooltip);
}

FillTypePicker::~FillTypePicker()
{
	delete mLayout;
	delete mLabel;
	delete mToolButton;
	delete mMenu;
	qDeleteAll(mActionToFillType.keys());
}

void FillTypePicker::setFillType(FillTypes fillType)
{
	setFillAndNotify(fillType);
}

void FillTypePicker::addNoFillAndNoBorderToList()
{
	auto action = mActionToFillType.key(FillTypes::NoBorderAndNoFill);
	if(action != nullptr) {
		mMenu->addAction(action);
	} else {
		insertItem(FillTypes::NoBorderAndNoFill, QStringLiteral("fillType_noBorderAndNoFill.svg"), tr("No Border and No Fill"));
	}
}

void FillTypePicker::removeNoFillAndNoBorderToList()
{
	auto action = mActionToFillType.key(FillTypes::NoBorderAndNoFill);
	if(action != nullptr) {
		mMenu->removeAction(action);
	}
}

FillTypes FillTypePicker::fillType() const
{
	return mActionToFillType.value(mToolButton->defaultAction());
}

void FillTypePicker::initGui(const QIcon &icon, const QString &tooltip)
{
	mLayout->setContentsMargins(0, 0, 0, 0);

	mLabel->setPixmap(icon.pixmap(ScaledSizeProvider::getScaledSize(QSize(20, 20))));
	mLabel->setToolTip(tooltip);

	insertItem(FillTypes::BorderAndFill, QStringLiteral("fillType_borderAndFill.svg"), tr("Border and Fill"));
	insertItem(FillTypes::BorderAndNoFill, QStringLiteral("fillType_borderAndNoFill.svg"), tr("Border and No Fill"));
	mToolButton->setMenu(mMenu);
	mToolButton->setPopupMode(QToolButton::InstantPopup);
	mToolButton->setFixedSize(ScaledSizeProvider::getScaledSize(Constants::SettingsWidgetSize));
	mToolButton->setIconSize(ScaledSizeProvider::getScaledSize(QSize(25, 25)));
	mToolButton->setToolTip(tooltip);
	mToolButton->setFocusPolicy(Qt::NoFocus);
	mToolButton->setDefaultAction(mActionToFillType.keys().first());

	mLayout->addWidget(mLabel);
	mLayout->addWidget(mToolButton);

	setLayout(mLayout);
	setFixedSize(sizeHint());
}

void FillTypePicker::insertItem(FillTypes fillType, const QString &iconName, const QString &text)
{
	auto action = new QAction(IconLoader::load(iconName), text, this);
	action->setToolTip(text);
	connect(action, &QAction::triggered, this, &FillTypePicker::selectionChanged);
	mMenu->addAction(action);
	mActionToFillType[action] = fillType;
}

void FillTypePicker::setFillAndNotify(FillTypes fill)
{
	auto action = mActionToFillType.key(fill);
	if(action != nullptr && mMenu->actions().contains(action)) {
		mToolButton->setDefaultAction(action);
		emit fillSelected(fill);
	}
}

void FillTypePicker::selectionChanged()
{
	auto action = dynamic_cast<QAction*>(sender());
	if(action != nullptr) {
		auto fillType = mActionToFillType.value(action);
		setFillAndNotify(fillType);
	}
}

} // namespace kImageAnnotator
