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

#include <QCoreApplication>
#include <QTranslator>
#include <QHBoxLayout>

#include <kImageAnnotator/KImageAnnotator.h>

#include "CoreView.h"

inline void initResource()
{
	Q_INIT_RESOURCE(kImageAnnotator_resources);
}

namespace kImageAnnotator {

void loadTranslations()
{
	static QTranslator *existingTranslator = nullptr;
	auto translator = new QTranslator(QCoreApplication::instance());
	auto translationsLoaded = translator->load(QLocale(),
											   QLatin1String("kImageAnnotator"),
											   QLatin1String("_"),
											   QLatin1String(KIMAGEANNOTATOR_LANG_INSTALL_DIR));
	if (translationsLoaded) {
		if (existingTranslator != nullptr) {
			QCoreApplication::removeTranslator(existingTranslator);
			delete existingTranslator;
		}
		QCoreApplication::installTranslator(translator);
		existingTranslator = translator;
	}
}

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

QImage KImageAnnotator::imageAt(int index) const
{
	Q_D(const KImageAnnotator);
	return d->mCoreView.imageAt(index);
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

int KImageAnnotator::addTab(const QPixmap &pixmap, const QString &title, const QString &toolTip)
{
	Q_D(KImageAnnotator);
	auto newTabIndex = d->mCoreView.addTab(pixmap, title, toolTip);

	if (isHidden()) {
		show();
	}

	return newTabIndex;
}

void KImageAnnotator::updateTabInfo(int index, const QString &title, const QString &toolTip)
{
	Q_D(KImageAnnotator);
	d->mCoreView.updateTabInfo(index, title, toolTip);
}

void KImageAnnotator::insertImageItem(const QPointF &position, const QPixmap &pixmap)
{
    Q_D(KImageAnnotator);
    d->mCoreView.insertImageItem(position, pixmap);
}

QSize KImageAnnotator::sizeHint() const
{
	Q_D(const KImageAnnotator);
	return d->mCoreView.sizeHint();
}

void KImageAnnotator::setTextFont(const QFont &font)
{
	Q_UNUSED(font)
	// Deprecated, will be removed with the next major release
}

void KImageAnnotator::setNumberFont(const QFont &font)
{
	Q_UNUSED(font)
	// Deprecated, will be removed with the next major release
}

void KImageAnnotator::setItemShadowEnabled(bool enabled)
{
	Q_UNUSED(enabled)
	// Deprecated, will be removed with the next major release
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
	d->mCoreView.reloadConfig();
}

void KImageAnnotator::setSmoothFactor(int factor)
{
	Q_D(KImageAnnotator);
	d->mConfig.setSmoothFactor(factor);
}

void KImageAnnotator::setSwitchToSelectToolAfterDrawingItem(bool enabled)
{
	Q_D(KImageAnnotator);
	d->mConfig.setSwitchToSelectToolAfterDrawingItem(enabled);
}

void KImageAnnotator::setNumberToolSeedChangeUpdatesAllItems(bool enabled)
{
	Q_D(KImageAnnotator);
	auto mode = enabled ? NumberUpdateMode::UpdateAllNumbers : NumberUpdateMode::UpdateOnlyNewNumbers;
	d->mConfig.setNumberToolUpdateMode(mode);
}

void KImageAnnotator::setTabBarAutoHide(bool enabled)
{
	Q_D(KImageAnnotator);
	d->mCoreView.setTabBarAutoHide(enabled);
}

void KImageAnnotator::removeTab(int index)
{
	Q_D(KImageAnnotator);
	d->mCoreView.removeTab(index);
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

void KImageAnnotator::showRotator()
{
	Q_D(KImageAnnotator);
	d->mCoreView.showRotator();
}

void KImageAnnotator::showCanvasModifier()
{
	Q_D(KImageAnnotator);
	d->mCoreView.showCanvasModifier();
}

void KImageAnnotator::showCutter()
{
	Q_D(KImageAnnotator);
	d->mCoreView.showCutter();
}

void KImageAnnotator::setSettingsCollapsed(bool isCollapsed)
{
	Q_D(KImageAnnotator);
	d->mCoreView.setSettingsCollapsed(isCollapsed);
}

void KImageAnnotator::setStickers(const QStringList &stickerPaths, bool keepDefault)
{
	Q_D(KImageAnnotator);
	d->mCoreView.setStickers(stickerPaths, keepDefault);
}

void KImageAnnotator::addTabContextMenuActions(const QList<QAction *> &actions)
{
	Q_D(KImageAnnotator);
	d->mCoreView.addTabContextMenuActions(actions);
}

void KImageAnnotator::setCanvasColor(const QColor &color)
{
	Q_D(KImageAnnotator);
	d->mConfig.setCanvasColor(color);
}

void KImageAnnotator::setSelectItemAfterDrawing(bool enabled)
{
	Q_D(KImageAnnotator);
	d->mConfig.setSelectItemAfterDrawing(enabled);
}

// KImageAnnotatorPrivate

KImageAnnotatorPrivate::KImageAnnotatorPrivate(KImageAnnotator *kImageAnnotator) : q_ptr(kImageAnnotator), mCoreView(&mConfig)
{
	initResource();

	mMainLayout.addWidget(&mCoreView);
	kImageAnnotator->setLayout(&mMainLayout);
	kImageAnnotator->hide();

	kImageAnnotator->connect(&mCoreView, &CoreView::imageChanged, kImageAnnotator, &KImageAnnotator::imageChanged);
	kImageAnnotator->connect(&mCoreView, &CoreView::currentTabChanged, kImageAnnotator, &KImageAnnotator::currentTabChanged);
	kImageAnnotator->connect(&mCoreView, &CoreView::tabCloseRequested, kImageAnnotator, &KImageAnnotator::tabCloseRequested);
	kImageAnnotator->connect(&mCoreView, &CoreView::tabMoved, kImageAnnotator, &KImageAnnotator::tabMoved);
	kImageAnnotator->connect(&mCoreView, &CoreView::tabContextMenuOpened, kImageAnnotator, &KImageAnnotator::tabContextMenuOpened);
}

} // namespace kImageAnnotator
