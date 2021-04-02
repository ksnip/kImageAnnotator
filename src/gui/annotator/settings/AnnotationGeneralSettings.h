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

#include "src/gui/annotator/docks/AnnotationDockWidgetContent.h"
#include "src/widgets/ImageEffectPicker.h"
#include "src/widgets/ZoomIndicator.h"

namespace kImageAnnotator {

class AnnotationGeneralSettings : public AnnotationDockWidgetContent
{
Q_OBJECT
public:
	explicit AnnotationGeneralSettings();
	~AnnotationGeneralSettings() override;
	ImageEffects effect() const;
	void setEffect(ImageEffects effect);
	void updateZoomLevel(double value);
	void setOrientation(Qt::Orientation orientation) override;
	QString name() const override;

signals:
	void effectChanged(ImageEffects effect);
	void zoomValueChanged(double value);

private:
	QBoxLayout *mMainLayout;
	ZoomIndicator *mZoomIndicator;
	ImageEffectPicker *mEffectPicker;

	void initGui();
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_ANNOTATIONGENERALSETTINGS_H
