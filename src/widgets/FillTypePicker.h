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

#ifndef KIMAGEANNOTATOR_FILLPICKER_H
#define KIMAGEANNOTATOR_FILLPICKER_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QToolButton>
#include <QMenu>
#include <QAction>

#include "src/common/constants/Constants.h"
#include "src/common/enum/FillTypes.h"
#include "src/common/helper/IconLoader.h"
#include "src/common/provider/ScaledSizeProvider.h"

namespace kImageAnnotator {

class FillTypePicker : public QWidget
{
Q_OBJECT
public:
	FillTypePicker(const QIcon &icon, const QString &tooltip);
	~FillTypePicker() override;
	void setFillType(FillTypes fillType);
	void addNoFillAndNoBorderToList();
	void removeNoFillAndNoBorderToList();
	FillTypes fillType() const;

signals:
	void fillSelected(FillTypes fillType) const;

private:
	QHBoxLayout *mLayout;
	QLabel *mLabel;
	QToolButton *mToolButton;
	QMenu *mMenu;
	QHash<QAction*, FillTypes> mActionToFillType;

	void initGui(const QIcon &icon, const QString &tooltip);
	void setFillAndNotify(FillTypes fill);

private slots:
	void selectionChanged();
	void insertItem(FillTypes fillType, const QString &iconName, const QString &text);
};

} // namespace kImageAnnotator

#endif // KIMAGEANNOTATOR_FILLPICKER_H
