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

#ifndef KIMAGEANNOTATOR_CONFIG_H
#define KIMAGEANNOTATOR_CONFIG_H

#include <QObject>
#include <QPointF>
#include <QColor>
#include <QHash>
#include <QFont>
#include <QSettings>

#include "src/common/enum/ToolTypes.h"
#include "src/common/enum/FillTypes.h"
#include "src/common/helper/ConfigNameHelper.h"

namespace kImageAnnotator {

class Config : public QObject
{
Q_OBJECT

public slots:
	static Config *instance();

	ToolTypes selectedTool() const;
	void setSelectedTool(ToolTypes tool);

	QColor toolColor(ToolTypes tool) const;
	void setToolColor(const QColor &color, ToolTypes tool);

	QColor toolTextColor(ToolTypes tool) const;
	void setToolTextColor(const QColor &color, ToolTypes tool);

	int toolSize(ToolTypes tool) const;
	void setToolSize(int size, ToolTypes tool);

	FillTypes toolFillType(ToolTypes tool) const;
	void setToolFillType(FillTypes fillType, ToolTypes tool);

	QFont textFont() const;
	void setTextFont(const QFont &font);

	QFont numberFont() const;
	void setNumberFont(const QFont &font);

	bool itemShadowEnabled() const;
	void setItemShadowEnabled(bool enabled);

	bool smoothPathEnabled() const;
	void setSmoothPathEnabled(bool enabled);

	void setSaveToolSelection(bool enabled);

	int smoothFactor() const;
	void setSmoothFactor(int factor);

signals:
	void toolChanged(ToolTypes tool) const;

private:
	QSettings mConfig;
	QList<ToolTypes> mAllTools;
	ToolTypes mSelectTool;
	QHash<ToolTypes, QColor> mToolToColor;
	QHash<ToolTypes, QColor> mToolToTextColor;
	QHash<ToolTypes, int> mToolToSize;
	QHash<ToolTypes, FillTypes> mToolToFillType;
	QFont mTextFont;
	QFont mNumberFont;
	bool mItemShadowEnabled;
	bool mSmoothPathEnabled;
	bool mSaveToolSelection;
	int mSmoothFactor;

	explicit Config();
	void initSelectedTool();
	void initToolColors();
	void initToolTextColors();
	void initToolSizes();
	void initToolFillTypes();
	void initFonts();
	void initGeneralSettings();

	QColor loadToolColor(ToolTypes toolType);
	void saveToolColor(ToolTypes toolType, const QColor &color);
	QColor loadToolTextColor(ToolTypes toolType);
	void saveToolTextColor(ToolTypes toolType, const QColor &color);
	int loadToolSize(ToolTypes toolType);
	void saveToolSize(ToolTypes toolType, int size);
	FillTypes loadToolFillType(ToolTypes toolType);
	void saveToolFillType(ToolTypes toolType, FillTypes fillType);
	ToolTypes loadToolType();
	void saveToolType(ToolTypes toolType);
	QColor defaultToolColor(ToolTypes toolType) const;
	QColor defaultToolTextColor(ToolTypes toolType) const;
	int defaultToolSize(ToolTypes toolType) const;
	FillTypes defaultToolFillType(ToolTypes toolType) const;
	ToolTypes defaultToolType();
};

} // namespace kImageAnnotator

#endif // KIMAGEANNOTATOR_CONFIG_H
