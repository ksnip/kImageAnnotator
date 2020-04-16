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

#include "AnnotationTabWidget.h"

namespace kImageAnnotator {

AnnotationTabWidget::AnnotationTabWidget(Config *config, AbstractSettingsProvider *settingsProvider) :
	mConfig(config),
	mSettingsProvider(settingsProvider),
	mRedoAction(new QAction(this)),
	mUndoAction(new QAction(this))
{
	setTabBarAutoHide(true);
	setMovable(true);
	setTabsClosable(false);

	connect(mUndoAction, &QAction::triggered, this, &AnnotationTabWidget::undoTriggered);
	connect(mRedoAction, &QAction::triggered, this, &AnnotationTabWidget::redoTriggered);
	connect(tabBar(), &QTabBar::tabMoved, this, &AnnotationTabWidget::tabMoved);
}

int AnnotationTabWidget::addImage(const QPixmap &image, const QString &title, const QString &toolTip)
{
	auto content = new AnnotationTabContent(image, mConfig, mSettingsProvider);
	connect(content->annotationArea(), &AnnotationArea::imageChanged, this, &AnnotationTabWidget::imageChanged);

	return QTabWidget::addTab(content, title);
}

AnnotationArea* AnnotationTabWidget::currentAnnotationArea() const
{
	return currentWidget() != nullptr ? dynamic_cast<AnnotationTabContent*>(currentWidget())->annotationArea() : nullptr;
}

QAction *AnnotationTabWidget::undoAction() const
{
	return mUndoAction;
}

QAction *AnnotationTabWidget::redoAction() const
{
	return mRedoAction;
}

void AnnotationTabWidget::updateTabInfo(int index, const QString &title, const QString &toolTip)
{
	setTabText(index, title);
	setTabToolTip(index, toolTip);
}

void AnnotationTabWidget::setUndoRedoEnabled(bool enabled)
{
	mUndoAction->setEnabled(enabled);
	mRedoAction->setEnabled(enabled);
}

void AnnotationTabWidget::tabInserted(int index)
{
	updateCurrentWidget(index);
	updateTabsClosable();
	QTabWidget::tabInserted(index);
}

void AnnotationTabWidget::tabRemoved(int index)
{
	updateTabsClosable();
	QTabWidget::tabRemoved(index);
}

void AnnotationTabWidget::undoTriggered()
{
	auto annotationArea = currentAnnotationArea();
	if(annotationArea != nullptr) {
		annotationArea->undoAction()->trigger();
	}
}

void AnnotationTabWidget::redoTriggered()
{
	auto annotationArea = currentAnnotationArea();
	if(annotationArea != nullptr) {
		annotationArea->redoAction()->trigger();
	}
}

void AnnotationTabWidget::updateTabsClosable()
{
	setTabsClosable(count() > 1);
}

void AnnotationTabWidget::updateCurrentWidget(int index)
{
	setCurrentIndex(index);
}

} // namespace kImageAnnotator