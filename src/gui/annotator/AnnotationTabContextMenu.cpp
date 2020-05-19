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
	  mCloseAllTabs(new QAction(this))
{
	mCloseTab->setText(tr("Close"));
	mCloseTab->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F4));

	mClosedOtherTabs->setText(tr("Close Other"));
	mCloseAllTabs->setText(tr("Close All"));

	connect(mCloseTab, &QAction::triggered, this, &AnnotationTabContextMenu::closeTabTriggered);
	connect(mClosedOtherTabs, &QAction::triggered, this, &AnnotationTabContextMenu::closeOtherTabsTriggered);
	connect(mCloseAllTabs, &QAction::triggered, this, &AnnotationTabContextMenu::closeAllTabsTriggered);

	addAction(mCloseTab);
	addAction(mClosedOtherTabs);
	addAction(mCloseAllTabs);
}

AnnotationTabContextMenu::~AnnotationTabContextMenu()
{
	delete mCloseTab;
	delete mClosedOtherTabs;
	delete mCloseAllTabs;
}

void AnnotationTabContextMenu::show(int tabIndex, const QPoint &pos)
{
	mTabIndex = tabIndex;
	exec(pos);
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

} // namespace kImageAnnotator