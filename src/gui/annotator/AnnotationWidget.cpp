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

AnnotationWidget::AnnotationWidget(AnnotationArea *annotationArea, Config *config)
{
	mConfig = config;
	mAnnotationArea = annotationArea;

	initGui();
}

AnnotationWidget::~AnnotationWidget()
{
	delete mView;
	delete mMainLayout;
	delete mSettings;
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
	mView = new AnnotationView(mAnnotationArea);
	mSettings =  new AnnotationSettings(mConfig);
	mMainLayout = new QHBoxLayout();
	mMainLayout->addWidget(mSettings);
	mMainLayout->addWidget(mView);

	setLayout(mMainLayout);
	setFocusPolicy(Qt::ClickFocus);

	connect(mAnnotationArea, &AnnotationArea::itemsSelected, this, &AnnotationWidget::editItems);
}

void AnnotationWidget::editItems(const QList<AbstractAnnotationItem *> &items)
{
	if(items.count() != 1) {
		mSettings->setSelect();
		return;
	}
	auto item = items.first();
	mSettings->loadFromItem(item);
}

} // namespace kImageAnnotator
