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

#ifndef KIMAGEANNOTATOR_ANNOTATIONGENERALSETTINGS_H
#define KIMAGEANNOTATOR_ANNOTATIONGENERALSETTINGS_H

#include "src/gui/annotator/docks/AbstractAnnotationDockWidgetContent.h"
#include "src/widgets/settingsPicker/ZoomPicker.h"

namespace kImageAnnotator {

class AnnotationGeneralSettings : public AbstractAnnotationDockWidgetContent
{
Q_OBJECT
public:
	explicit AnnotationGeneralSettings();
	~AnnotationGeneralSettings() override;
	void updateZoomLevel(double value);
	QString name() const override;

signals:
	void zoomValueChanged(double value);

private:
	QBoxLayout *mMainLayout;
	ZoomPicker *mZoomPicker;

	void initGui();
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_ANNOTATIONGENERALSETTINGS_H
