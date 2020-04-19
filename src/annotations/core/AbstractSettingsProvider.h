/*
 * Copyright (C) 2019 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KIMAGEANNOTATOR_ABSTRACTSETTINGSPROVIDER_H
#define KIMAGEANNOTATOR_ABSTRACTSETTINGSPROVIDER_H

#include <QColor>
#include <QList>

#include "AbstractToolChangeListener.h"
#include "AbstractItemSettingsChangeListener.h"
#include "AbstractBadgeNumberChangeListener.h"
#include "src/common/enum/FillTypes.h"
#include "src/annotations/items/AbstractAnnotationItem.h"

namespace kImageAnnotator {

class AbstractSettingsProvider
{
public:
	virtual void editItem(AbstractAnnotationItem *item) = 0;
	virtual void activateSelectTool() = 0;
	virtual ToolTypes toolType() const = 0;
	virtual QColor toolColor() const = 0;
	virtual QColor textColor() const = 0;
	virtual int toolWidth() const = 0;
	virtual int fontSize() const = 0;
	virtual FillTypes fillType() const = 0;
	virtual int blurRadius() const = 0;
	void subscribeToToolChange(AbstractToolChangeListener *listener);
	void subscribeToItemSettingsChange(AbstractItemSettingsChangeListener *listener);
	void subscribeToBadgeNumberChange(AbstractBadgeNumberChangeListener *listener);

protected:
	virtual void toolChanged(ToolTypes toolType);
	virtual void firstBadgeNumberChanged(int number);
	virtual void itemSettingChanged();

private:
	QList<AbstractToolChangeListener*> mToolChangeListeners;
	QList<AbstractItemSettingsChangeListener*> mItemSettingsChangeListeners;
	QList<AbstractBadgeNumberChangeListener*> mBadgeNumberChangeListeners;
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_ABSTRACTSETTINGSPROVIDER_H
