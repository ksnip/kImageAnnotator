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

#ifndef KIMAGEANNOTATOR_BOOLPICKER_H
#define KIMAGEANNOTATOR_BOOLPICKER_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>

#include "SettingsPickerWidget.h"
#include "src/widgets/menuButtons/ListMenuToolButton.h"
#include "src/common/helper/IconLoader.h"
#include "src/common/provider/ScaledSizeProvider.h"

namespace kImageAnnotator {

class BoolPicker : public SettingsPickerWidget
{
Q_OBJECT
public:
	explicit BoolPicker(QWidget *parent);
	~BoolPicker() override;
	void setEnabledState(bool enabled);
	bool enabledState() const;
	void setToolTip(const QString &toolTip);
	void setIcon(const QIcon &icon);

signals:
	void enabledStateChanged(bool enabled) const;

protected:
	QWidget* expandingWidget() override;

private:
	QHBoxLayout *mLayout;
	QLabel *mLabel;
	ListMenuToolButton *mToolButton;

	void initGui();
	void insertItem(bool enabled, const QString &iconName, const QString &text);

private slots:
	void selectionChanged();
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_BOOLPICKER_H
