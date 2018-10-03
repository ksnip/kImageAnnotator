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

#ifndef KIMAGEANNOTATOR_SCALEWIDGET_H
#define KIMAGEANNOTATOR_SCALEWIDGET_H

#include <QWidget>
#include <QGraphicsView>
#include <QVBoxLayout>

#include "ScaleDialog.h"
#include "src/annotations/core/AnnotationArea.h"

namespace kImageAnnotator {

class ScaleWidget : public QWidget
{
Q_OBJECT
public:
	explicit ScaleWidget(AnnotationArea *annotationArea);
	~ScaleWidget();
	void activate();

signals:
	void closing() const;

private:
	AnnotationArea *mAnnotationArea;
	QGraphicsView *mView;
	QVBoxLayout *mMainLayout;

	void initGui();
	void showDialog();
	void scale(const QSize &newSize);
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_SCALEWIDGET_H
