/*
 * Copyright (C) 2021 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KIMAGEANNOTATOR_ANNOTATIONDOCKWIDGETDRAGHANDLE_H
#define KIMAGEANNOTATOR_ANNOTATIONDOCKWIDGETDRAGHANDLE_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>

#include "src/common/helper/IconLoader.h"
#include "src/common/provider/ScaledSizeProvider.h"

namespace kImageAnnotator {

class AnnotationDockWidgetDragHandle : public QWidget
{
	Q_OBJECT
public:
	explicit AnnotationDockWidgetDragHandle(QWidget *parent);
	~AnnotationDockWidgetDragHandle() override = default;
	QSize sizeHint() const override;
	QSize minimumSizeHint() const override;
	void setOrientation(Qt::Orientation orientation);

protected:
	void paintEvent(QPaintEvent *event) override;
	void mouseDoubleClickEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;

private:
	QPixmap mVerticalHandlerImage;
	QPixmap mHorizontalHandlerImage;
	QLabel *mLabel;
	QHBoxLayout *mLayout;

	void initGui();
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_ANNOTATIONDOCKWIDGETDRAGHANDLE_H
