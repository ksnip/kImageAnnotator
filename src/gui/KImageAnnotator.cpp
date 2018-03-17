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

KImageAnnotator::KImageAnnotator(const QPixmap& image)
{
    initAppSettings();
    initGui();
    setupDefaults();

    mAnnotationArea->setBackgroundImage(image);
}

KImageAnnotator::~KImageAnnotator()
{
    delete mAnnotationArea;
    delete mView;
    delete mMainLayout;
    delete mToolsLayout;
    delete mPropertiesLayout;
    delete mToolPicker;
    delete mOutlineColorPicker;
    delete mForegroundColorPicker;
    delete mSizePicker;
    delete mFillPicker;
}

void KImageAnnotator::initAppSettings()
{
    QCoreApplication::setOrganizationName(QStringLiteral("kimageannotator"));
    QCoreApplication::setOrganizationDomain(QStringLiteral("kimageannotator.kde.org"));
    QCoreApplication::setApplicationName(QStringLiteral("kimageAnnotator"));
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, true);
}

void KImageAnnotator::initGui()
{

    mAnnotationArea = new AnnotationArea();
    mView = new QGraphicsView(mAnnotationArea);
    mMainLayout = new QHBoxLayout();
    mToolsLayout = new QVBoxLayout();
    mPropertiesLayout = new QVBoxLayout();
    mToolPicker = new ToolPicker();
    mOutlineColorPicker = new ColorPicker(QIcon::fromTheme(QStringLiteral("color-fill")));
    mForegroundColorPicker = new ColorPicker(QIcon::fromTheme(QStringLiteral("format-text-color")));
    mSizePicker = new SizePicker(QIcon::fromTheme(QStringLiteral("newline")));
    mFillPicker = new FillPicker(tr("Fill"), 70);

    mToolsLayout->addWidget(mToolPicker);
    mToolsLayout->addWidget(mOutlineColorPicker);
    mToolsLayout->addWidget(mForegroundColorPicker);
    mToolsLayout->addWidget(mSizePicker);
    mToolsLayout->setAlignment(Qt::AlignTop | Qt::AlignCenter);

    mPropertiesLayout->addWidget(mSizePicker);
    mPropertiesLayout->addWidget(mFillPicker);
    mPropertiesLayout->setAlignment(Qt::AlignTop);

    mMainLayout->addLayout(mToolsLayout);
    mMainLayout->addWidget(mView);
//     mMainLayout->addLayout(mPropertiesLayout);
    setLayout(mMainLayout);

    mVisibilitySwitcher.setOutlineColorWidget(mOutlineColorPicker);
    mVisibilitySwitcher.setForegroundColorWidget(mForegroundColorPicker);
    mVisibilitySwitcher.setSizeWidget(mSizePicker);
    mVisibilitySwitcher.setFillWidget(mFillPicker);

    mConfig = Config::instance();

    connect(mToolPicker, &ToolPicker::toolSelected, mConfig, &Config::setSelectedTool);
    connect(mToolPicker, &ToolPicker::toolSelected, this, &KImageAnnotator::updateSelection);
    connect(mOutlineColorPicker, &ColorPicker::colorSelected, [this](const QColor & color) {
        mConfig->setToolOutlineColor(color, mToolPicker->tool());
    });
    connect(mForegroundColorPicker, &ColorPicker::colorSelected, [this](const QColor & color) {
        mConfig->setToolForegroundColor(color, mToolPicker->tool());
    });
    connect(mSizePicker, &SizePicker::sizeSelected, [this](int size) {
        mConfig->setToolSize(size, mToolPicker->tool());
    });
    connect(mFillPicker, &FillPicker::fillSelected, [this](FillTypes fill) {
        mConfig->setToolFillType(fill, mToolPicker->tool());
    });
}

void KImageAnnotator::setupDefaults()
{
    mToolPicker->setTool(mConfig->selectedTool());
}

void KImageAnnotator::updateSelection(ToolTypes tool)
{
    mOutlineColorPicker->setColor(mConfig->toolOutlineColor(tool));
    mForegroundColorPicker->setColor(mConfig->toolForegroundColor(tool));
    mSizePicker->setSize(mConfig->toolSize(tool));
    mFillPicker->setFill(mConfig->toolFillType(tool));

    mVisibilitySwitcher.setCurrentTool(tool);
}
