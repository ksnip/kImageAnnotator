/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef ANNOTATIONTABWIDGET_H
#define ANNOTATIONTABWIDGET_H

#include <QTabWidget>
#include <QPixmap>

#include "AnnotationTabContent.h"
#include "AnnotationTabContextMenu.h"
#include "AnnotationTabCloser.h"
#include "AnnotationTabClickEventFilter.h"
#include "src/common/filter/KeyEventFilter.h"


namespace kImageAnnotator {

class AnnotationTabWidget : public QTabWidget
{
	Q_OBJECT
public:
	AnnotationTabWidget(Config *config, AbstractSettingsProvider *settingsProvider);
	~AnnotationTabWidget() override = default;
	int addTab(const QPixmap &image, const QString &title, const QString &toolTip);
	int insertTab(int index, const QPixmap &image, const QString &title, const QString &toolTip);
	AnnotationArea* currentAnnotationArea() const;
	AnnotationArea *annotationAreaAt(int index) const;
	ZoomValueProvider* currentZoomValueProvider() const;
	QAction* undoAction() const;
	QAction* redoAction() const;
	void updateTabInfo(int index, const QString &title, const QString &toolTip);
	void setUndoRedoEnabled(bool enabled);
    void addContextMenuActions(const QList<QAction*> & actions);

signals:
	void imageChanged() const;
	void tabMoved(int fromIndex, int toIndex) const;
	void tabContextMenuOpened(int index) const;

public slots:
	void undoTriggered() const;
	void redoTriggered() const;

protected:
	void tabInserted(int index) override;
	void tabRemoved(int index) override;

private:
	Config *mConfig;
	QTabBar *mTabBar;
	AbstractSettingsProvider *mSettingsProvider;
	QAction *mUndoAction;
	QAction *mRedoAction;
	AnnotationTabContextMenu *mTabContextMenu;
	AnnotationTabCloser *mTabCloser;
	AnnotationTabClickEventFilter *mTabClickFilter;
	AnnotationItemClipboard *mItemClipboard;
	KeyEventFilter mKeyEventFilter;

private slots:
	void updateCurrentWidget(int index);
	void showTabContextMenu(const QPoint &pos);
	void tabChanged();
};

} // namespace kImageAnnotator

#endif //ANNOTATIONTABWIDGET_H
