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

#ifndef KIMAGEANNOTATOR_ANNOTATIONWIDGET_H
#define KIMAGEANNOTATOR_ANNOTATIONWIDGET_H

#include <QWidget>
#include <QHBoxLayout>

#include "AnnotationView.h"
#include "AnnotationSettings.h"
#include "src/annotations/core/AnnotationArea.h"

namespace kImageAnnotator {

class AnnotationWidget : public QWidget
{
Q_OBJECT
public:
	explicit AnnotationWidget(AnnotationArea *annotationArea, Config *config);
	~AnnotationWidget() override;
	QSize sizeHint() const override;

private:
	AnnotationArea *mAnnotationArea;
	AnnotationView *mView;
	AnnotationSettings *mSettings;
	QHBoxLayout *mMainLayout;
	Config *mConfig;

	void initGui();

private slots:
	void editItems(const QList<AbstractAnnotationItem *> &items);
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_ANNOTATIONWIDGET_H
