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

#ifndef KIMAGEANNOTATOR_EFFECTPICKER_H
#define KIMAGEANNOTATOR_EFFECTPICKER_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QToolButton>
#include <QMenu>
#include <QAction>

#include "src/widgets/menuButtons/ListMenuToolButton.h"
#include "src/common/constants/Constants.h"
#include "src/common/enum/Effects.h"
#include "src/common/helper/IconLoader.h"

namespace kImageAnnotator {

class EffectPicker : public QWidget
{
	Q_OBJECT
public:
	explicit EffectPicker(QWidget *parent);
	~EffectPicker() override;
	void setEffect(Effects effect);
	Effects effect() const;

signals:
	void effectSelected(Effects effect) const;

private:
	QHBoxLayout *mLayout;
	QLabel *mLabel;
	ListMenuToolButton *mToolButton;

	void initGui();

private slots:
	void insertItem(Effects effects, const QString &iconName, const QString &text);
	void selectionChanged();
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_EFFECTPICKER_H
