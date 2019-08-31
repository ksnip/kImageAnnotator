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

#include "CoreView.h"

inline void initResource()
{
	Q_INIT_RESOURCE(kImageAnnotator_icons);
}

namespace kImageAnnotator {

class KImageAnnotatorPrivate
{
	Q_DISABLE_COPY(KImageAnnotatorPrivate)

	Q_DECLARE_PUBLIC(KImageAnnotator)

	explicit KImageAnnotatorPrivate(KImageAnnotator *kImageAnnotator);

	KImageAnnotator *const q_ptr;
	Config mConfig;
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

QAction *KImageAnnotator::undoAction()
{
	Q_D(KImageAnnotator);
	return d->mCoreView.undoAction();
}

QAction *KImageAnnotator::redoAction()
{
	Q_D(KImageAnnotator);
	return d->mCoreView.redoAction();
}

void KImageAnnotator::loadImage(const QPixmap &pixmap)
{
	Q_D(KImageAnnotator);
	d->mCoreView.loadImage(pixmap);

	if (isHidden()) {
		show();
	}
}

void KImageAnnotator::insertImageItem(const QPointF &position, const QPixmap &pixmap)
{
    Q_D(KImageAnnotator);
    d->mCoreView.insertImageItem(position, pixmap);
}

QSize KImageAnnotator::sizeHint() const
{
	Q_D(const KImageAnnotator);
	if (isVisible()) {
		return d->mCoreView.sizeHint();
	} else {
		return { 0, 0 };
	}
}

void KImageAnnotator::setTextFont(const QFont &font)
{
	Q_D(KImageAnnotator);
	d->mConfig.setToolFont(font, ToolTypes::Text);
}

void KImageAnnotator::setNumberFont(const QFont &font)
{
	Q_D(KImageAnnotator);
	d->mConfig.setToolFont(font, ToolTypes::Number);
}

void KImageAnnotator::setItemShadowEnabled(bool enabled)
{
	Q_D(KImageAnnotator);
	d->mConfig.setItemShadowEnabled(enabled);
}

void KImageAnnotator::setSmoothPathEnabled(bool enabled)
{
	Q_D(KImageAnnotator);
	d->mConfig.setSmoothPathEnabled(enabled);
}

void KImageAnnotator::setSaveToolSelection(bool enabled)
{
	Q_D(KImageAnnotator);
	d->mConfig.setSaveToolSelection(enabled);
}

void KImageAnnotator::setSmoothFactor(int factor)
{
	Q_D(KImageAnnotator);
	d->mConfig.setSmoothFactor(factor);
}

void KImageAnnotator::showAnnotator()
{
	Q_D(KImageAnnotator);
	d->mCoreView.showAnnotator();
}

void KImageAnnotator::showCropper()
{
	Q_D(KImageAnnotator);
	d->mCoreView.showCropper();
}

void KImageAnnotator::showScaler()
{
	Q_D(KImageAnnotator);
	d->mCoreView.showScaler();
}

// KImageAnnotatorPrivate

KImageAnnotatorPrivate::KImageAnnotatorPrivate(KImageAnnotator *kImageAnnotator) : q_ptr(kImageAnnotator), mCoreView(&mConfig)
{
	initResource();

	QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, true);

	mMainLayout.addWidget(&mCoreView);
	kImageAnnotator->setLayout(&mMainLayout);
	kImageAnnotator->hide();

	kImageAnnotator->connect(&mCoreView, &CoreView::imageChanged, kImageAnnotator, &KImageAnnotator::imageChanged);
}

} // namespace kImageAnnotator
