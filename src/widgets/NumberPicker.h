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

#ifndef KIMAGEANNOTATOR_NUMBERPICKER_H
#define KIMAGEANNOTATOR_NUMBERPICKER_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QIcon>

#include "CustomSpinBox.h"
#include "src/common/provider/ScaledSizeProvider.h"

namespace kImageAnnotator {

class NumberPicker : public QWidget
{
Q_OBJECT

public:
	explicit NumberPicker(QWidget *parent);
	~NumberPicker() override;
	void setNumber(int number);
	void setRange(int min, int max);
	int number() const;
	void setToolTip(const QString &toolTip);
	void setIcon(const QIcon &icon);

signals:
	void numberSelected(int number) const;

private:
	QHBoxLayout *mLayout;
	CustomSpinBox *mSpinBox;
	QLabel *mLabel;

	void initGui();
	void setNumberAndNotify(int number) const;

private slots:
	void selectionChanged();
};

} // namespace kImageAnnotator

#endif // KIMAGEANNOTATOR_NUMBERPICKER_H
