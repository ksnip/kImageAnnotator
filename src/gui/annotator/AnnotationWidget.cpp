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

#include "AnnotationWidget.h"

namespace kImageAnnotator {

AnnotationWidget::AnnotationWidget(Config *config) :
	mConfig(config),
	mItemSettings(new AnnotationItemSettings()),
	mGeneralSettings(new AnnotationGeneralSettings),
	mToolSelection(new AnnotationToolSelection),
	mImageSettings(new AnnotationImageSettings),
	mSettingsAdapter(new AnnotationSettingsAdapter(mGeneralSettings, mItemSettings, mToolSelection, mImageSettings, config)),
	mAnnotationTabWidget(new AnnotationTabWidget(config, mSettingsAdapter))
{
	initGui();
	restoreDockWidgets();
}

AnnotationWidget::~AnnotationWidget()
{
	delete mSettingsAdapter;
	delete mItemSettings;
	delete mToolSelection;
	delete mImageSettings;
	delete mGeneralSettings;
}

QSize AnnotationWidget::sizeHint() const
{
	auto offset = ScaledSizeProvider::scaledSize(QSize(100, 100));
	return QMainWindow::sizeHint() + offset;
}

void AnnotationWidget::initGui()
{
	setCentralWidget(mAnnotationTabWidget);

	insertDockWidget(Qt::LeftDockWidgetArea, mToolSelection);
	insertDockWidget(Qt::TopDockWidgetArea, mItemSettings);
	insertDockWidget(Qt::BottomDockWidgetArea, mGeneralSettings);
	insertDockWidget(Qt::BottomDockWidgetArea, mImageSettings);

	setFocusPolicy(Qt::ClickFocus);

	connect(mAnnotationTabWidget, &AnnotationTabWidget::imageChanged, this, &AnnotationWidget::imageChanged);
	connect(mAnnotationTabWidget, &AnnotationTabWidget::currentChanged, this, &AnnotationWidget::currentTabChanged);
	connect(mAnnotationTabWidget, &AnnotationTabWidget::tabCloseRequested, this, &AnnotationWidget::tabCloseRequested);
	connect(mAnnotationTabWidget, &AnnotationTabWidget::tabMoved, this, &AnnotationWidget::tabMoved);
	connect(mAnnotationTabWidget, &AnnotationTabWidget::tabContextMenuOpened, this, &AnnotationWidget::tabContextMenuOpened);

	connect(qApp, &QCoreApplication::aboutToQuit, this, &AnnotationWidget::persistDockWidgets);
}

void AnnotationWidget::insertDockWidget(Qt::DockWidgetArea area, AnnotationDockWidgetContent *content)
{
	auto dockWidget = new AnnotationDockWidget(content);
	mDockWidgets.append(dockWidget);
	addDockWidget(area, dockWidget);
}

QImage AnnotationWidget::image() const
{
	auto currentAnnotationArea = annotationArea();
	return currentAnnotationArea != nullptr ? currentAnnotationArea->image() : QImage();
}

QImage AnnotationWidget::imageAt(int index) const
{
	auto annotationArea = annotationAreaAt(index);
	return annotationArea != nullptr ? annotationArea->image() : QImage();
}

void AnnotationWidget::loadImage(const QPixmap &pixmap)
{
	auto currentAnnotationArea = annotationArea();
	if(currentAnnotationArea == nullptr) {
		addTab(pixmap, QString(), QString());
	} else {
		currentAnnotationArea->loadImage(pixmap);
	}
}

int AnnotationWidget::addTab(const QPixmap &pixmap, const QString &title, const QString &toolTip)
{
	return mAnnotationTabWidget->addTab(pixmap, title, toolTip);
}

void AnnotationWidget::updateTabInfo(int index, const QString &title, const QString &toolTip)
{
	mAnnotationTabWidget->updateTabInfo(index, title, toolTip);
}

void AnnotationWidget::insertImageItem(const QPointF &position, const QPixmap &pixmap) const
{
	auto currentAnnotationArea = annotationArea();
	if(currentAnnotationArea != nullptr) {
		currentAnnotationArea->insertImageItem(position, pixmap);
	}
}

void AnnotationWidget::removeTab(int index)
{
	mAnnotationTabWidget->removeTab(index);
}

void AnnotationWidget::setUndoEnabled(bool enabled)
{
	mAnnotationTabWidget->setUndoRedoEnabled(enabled);
}

QAction *AnnotationWidget::undoAction() const
{
	return mAnnotationTabWidget->undoAction();
}

QAction *AnnotationWidget::redoAction() const
{
	return mAnnotationTabWidget->redoAction();
}

void AnnotationWidget::clearSelection() const
{
	auto currentAnnotationArea = annotationArea();
	if(currentAnnotationArea != nullptr) {
		annotationArea()->clearSelection();
	}
}

AnnotationArea *AnnotationWidget::annotationArea() const
{
	return mAnnotationTabWidget->currentAnnotationArea();
}

AnnotationArea *AnnotationWidget::annotationAreaAt(int index) const
{
	return mAnnotationTabWidget->annotationAreaAt(index);
}

void AnnotationWidget::reloadConfig()
{
	mSettingsAdapter->reloadConfig();
}

void AnnotationWidget::setTabBarAutoHide(bool enabled)
{
	mAnnotationTabWidget->setTabBarAutoHide(enabled);
}

void AnnotationWidget::setStickers(const QStringList &stickerPaths, bool keepDefault)
{
	mItemSettings->setStickers(stickerPaths, keepDefault);
}

void AnnotationWidget::addTabContextMenuActions(const QList<QAction *> &actions)
{
	mAnnotationTabWidget->addContextMenuActions(actions);
}

void AnnotationWidget::setSettingsCollapsed(bool isCollapsed)
{
	for(auto dockWidget : mDockWidgets) {
		dockWidget->setCollapsed(isCollapsed);
	}
}

void AnnotationWidget::persistDockWidgets()
{
	mConfig->setAnnotatorDockWidgetsState(saveState());
}

void AnnotationWidget::restoreDockWidgets()
{
	restoreState(mConfig->annotatorDockWidgetsState());
}

} // namespace kImageAnnotator
