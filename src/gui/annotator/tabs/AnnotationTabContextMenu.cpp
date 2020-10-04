/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
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

#include "AnnotationTabContextMenu.h"

namespace kImageAnnotator {

AnnotationTabContextMenu::AnnotationTabContextMenu(QWidget *parent)
	: QMenu(parent),
	  mCloseTab(new QAction(this)),
	  mClosedOtherTabs(new QAction(this)),
	  mCloseAllTabs(new QAction(this)),
	  mCloseAllTabsToLeft(new QAction(this)),
	  mCloseAllTabsToRight(new QAction(this)),
	  mTabIndex(-1)
{
	mCloseTab->setText(tr("Close"));
	mClosedOtherTabs->setText(tr("Close Other"));
	mCloseAllTabs->setText(tr("Close All"));
	mCloseAllTabsToLeft->setText(tr("Close All to the Left"));
	mCloseAllTabsToRight->setText(tr("Close All to the Right"));

	mCloseTab->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_W));
	mCloseTab->setShortcutContext(Qt::ApplicationShortcut);
	parent->addAction(mCloseTab);

	connect(mCloseTab, &QAction::triggered, this, &AnnotationTabContextMenu::closeTabTriggered);
	connect(mClosedOtherTabs, &QAction::triggered, this, &AnnotationTabContextMenu::closeOtherTabsTriggered);
	connect(mCloseAllTabs, &QAction::triggered, this, &AnnotationTabContextMenu::closeAllTabsTriggered);
	connect(mCloseAllTabsToLeft, &QAction::triggered, this, &AnnotationTabContextMenu::closeAllTabsToLeftTriggered);
	connect(mCloseAllTabsToRight, &QAction::triggered, this, &AnnotationTabContextMenu::closeAllTabsToRightTriggered);

	addAction(mCloseTab);
	addAction(mClosedOtherTabs);
	addAction(mCloseAllTabs);
	addAction(mCloseAllTabsToLeft);
	addAction(mCloseAllTabsToRight);
}

AnnotationTabContextMenu::~AnnotationTabContextMenu()
{
	delete mCloseTab;
	delete mClosedOtherTabs;
	delete mCloseAllTabs;
	qDeleteAll(mCustomActionMap.keys());
}

void AnnotationTabContextMenu::show(int tabIndex, const QPoint &pos)
{
	mTabIndex = tabIndex;
	exec(pos);
	mTabIndex = -1;
}

void AnnotationTabContextMenu::closeTabTriggered() const
{
	emit closeTab(mTabIndex);
}

void AnnotationTabContextMenu::closeOtherTabsTriggered() const
{
	emit closeOtherTabs(mTabIndex);
}

void AnnotationTabContextMenu::closeAllTabsTriggered() const
{
	emit closeAllTabs();
}

void AnnotationTabContextMenu::closeAllTabsToLeftTriggered() const
{
	emit closeAllTabsToLeft(mTabIndex);
}

void AnnotationTabContextMenu::closeAllTabsToRightTriggered() const
{
	emit closeAllTabsToRight(mTabIndex);
}

void AnnotationTabContextMenu::addCustomActions(const QList<QAction *> &customActions)
{
    addSeparator();
    for(auto innerAction : customActions) {
        auto outerAction = new QAction(this);
        outerAction->setText(innerAction->text());
        outerAction->setIcon(innerAction->icon());
        outerAction->setToolTip(innerAction->toolTip());
        outerAction->setEnabled(innerAction->isEnabled());
        mCustomActionMap[outerAction] = innerAction;
        connect(innerAction, &QAction::changed, this, &AnnotationTabContextMenu::customActionChanged);
        connect(outerAction, &QAction::triggered, this, &AnnotationTabContextMenu::customActionTriggered);
        addAction(outerAction);
    }
}

void AnnotationTabContextMenu::customActionTriggered()
{
    auto outerAction = dynamic_cast<QAction *>(sender());
    auto innerAction = mCustomActionMap.value(outerAction);
    innerAction->setData(mTabIndex);
    innerAction->trigger();
}

void AnnotationTabContextMenu::customActionChanged()
{
    auto innerAction = dynamic_cast<QAction *>(sender());
    auto outerAction = mCustomActionMap.key(innerAction);
    outerAction->setEnabled(innerAction->isEnabled());
}

} // namespace kImageAnnotator