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

#ifndef KIMAGEANNOTATOR_ANNOTATIONTOOLSELECTION_H
#define KIMAGEANNOTATOR_ANNOTATIONTOOLSELECTION_H

#include "src/gui/annotator/docks/AnnotationDockWidgetContent.h"
#include "src/widgets/ToolPicker.h"

namespace kImageAnnotator {

class AnnotationToolSelection : public AnnotationDockWidgetContent
{
Q_OBJECT
public:
	AnnotationToolSelection();
	~AnnotationToolSelection() override;
	Tools toolType() const;
	void setToolType(Tools tool);
	void setOrientation(Qt::Orientation orientation) override;
	QString name() const override;

signals:
	void toolTypeChanged(Tools toolType);

private:
	QVBoxLayout *mMainLayout;
	ToolPicker *mToolPicker;
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_ANNOTATIONTOOLSELECTION_H
