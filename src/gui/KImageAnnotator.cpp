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
#include <QHBoxLayout>

#include <kImageAnnotator/KImageAnnotator.h>

#include "src/gui/CoreView.h"

// Impl Definition
class KImageAnnotator::Impl : public QSharedData
{
public:
    explicit Impl();
    ~Impl();
    QImage image() const;

public slots:
    void loadImage(const QPixmap& pixmap);

public:
    QHBoxLayout *mMainLayout;
    CoreView *mCoreView;
};

// KImageAnnotator Implementation
KImageAnnotator::KImageAnnotator() : mImpl(new Impl)
{
    setLayout(mImpl->mMainLayout);
}

KImageAnnotator::~KImageAnnotator()
{
}

QImage KImageAnnotator::image() const
{
    return mImpl->image();
}

void KImageAnnotator::loadImage(const QPixmap& pixmap)
{
    mImpl->loadImage(pixmap);
}

// Impl

KImageAnnotator::Impl::Impl()
{
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, true);

    mCoreView = new CoreView();
    mMainLayout = new QHBoxLayout();
    mMainLayout->addWidget(mCoreView);
}

KImageAnnotator::Impl::~Impl()
{
    delete mCoreView;
    delete mMainLayout;
}

QImage KImageAnnotator::Impl::image() const
{
    return mCoreView->image();
}

void KImageAnnotator::Impl::loadImage(const QPixmap &pixmap)
{
    mCoreView->loadImage(pixmap);
}

