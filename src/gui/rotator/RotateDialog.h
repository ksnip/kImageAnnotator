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

#ifndef KIMAGEANNOTATOR_ROTATEDIALOG_H
#define KIMAGEANNOTATOR_ROTATEDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGridLayout>
#include <QRadioButton>

#include "src/widgets/CustomSpinBox.h"

namespace kImageAnnotator {

class RotateDialog : public QDialog
{
Q_OBJECT
public:
	explicit RotateDialog(QWidget *parent = nullptr);
	~RotateDialog() override;

signals:
	void finished(qreal angle) const;

private:
	QRadioButton *m180RadioButton;
	QRadioButton *m90ClockwiseRadioButton;
	QRadioButton *m90CounterClockwiseRadioButton;
	QRadioButton *mArbitraryRotationRadioButton;
	CustomSpinBox *mArbitraryRotationSpinBox;
	QPushButton *mOkButton;
	QPushButton *mCancelButton;
	QGridLayout *mRadioButtonLayout;
	QHBoxLayout *mButtonRowLayout;
	QVBoxLayout *mMainLayout;

	void initGui();
	void setDefault();

private slots:
	void rotate();
	void cancel();
	void selectionChanged();
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_ROTATEDIALOG_H
