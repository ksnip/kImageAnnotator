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

#include "CoreView.h"

namespace kImageAnnotator {

CoreView::CoreView(Config *config) :
	mConfig(config),
	mAnnotationWidget(new AnnotationWidget(mConfig)),
	mCropWidget(new CropWidget),
	mScaleWidget(new ScaleWidget),
	mRotateWidget(new RotateWidget),
	mModifyCanvasWidget(new ModifyCanvasWidget)
{
	addWidget(mAnnotationWidget);
	addWidget(mCropWidget);
	addWidget(mScaleWidget);
	addWidget(mRotateWidget);
	addWidget(mModifyCanvasWidget);

	connect(mAnnotationWidget, &AnnotationWidget::imageChanged, this, &CoreView::imageChanged);
	connect(mAnnotationWidget, &AnnotationWidget::currentTabChanged, this, &CoreView::currentTabChanged);
	connect(mAnnotationWidget, &AnnotationWidget::tabCloseRequested, this, &CoreView::tabCloseRequested);
	connect(mAnnotationWidget, &AnnotationWidget::tabMoved, this, &CoreView::tabMoved);
	connect(mAnnotationWidget, &AnnotationWidget::tabContextMenuOpened, this, &CoreView::tabContextMenuOpened);
	connect(mAnnotationWidget, &AnnotationWidget::activateCrop, this, &CoreView::showCropper);
	connect(mAnnotationWidget, &AnnotationWidget::activateScale, this, &CoreView::showScaler);
	connect(mAnnotationWidget, &AnnotationWidget::activateModifyCanvas, this, &CoreView::showCanvasModifier);
	connect(mCropWidget, &CropWidget::closing, this, &CoreView::showAnnotator);
	connect(mScaleWidget, &ScaleWidget::closing, this, &CoreView::showAnnotator);
	connect(mRotateWidget, &RotateWidget::closing, this, &CoreView::showAnnotator);
	connect(mModifyCanvasWidget, &ModifyCanvasWidget::closing, this, &CoreView::showAnnotator);
}

CoreView::~CoreView()
{
	delete mAnnotationWidget;
	delete mCropWidget;
	delete mScaleWidget;
	delete mRotateWidget;
	delete mModifyCanvasWidget;
}

QImage CoreView::image() const
{
	return mAnnotationWidget->image();
}

QImage CoreView::imageAt(int index) const
{
	return mAnnotationWidget->imageAt(index);
}

void CoreView::loadImage(const QPixmap &pixmap)
{
	mAnnotationWidget->loadImage(pixmap);
}

int CoreView::addTab(const QPixmap &pixmap, const QString &title, const QString &toolTip)
{
	return mAnnotationWidget->addTab(pixmap, title, toolTip);
}

void CoreView::updateTabInfo(int index, const QString &title, const QString &toolTip)
{
	mAnnotationWidget->updateTabInfo(index, title, toolTip);
}

void CoreView::insertImageItem(const QPointF &position, const QPixmap &pixmap)
{
    mAnnotationWidget->insertImageItem(position, pixmap);
}

void CoreView::removeTab(int index)
{
	mAnnotationWidget->removeTab(index);
}

void CoreView::showAnnotator()
{
	mAnnotationWidget->setUndoEnabled(true);
	setCurrentWidget(mAnnotationWidget);
}

void CoreView::showCropper()
{
	mAnnotationWidget->setUndoEnabled(false);
	mAnnotationWidget->clearSelection();
	setCurrentWidget(mCropWidget);
	mCropWidget->activate(mAnnotationWidget->annotationArea());
}

void CoreView::showScaler()
{
	mAnnotationWidget->setUndoEnabled(false);
	mAnnotationWidget->clearSelection();
	setCurrentWidget(mScaleWidget);
	mScaleWidget->activate(mAnnotationWidget->annotationArea());
}

void CoreView::showRotator()
{
	mAnnotationWidget->setUndoEnabled(false);
	mAnnotationWidget->clearSelection();
	setCurrentWidget(mRotateWidget);
	mRotateWidget->activate(mAnnotationWidget->annotationArea());
}

void CoreView::showCanvasModifier()
{
	mAnnotationWidget->setUndoEnabled(false);
	mAnnotationWidget->clearSelection();
	setCurrentWidget(mModifyCanvasWidget);
	mModifyCanvasWidget->activate(mAnnotationWidget->annotationArea());
}

void CoreView::showControlsWidget()
{
	mAnnotationWidget->showControlsWidget();
}

void CoreView::setSettingsCollapsed(bool isCollapsed)
{
	mAnnotationWidget->setSettingsCollapsed(isCollapsed);
}

void CoreView::setTabBarAutoHide(bool enabled)
{
	mAnnotationWidget->setTabBarAutoHide(enabled);
}

QAction *CoreView::undoAction()
{
	return mAnnotationWidget->undoAction();
}

QAction *CoreView::redoAction()
{
	return mAnnotationWidget->redoAction();
}

QSize CoreView::sizeHint() const
{
	return mAnnotationWidget->sizeHint();
}

void CoreView::reloadConfig()
{
	mAnnotationWidget->reloadConfig();
}

void CoreView::setStickers(const QStringList &stickerPaths, bool keepDefault)
{
	mAnnotationWidget->setStickers(stickerPaths, keepDefault);
}

void CoreView::addTabContextMenuActions(const QList<QAction *> &actions)
{
	mAnnotationWidget->addTabContextMenuActions(actions);
}

} // namespace kImageAnnotator
