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

#ifndef KIMAGEANNOTATOR_ANNOTATIONVIEW_H
#define KIMAGEANNOTATOR_ANNOTATIONVIEW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QGraphicsView>

#include "src/gui/VisibilitySwitcher.h"
#include "src/annotations/core/AnnotationArea.h"
#include "src/widgets/ToolPicker.h"
#include "src/widgets/ColorPicker.h"
#include "src/widgets/SizePicker.h"
#include "src/widgets/FillPicker.h"

namespace kImageAnnotator {

class AnnotationView : public QWidget
{
Q_OBJECT
public:
    explicit AnnotationView(AnnotationArea *annotationArea);
    virtual ~AnnotationView();

signals:
    void imageChanged() const;

private:
    AnnotationArea *mAnnotationArea;
    QGraphicsView *mView;
    QHBoxLayout *mMainLayout;
    QVBoxLayout *mToolsLayout;
    ToolPicker *mToolPicker;
    ColorPicker *mColorPicker;
    ColorPicker *mTextColorPicker;
    SizePicker *mSizePicker;
    FillPicker *mFillPicker;
    Config *mConfig;
    VisibilitySwitcher mVisibilitySwitcher;

    void initGui();
    void setupDefaults();
    void updateSelection(ToolTypes tool);

private slots:
    void setToolColor(const QColor &color);
    void setToolTextColor(const QColor &color);
    void setToolSize(int size);
    void setToolFillType(FillTypes fill);
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_ANNOTATIONVIEW_H
