/*
 * Copyright (C) 2018 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KIMAGEANNOTATOR_CONFIG_H
#define KIMAGEANNOTATOR_CONFIG_H

#include <QObject>
#include <QPointF>
#include <QColor>
#include <QHash>
#include <QFont>
#include <QSettings>

#include "src/common/enum/Tools.h"
#include "src/common/enum/FillModes.h"
#include "src/common/helper/ConfigNameHelper.h"

namespace kImageAnnotator {

class Config : public QObject
{
Q_OBJECT

public:
	explicit Config();
	~Config() override = default;

public slots:
	Tools selectedTool() const;
	void setSelectedToolType(Tools tool);

	QColor toolColor(Tools tool) const;
	void setToolColor(const QColor &color, Tools tool);

	QColor toolTextColor(Tools tool) const;
	void setToolTextColor(const QColor &color, Tools tool);

	int toolWidth(Tools tool) const;
	void setToolWidth(int size, Tools tool);

	FillModes toolFillType(Tools tool) const;
	void setToolFillType(FillModes fillType, Tools tool);

	QFont toolFont(Tools toolType) const;
	void setToolFont(const QFont &font, Tools toolType);

	int toolFontSize(Tools toolType) const;
	void setToolFontSize(int fontSize, Tools toolType);

	bool itemShadowEnabled() const;
	void setItemShadowEnabled(bool enabled);

	bool smoothPathEnabled() const;
	void setSmoothPathEnabled(bool enabled);

	void setSaveToolSelection(bool enabled);

	int smoothFactor() const;
	void setSmoothFactor(int factor);

	bool switchToSelectToolAfterDrawingItem() const;
	void setSwitchToSelectToolAfterDrawingItem(bool enabled);

	int obfuscationFactor(Tools toolType) const;
	void setObfuscationFactor(int factor, Tools toolType);

private:
	QSettings mConfig;
	QList<Tools> mAllTools;
	Tools mSelectTool;
	QHash<Tools, QColor> mToolToColor;
	QHash<Tools, QColor> mToolToTextColor;
	QHash<Tools, int> mToolToWidth;
	QHash<Tools, FillModes> mToolToFillType;
	QHash<Tools, QFont> mToolToFont;
	QHash<Tools, int> mToolToObfuscationFactor;
	bool mItemShadowEnabled;
	bool mSmoothPathEnabled;
	bool mSaveToolSelection;
	int mSmoothFactor;
	bool mSwitchToSelectToolAfterDrawingItem;

	void initToolSettings();
	void initSelectedTool();
	void initToolColors();
	void initToolTextColors();
	void initToolWidths();
	void initToolFillTypes();
	void initToolFonts();
	void initObfuscateFactor();
	void initGeneralSettings();

	QColor loadToolColor(Tools toolType);
	void saveToolColor(Tools toolType, const QColor &color);
	QColor loadToolTextColor(Tools toolType);
	void saveToolTextColor(Tools toolType, const QColor &color);
	int loadToolWidth(Tools toolType);
	void saveToolWidth(Tools toolType, int size);
	FillModes loadToolFillType(Tools toolType);
	void saveToolFillType(Tools toolType, FillModes fillType);
	Tools loadToolType();
	void saveToolType(Tools toolType);
	int loadToolFontSize(Tools toolType);
	void saveToolFontSize(Tools toolType, int fontSize);
	int loadObfuscateFactor(Tools toolType);
	void saveObfuscateFactor(Tools toolType, int radius);

	static QColor defaultToolColor(Tools toolType) ;
	static QColor defaultToolTextColor(Tools toolType) ;
	static int defaultToolWidth(Tools toolType) ;
	static FillModes defaultToolFillMode(Tools toolType) ;
	static Tools defaultToolType();
	static int defaultToolFontSize(Tools toolType) ;
	static int defaultObfuscateFactor() ;
};

} // namespace kImageAnnotator

#endif // KIMAGEANNOTATOR_CONFIG_H
