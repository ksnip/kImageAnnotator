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

#ifndef KIMAGEANNOTATOR_H
#define KIMAGEANNOTATOR_H

#include <QWidget>
#include <QCoreApplication>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "VisibilitySwitcher.h"
#include "../annotations/AnnotationArea.h"
#include "../backend/Config.h"
#include "../widgets/ToolPicker.h"
#include "../widgets/ColorPicker.h"
#include "../widgets/SizePicker.h"
#include "../widgets/FillPicker.h"

class KImageAnnotator : public QWidget
{
    Q_OBJECT
public:
    KImageAnnotator(const QPixmap& image);
    ~KImageAnnotator();

private:
    AnnotationArea* mAnnotationArea;
    QGraphicsView*  mView;
    QHBoxLayout*    mMainLayout;
    QVBoxLayout*    mToolsLayout;
    QVBoxLayout*    mPropertiesLayout;
    ToolPicker*     mToolPicker;
    ColorPicker*    mOutlineColorPicker;
    ColorPicker*    mForegroundColorPicker;
    SizePicker*     mSizePicker;
    FillPicker*     mFillPicker;
    Config*         mConfig;
    VisibilitySwitcher mVisibilitySwitcher;

    void initAppSettings();
    void initGui();
    void setupDefaults();

private slots:
    void updateSelection(ToolTypes tool);
};

#endif // KIMAGEANNOTATOR_H
