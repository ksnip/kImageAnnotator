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
#include <QGraphicsView>
#include <QVBoxLayout>

#include "AnnotationArea.h"
#include "widgets/ToolPicker.h"
#include "widgets/ColorPicker.h"

class KImageAnnotator : public QWidget
{
    Q_OBJECT
public:
    KImageAnnotator(const QPixmap& image);
    ~KImageAnnotator();

private:
    AnnotationArea*        mAnnotationArea;
    QGraphicsView*         mView;
    QHBoxLayout*           mMainLayout;
    QVBoxLayout*           mSidebarLayout;
    ToolPicker*            mToolPicker;
    ColorPicker*           mColorPicker;
};

#endif // KIMAGEANNOTATOR_H
