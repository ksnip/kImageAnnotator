/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef KIMAGEANNOTATOR_IMAGEEFFECTPICKER_H
#define KIMAGEANNOTATOR_IMAGEEFFECTPICKER_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QToolButton>
#include <QMenu>
#include <QAction>

#include "SettingsPickerWidget.h"
#include "src/widgets/menuButtons/ListMenuToolButton.h"
#include "src/common/provider/ScaledSizeProvider.h"
#include "src/common/enum/ImageEffects.h"
#include "src/common/helper/IconLoader.h"

namespace kImageAnnotator {

class ImageEffectPicker : public SettingsPickerWidget
{
	Q_OBJECT
public:
	explicit ImageEffectPicker(QWidget *parent);
	~ImageEffectPicker() override;
	void setEffect(ImageEffects effect);
	ImageEffects effect() const;

signals:
	void effectSelected(ImageEffects effect) const;

protected:
	QWidget* expandingWidget() override;

private:
	QHBoxLayout *mLayout;
	QLabel *mLabel;
	ListMenuToolButton *mToolButton;

	void initGui();

private slots:
	void insertItem(ImageEffects effects, const QString &iconName, const QString &text);
	void selectionChanged();
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_IMAGEEFFECTPICKER_H
