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

#ifndef KIMAGEANNOTATOR_KIMAGEANNOTATOR_H
#define KIMAGEANNOTATOR_KIMAGEANNOTATOR_H

#include <QWidget>

#include <kImageAnnotator/KImageAnnotatorExport.h>

namespace kImageAnnotator {

KIMAGEANNOTATOR_EXPORT void loadTranslations();

class KImageAnnotatorPrivate;

class KIMAGEANNOTATOR_EXPORT KImageAnnotator : public QWidget
{
Q_OBJECT

	Q_DECLARE_PRIVATE(KImageAnnotator)

public:
	explicit KImageAnnotator();
	~KImageAnnotator() override;
	QImage image() const;
	QImage imageAt(int index) const;
	QAction *undoAction();
	QAction *redoAction();
	QSize sizeHint() const;
	void showAnnotator();
	void showCropper();
	void showScaler();
	void setSettingsCollapsed(bool isCollapsed);

public Q_SLOTS:
	void loadImage(const QPixmap &pixmap);
	int addTab(const QPixmap &pixmap, const QString &title, const QString &toolTip);
	void updateTabInfo(int index, const QString &title, const QString &toolTip);
	void insertImageItem(const QPointF &position, const QPixmap &pixmap);
	void setTextFont(const QFont &font);
	void setNumberFont(const QFont &font);
	void setItemShadowEnabled(bool enabled);
	void setSmoothPathEnabled(bool enabled);
	void setSaveToolSelection(bool enabled);
	void setSmoothFactor(int factor);
	void setSwitchToSelectToolAfterDrawingItem(bool enabled);
	void setNumberToolSeedChangeUpdatesAllItems(bool enabled);
	void setTabBarAutoHide(bool enabled);
	void removeTab(int index);
	void setStickers(const QStringList &stickerPaths, bool keepDefault);
	void addTabContextMenuActions(const QList<QAction*> & actions);

Q_SIGNALS:
	void imageChanged() const;
	void currentTabChanged(int index) const;
	void tabCloseRequested(int index) const;
	void tabMoved(int fromIndex, int toIndex);
	void tabContextMenuOpened(int index) const;

private:
	QScopedPointer<KImageAnnotatorPrivate> const d_ptr;
};

} // namespace kImageAnnotator

#endif // KIMAGEANNOTATOR_KIMAGEANNOTATOR_H
