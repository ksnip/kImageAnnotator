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

#ifndef KIMAGEANNOTATOR_ANNOTATIONWIDGET_H
#define KIMAGEANNOTATOR_ANNOTATIONWIDGET_H

#include <QHBoxLayout>

#include "src/gui/annotator/tabs/AnnotationTabWidget.h"
#include "src/annotations/core/AnnotationArea.h"
#include "src/common/provider/ScaledSizeProvider.h"

namespace kImageAnnotator {

class AnnotationWidget : public QWidget
{
Q_OBJECT
public:
	explicit AnnotationWidget(Config *config);
	~AnnotationWidget() override;
	QSize sizeHint() const override;
	QImage image() const;
	QImage imageAt(int index) const;
	void loadImage(const QPixmap &pixmap);
	int addTab(const QPixmap &pixmap, const QString &title, const QString &toolTip);
	void updateTabInfo(int index, const QString &title, const QString &toolTip);
	void insertImageItem(const QPointF &position, const QPixmap &pixmap) const;
	void removeTab(int index);
	void setUndoEnabled(bool enabled);
	QAction* undoAction() const;
	QAction* redoAction() const;
	void clearSelection() const;
	AnnotationArea* annotationArea() const;
	AnnotationArea *annotationAreaAt(int index) const;
	void reloadConfig();
	void setTabBarAutoHide(bool enabled);
	void setStickers(const QStringList &stickerPaths, bool keepDefault);
	void addTabContextMenuActions(const QList<QAction*> & actions);
	void setSettingsCollapsed(bool isCollapsed);

signals:
	void imageChanged() const;
	void currentTabChanged(int index) const;
	void tabCloseRequested(int index) const;
	void tabMoved(int fromIndex, int toIndex);
	void tabContextMenuOpened(int index) const;

private:
	AnnotationSettings *mSettings;
	AnnotationTabWidget *mAnnotationTabWidget;
	QHBoxLayout *mMainLayout;

	void initGui();
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_ANNOTATIONWIDGET_H
