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

#include "KImageAnnotator.h"

KImageAnnotator::KImageAnnotator(const QPixmap& image) :
    mAnnotationArea(new AnnotationArea),
    mView(new QGraphicsView(mAnnotationArea)),
    mMainLayout(new QGridLayout),
    mToolPicker(new ToolPicker),
    mColorPicker(new ColorPicker)

{
    mAnnotationArea->setBackgroundImage(image);
    mMainLayout->addWidget(mToolPicker, 0, 0, -1, 1);
    mMainLayout->addWidget(mView, 0, 1, 1, -1);
    mMainLayout->addWidget(mColorPicker, 1, 1, -1, 1);
    setLayout(mMainLayout);

    connect(mToolPicker, &ToolPicker::toolSelected, mAnnotationArea, &AnnotationArea::setTool);
    connect(mColorPicker, &ColorPicker::colorSelected, mAnnotationArea, &AnnotationArea::setColor);

    mToolPicker->setTool(ToolTypes::Line);
    mColorPicker->setColor(QColor(QStringLiteral("red")));
}

KImageAnnotator::~KImageAnnotator()
{
    delete mAnnotationArea;
    delete mView;
    delete mMainLayout;
}
