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

#ifndef KIMAGEANNOTATOR_FILLMODEPICKER_H
#define KIMAGEANNOTATOR_FILLMODEPICKER_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QToolButton>
#include <QMenu>
#include <QAction>

#include "src/widgets/menuButtons/ListMenuToolButton.h"
#include "src/common/enum/FillModes.h"
#include "src/common/helper/IconLoader.h"
#include "src/common/provider/ScaledSizeProvider.h"

namespace kImageAnnotator {

class FillModePicker : public QWidget
{
	Q_OBJECT
public:
	explicit FillModePicker(QWidget *parent);
	~FillModePicker() override;
	void setFillType(FillModes fillType);
	void addNoFillAndNoBorderToList();
	void removeNoFillAndNoBorderToList();
	FillModes fillType() const;

signals:
	void fillSelected(FillModes fillType) const;

private:
	QHBoxLayout *mLayout;
	QLabel *mLabel;
	ListMenuToolButton *mToolButton;

	void initGui();

private slots:
	void insertItem(FillModes fillType, const QString &iconName, const QString &text);
	void selectionChanged();
};

} // namespace kImageAnnotator

#endif // KIMAGEANNOTATOR_FILLMODEPICKER_H
