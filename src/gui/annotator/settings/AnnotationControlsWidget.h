/*
 * Copyright (C) 2021 Antonio Prcela <antonio.prcela@gmail.com>
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

#ifndef KIMAGEANNOTATOR_ANNOTATIONCONTROLSWIDGET_H
#define KIMAGEANNOTATOR_ANNOTATIONCONTROLSWIDGET_H

#include "src/gui/annotator/docks/AbstractAnnotationDockWidgetContent.h"
#include "src/widgets/Controls.h"

namespace kImageAnnotator {

class AnnotationControlsWidget : public AbstractAnnotationDockWidgetContent
{
Q_OBJECT
public:
	AnnotationControlsWidget();
	~AnnotationControlsWidget() override = default;
	void setOrientation(Qt::Orientation orientation) override;
	QString name() const override;

Q_SIGNALS:
	void undo() const;
	void redo() const;
	void showCrop() const;
	void showScale() const;
	void showRotate() const;
	void showModifyCanvas() const;
	void showCut() const;

private:
	QBoxLayout *mMainLayout;
	Controls *mControls;
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_ANNOTATIONCONTROLSWIDGET_H

