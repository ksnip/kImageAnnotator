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

#include "ISettings.h"
#include "src/common/enum/Tools.h"
#include "src/common/enum/FillModes.h"
#include "src/common/enum/NumberUpdateMode.h"
#include "src/common/helper/ConfigNameHelper.h"

namespace kImageAnnotator {

class Config : public QObject
{
Q_OBJECT
public:
	explicit Config(const QSharedPointer<ISettings> &settings);
	~Config() override = default;

public slots:
	Tools selectedTool() const;
	void setSelectedToolType(Tools tool);

	QColor toolColor(Tools tool) const;
	void setToolColor(const QColor &color, Tools tool);

	QColor toolTextColor(Tools tool) const;
	void setToolTextColor(const QColor &color, Tools tool);

	int toolWidth(Tools tool) const;
	void setToolWidth(int width, Tools tool);

	FillModes toolFillType(Tools tool) const;
	void setToolFillType(FillModes fillType, Tools tool);

	QFont toolFont(Tools tool) const;
	void setToolFont(const QFont &font, Tools tool);

	bool shadowEnabled(Tools tool) const;
	void setShadowEnabled(bool enabled, Tools tool);

	bool smoothPathEnabled() const;
	void setSmoothPathEnabled(bool enabled);

	void setSaveToolSelection(bool enabled);

	int smoothFactor() const;
	void setSmoothFactor(int factor);

	bool switchToSelectToolAfterDrawingItem() const;
	void setSwitchToSelectToolAfterDrawingItem(bool enabled);

	NumberUpdateMode numberUpdateMode() const;
	void setNumberToolUpdateMode(enum NumberUpdateMode numberUpdateMode);

	int obfuscationFactor(Tools toolType) const;
	void setObfuscationFactor(int factor, Tools toolType);

	QColor canvasColor() const;
	void setCanvasColor(const QColor &color);

	QByteArray annotatorDockWidgetsState() const;
	void setAnnotatorDockWidgetsState(const QByteArray &state);

	bool selectItemAfterDrawing() const;
	void setSelectItemAfterDrawing(bool enabled);

	qreal toolOpacity(Tools tool) const;
	void setToolOpacity(qreal opacity, Tools tool);

signals:
	void numberUpdateModeChanged(enum NumberUpdateMode numberUpdateMode) const;

private:
	QSharedPointer<ISettings> mSettings;
	QList<Tools> mAllTools;
	Tools mSelectTool;
	QHash<Tools, QColor> mToolToColor;
	QHash<Tools, QColor> mToolToTextColor;
	QHash<Tools, int> mToolToWidth;
	QHash<Tools, FillModes> mToolToFillType;
	QHash<Tools, QFont> mToolToFont;
	QHash<Tools, int> mToolToObfuscationFactor;
	QHash<Tools, bool> mToolToShadowEnabled;
	QHash<Tools, qreal> mToolToOpacity;
	bool mSmoothPathEnabled;
	bool mSaveToolSelection;
	int mSmoothFactor;
	bool mSwitchToSelectToolAfterDrawingItem;
	bool mSelectItemAfterDrawing;
	NumberUpdateMode mNumberUpdateMode;
	QColor mCanvasColor;

	void initToolSettings();
	void initSelectedTool();
	void initToolColors();
	void initToolTextColors();
	void initToolWidths();
	void initToolFillTypes();
	void initToolFonts();
	void initToolOpacity();
	void initObfuscateFactor();
	void initShadowEnabled();
	void initGeneralSettings();

	QColor loadToolColor(Tools toolType);
	void saveToolColor(Tools toolType, const QColor &color);
	QColor loadToolTextColor(Tools toolType);
	void saveToolTextColor(Tools toolType, const QColor &color);
	int loadToolWidth(Tools toolType);
	void saveToolWidth(Tools toolType, int size);
	FillModes loadToolFillType(Tools toolType);
	void saveToolFillType(Tools toolType, FillModes fillType);
	QFont loadToolFont(Tools tool) const;
	void saveToolFont(Tools tool, const QFont &font);
	Tools loadToolType();
	void saveToolType(Tools toolType);
	int loadToolObfuscateFactor(Tools toolType);
	void saveToolObfuscateFactor(Tools toolType, int radius);
	bool loadToolShadowEnabled(Tools tool);
	void saveToolShadowEnabled(Tools tool, bool enabled);
	qreal loadToolOpacity(Tools tool);
	void saveToolOpacity(Tools tool, qreal opacity);

	static QColor defaultToolColor(Tools toolType);
	static QColor defaultToolTextColor(Tools toolType);
	static int defaultToolWidth(Tools toolType);
	static FillModes defaultToolFillMode(Tools toolType);
	static QFont defaultToolFont(Tools tool);
	static Tools defaultToolType();
	static int defaultObfuscateFactor();
	static bool defaultShadowEnabled(Tools tool);
	static qreal defaultToolOpacity();
};

} // namespace kImageAnnotator

#endif // KIMAGEANNOTATOR_CONFIG_H
