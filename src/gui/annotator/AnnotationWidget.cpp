/*
 * Copyright (C) 2018 Damir Porobic <damir.porobic@gmx.com>
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

#include "AnnotationWidget.h"

namespace kImageAnnotator {

AnnotationWidget::AnnotationWidget(Config *config)
{
	mConfig = config;

	initGui();
}

AnnotationWidget::~AnnotationWidget()
{
	delete mAnnotationView;
	delete mMainLayout;
	delete mSettings;
	delete mAnnotationArea;
}

QSize AnnotationWidget::sizeHint() const
{
	auto minSize = mSettings->sizeHint();
	auto sceneSize = mAnnotationArea->sceneRect().size();
	auto width = minSize.width() + sceneSize.width();
	auto height = (minSize.height() > sceneSize.height()) ? minSize.height() : sceneSize.height();
	auto offset = QSize(100, 100);
	return QSize(static_cast<int>(width), static_cast<int>(height)) + offset;
}

void AnnotationWidget::initGui()
{
	mSettings =  new AnnotationSettings(mConfig);
	mAnnotationArea = new AnnotationArea(mConfig, mSettings);
	mAnnotationView = new AnnotationView(mAnnotationArea);
	mMainLayout = new QHBoxLayout();
	mMainLayout->addWidget(mSettings);
	mMainLayout->addWidget(mAnnotationView);

	setLayout(mMainLayout);
	setFocusPolicy(Qt::ClickFocus);

	connect(mAnnotationArea, &AnnotationArea::imageChanged, this, &AnnotationWidget::imageChanged);
	connect(mAnnotationArea, &AnnotationArea::itemsSelected, this, &AnnotationWidget::editItems);
}

void AnnotationWidget::editItems(const QList<AbstractAnnotationItem *> &items)
{
	if(items.count() != 1) {
		mSettings->activateSelectTool();
		return;
	}
	auto item = items.first();
	mSettings->loadFromItem(item);
}

QImage AnnotationWidget::image() const
{
	return mAnnotationArea->image();
}

void AnnotationWidget::loadImage(const QPixmap &pixmap)
{
	mAnnotationArea->loadImage(pixmap);
}

void AnnotationWidget::insertImageItem(const QPointF &position, const QPixmap &pixmap)
{
	mAnnotationArea->insertImageItem(position, pixmap);
}

void AnnotationWidget::setUndoEnabled(bool enabled)
{
	mAnnotationArea->setUndoEnabled(enabled);
}

QAction *AnnotationWidget::undoAction() const
{
	return mAnnotationArea->undoAction();
}

QAction *AnnotationWidget::redoAction() const
{
	return mAnnotationArea->redoAction();
}

void AnnotationWidget::clearSelection()
{
	mAnnotationArea->clearSelection();
}

AnnotationArea *AnnotationWidget::annotationArea() const
{
	return mAnnotationArea;
}

} // namespace kImageAnnotator
