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

#ifndef KIMAGEANNOTATOR_ANNOTATIONTABCONTEXTMENU_H
#define KIMAGEANNOTATOR_ANNOTATIONTABCONTEXTMENU_H

#include <QMenu>

namespace kImageAnnotator {

class AnnotationTabContextMenu : public QMenu
{
	Q_OBJECT
public:
	explicit AnnotationTabContextMenu(QWidget *parent);
	~AnnotationTabContextMenu() override;
	void show(int tabIndex, const QPoint &pos);
	void addCustomActions(const QList<QAction*> & customActions);

signals:
	void closeTab(int index) const;
	void closeOtherTabs(int index) const;
	void closeAllTabs() const;
	void closeAllTabsToLeft(int index) const;
	void closeAllTabsToRight(int index) const;

private:
	int mTabIndex;
	QAction *mCloseTab;
	QAction *mClosedOtherTabs;
	QAction *mCloseAllTabs;
	QAction *mCloseAllTabsToLeft;
	QAction *mCloseAllTabsToRight;
	QHash<QAction*, QAction*> mCustomActionMap;

	void closeTabTriggered() const;
	void closeOtherTabsTriggered() const;
	void closeAllTabsTriggered() const;
	void closeAllTabsToLeftTriggered() const;
	void closeAllTabsToRightTriggered() const;

private slots:
    void customActionTriggered();
    void customActionChanged();
	void addCustomAction(QAction *innerAction);
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_ANNOTATIONTABCONTEXTMENU_H
