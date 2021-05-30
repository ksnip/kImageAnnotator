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

#ifndef KIMAGEANNOTATOR_SCALEDIALOG_H
#define KIMAGEANNOTATOR_SCALEDIALOG_H

#include <QDialog>
#include <QCheckBox>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QtWidgets/QSpinBox>

#include "ScaleSizeHandler.h"
#include "src/widgets/CustomSpinBox.h"

namespace kImageAnnotator {

class ScaleDialog : public QDialog
{
Q_OBJECT
public:
	explicit ScaleDialog(const QSize &imageSize, QWidget *parent = nullptr);
	~ScaleDialog() override = default;

signals:
	void finished(const QSize &newSize) const;

private:
	ScaleSizeHandler mSizeHandler;
	QCheckBox *mKeepAspectRatioCheckBox;
	QLabel *mWidthPixelLabel;
	QLabel *mHeightPixelLabel;
	QLabel *mWidthPercentLabel;
	QLabel *mHeightPercentLabel;
	CustomSpinBox *mWidthPixelSpinBox;
	CustomSpinBox *mHeightPixelSpinBox;
	CustomSpinBox *mWidthPercentSpinBox;
	CustomSpinBox *mHeightPercentSpinBox;
	QPushButton *mOkButton;
	QPushButton *mCancelButton;
	QGridLayout *mPixelGridLayout;
	QGridLayout *mPercentGridLayout;
	QGroupBox *mPixelGroupBox;
	QGroupBox *mPercentGroupBox;
	QHBoxLayout *mButtonRowLayout;
	QVBoxLayout *mMainLayout;

	void initGui();

private slots:
	void scale();
	void cancel();
};

} // namespace kImageAnnotator

#endif // KIMAGEANNOTATOR_SCALEDIALOG_H
