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

#ifndef ANNOTATIONTAB_H
#define ANNOTATIONTAB_H

#include <QWidget>
#include <QHBoxLayout>

#include "AnnotationView.h"
#include "AnnotationSettings.h"
#include "src/annotations/core/AnnotationArea.h"

namespace kImageAnnotator {

class AnnotationTabContent : public QWidget
{
	Q_OBJECT
public:
	AnnotationTabContent(const QPixmap &pixmap, Config *config, AbstractSettingsProvider *settingsProvider);
	~AnnotationTabContent() override;

	AnnotationArea* annotationArea() const;

private:
	AnnotationArea *mAnnotationArea;
	AnnotationView *mAnnotationView;
	QHBoxLayout *mMainLayout;
};

} // namespace kImageAnnotator

#endif //ANNOTATIONTAB_H
