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

#include <QCoreApplication>
#include <QGraphicsView>
#include <QHBoxLayout>

#include "src/gui/VisibilitySwitcher.h"
#include "src/annotations/core/AnnotationArea.h"
#include "src/widgets/ToolPicker.h"
#include "src/widgets/ColorPicker.h"
#include "src/widgets/SizePicker.h"
#include "src/widgets/FillPicker.h"

#include <kImageAnnotator/KImageAnnotator.h>

// Impl Definition
class KImageAnnotator::Impl : public QSharedData
{
public:
    explicit Impl(const QPixmap &image);
    ~Impl();

public:
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

    void initAppSettings();
    void initGui();
    void setupDefaults();
    void updateSelection(ToolTypes tool);
};

// KImageAnnotator Implementation
KImageAnnotator::KImageAnnotator(const QPixmap &image) : mImpl(new Impl(image))
{
    setLayout(mImpl->mMainLayout);
    setFocusPolicy(Qt::ClickFocus);

    connect(mImpl->mToolPicker, &ToolPicker::toolSelected, mImpl->mConfig, &Config::setSelectedTool);
    connect(mImpl->mToolPicker, &ToolPicker::toolSelected, [this](ToolTypes tool)
    {
        mImpl->updateSelection(tool);
    });
    connect(mImpl->mColorPicker, &ColorPicker::colorSelected, [this](const QColor &color)
    {
        mImpl->mConfig->setToolColor(color, mImpl->mToolPicker->tool());
    });
    connect(mImpl->mTextColorPicker, &ColorPicker::colorSelected, [this](const QColor &color)
    {
        mImpl->mConfig->setToolForegroundColor(color, mImpl->mToolPicker->tool());
    });
    connect(mImpl->mSizePicker, &SizePicker::sizeSelected, [this](int size)
    {
        mImpl->mConfig->setToolSize(size, mImpl->mToolPicker->tool());
    });
    connect(mImpl->mFillPicker, &FillPicker::fillSelected, [this](FillTypes fill)
    {
        mImpl->mConfig->setToolFillType(fill, mImpl->mToolPicker->tool());
    });
}

KImageAnnotator::~KImageAnnotator()
{
}

// Impl Implementation
KImageAnnotator::Impl::Impl(const QPixmap &image)
{
    initAppSettings();
    initGui();
    setupDefaults();

    mAnnotationArea->setBackgroundImage(image);
    mView->setFixedSize(image.size() + QSize(50, 50));
}

KImageAnnotator::Impl::~Impl()
{
    delete mAnnotationArea;
    delete mView;
    delete mMainLayout;
    delete mToolsLayout;
    delete mToolPicker;
    delete mColorPicker;
    delete mTextColorPicker;
    delete mSizePicker;
    delete mFillPicker;
}

void KImageAnnotator::Impl::initAppSettings()
{
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, true);
}

void KImageAnnotator::Impl::initGui()
{
    mAnnotationArea = new AnnotationArea();
    mView = new QGraphicsView(mAnnotationArea);
    mMainLayout = new QHBoxLayout();
    mToolsLayout = new QVBoxLayout();
    mToolPicker = new ToolPicker();
    mColorPicker = new ColorPicker(QIcon::fromTheme(QStringLiteral("tool_color_picker")), tr("Color"));
    mTextColorPicker = new ColorPicker(QIcon::fromTheme(QStringLiteral("format-text-color")), tr("Text Color"));
    mSizePicker = new SizePicker(QIcon::fromTheme(QStringLiteral("newline")), tr("Size"));
    mFillPicker = new FillPicker(QIcon::fromTheme(QStringLiteral("fill-color")), tr("Fill Type"));

    mToolsLayout->addWidget(mToolPicker);
    mToolsLayout->addSpacing(20);
    mToolsLayout->addWidget(mColorPicker);
    mToolsLayout->addWidget(mTextColorPicker);
    mToolsLayout->addWidget(mSizePicker);
    mToolsLayout->addWidget(mFillPicker);
    mToolsLayout->setAlignment(Qt::AlignTop | Qt::AlignCenter);

    mMainLayout->addLayout(mToolsLayout);
    mMainLayout->addWidget(mView);

    mVisibilitySwitcher.setOutlineColorWidget(mColorPicker);
    mVisibilitySwitcher.setForegroundColorWidget(mTextColorPicker);
    mVisibilitySwitcher.setSizeWidget(mSizePicker);
    mVisibilitySwitcher.setFillWidget(mFillPicker);

    mConfig = Config::instance();
}

void KImageAnnotator::Impl::setupDefaults()
{
    mToolPicker->setTool(mConfig->selectedTool());
}

void KImageAnnotator::Impl::updateSelection(ToolTypes tool)
{
    mColorPicker->setColor(mConfig->toolColor(tool));
    mTextColorPicker->setColor(mConfig->toolTextColor(tool));
    mSizePicker->setSize(mConfig->toolSize(tool));
    mFillPicker->setFill(mConfig->toolFillType(tool));

    mVisibilitySwitcher.setCurrentTool(tool);
}
