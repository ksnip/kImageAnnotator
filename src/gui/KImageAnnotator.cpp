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

namespace kImageAnnotator {

class KImageAnnotatorPrivate
{
	Q_DISABLE_COPY(KImageAnnotatorPrivate)

	Q_DECLARE_PUBLIC(KImageAnnotator)

	explicit KImageAnnotatorPrivate(KImageAnnotator *kImageAnnotator);

	KImageAnnotator *const q_ptr;
	CoreView mCoreView;
	QHBoxLayout mMainLayout;
};

KImageAnnotator::KImageAnnotator() : d_ptr(new KImageAnnotatorPrivate(this))
{}

KImageAnnotator::~KImageAnnotator()
{}

QImage KImageAnnotator::image() const
{
	Q_D(const KImageAnnotator);
	return d->mCoreView.image();
}

void KImageAnnotator::loadImage(const QPixmap &pixmap)
{
	Q_D(KImageAnnotator);
	d->mCoreView.loadImage(pixmap);
}

// KImageAnnotatorPrivate

KImageAnnotatorPrivate::KImageAnnotatorPrivate(KImageAnnotator *kImageAnnotator) : q_ptr(kImageAnnotator)
{
	QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, true);

	mMainLayout.addWidget(&mCoreView);
	kImageAnnotator->setLayout(&mMainLayout);

	kImageAnnotator->connect(&mCoreView, &CoreView::imageChanged, kImageAnnotator, &KImageAnnotator::imageChanged);
}

} // namespace kImageAnnotator
