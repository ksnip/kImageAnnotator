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

#ifndef KIMAGEANNOTATOR_ANNOTATIONSETTINGSADAPTER_H
#define KIMAGEANNOTATOR_ANNOTATIONSETTINGSADAPTER_H

#include "AnnotationGeneralSettings.h"
#include "AnnotationItemSettings.h"
#include "AnnotationToolSelection.h"
#include "src/annotations/core/AbstractSettingsProvider.h"

namespace kImageAnnotator {

class AnnotationSettingsAdapter : public QObject, public AbstractSettingsProvider
{
	Q_OBJECT
public:
	explicit AnnotationSettingsAdapter(AnnotationGeneralSettings *generalSettings, AnnotationItemSettings *itemSettings, AnnotationToolSelection *toolSettings, Config *config);
	~AnnotationSettingsAdapter() override = default;
	void editItem(AbstractAnnotationItem *item) override;
	void activateSelectTool() override;
	Tools toolType() const override;
	QColor toolColor() const override;
	QColor textColor() const override;
	int toolWidth() const override;
	int fontSize() const override;
	FillModes fillType() const override;
	int obfuscationFactor() const override;
	QString sticker() const override;
	ImageEffects effect() const override;
	void updateNumberToolSeed(int numberToolSeed) override;
	void updateZoomLevel(double value) override;
	void reloadConfig();

private:
	AnnotationGeneralSettings *mGeneralSettings;
	AnnotationItemSettings *mItemSettings;
	AnnotationToolSelection *mToolSettings;
	Config *mConfig;
	bool mEditExistingItem;

private slots:
	void effectChanged(ImageEffects effect) override;
	void zoomValueChanged(double value) override;
	void toolTypeChanged(Tools toolType);
	void loadFromConfig(Tools tool);
	void loadFromItem(const AbstractAnnotationItem *item);
	void toolColorChanged(const QColor &color);
	void toolTextColorChanged(const QColor &color);
	void toolWidthChanged(int width);
	void toolFillTypeChanged(FillModes fill);
	void toolFontSizeChanged(int size);
	void notifyNumberToolSeedChanged(int newNumberToolSeed);
	void obfuscateFactorChanged(int factor);
	void stickerChanged(const QString &sticker);
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_ANNOTATIONSETTINGSADAPTER_H
