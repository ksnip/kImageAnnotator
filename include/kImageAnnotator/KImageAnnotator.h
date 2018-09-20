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

class KImageAnnotatorPrivate;

class KIMAGEANNOTATOR_EXPORT KImageAnnotator : public QWidget
{
Q_OBJECT

	Q_DECLARE_PRIVATE(KImageAnnotator)

public:
	explicit KImageAnnotator();
	~KImageAnnotator();
	QImage image() const;
	QAction *undoAction();
	QAction *redoAction();
	QSize sizeHint() const;
	void showAnnotator();
	void showCropper();
	void showScaler();

public slots:
	void loadImage(const QPixmap &pixmap);
	void setTextFont(const QFont &font);
	void setNumberFont(const QFont &font);
	void setItemShadowEnabled(bool enabled);
	void setSmoothPathEnabled(bool enabled);
	void setSaveToolSelection(bool enabled);
	void setSmoothFactor(int factor);

signals:
	void imageChanged() const;

private:
	QScopedPointer<KImageAnnotatorPrivate> const d_ptr;
};

} // namespace kImageAnnotator

#endif // KIMAGEANNOTATOR_KIMAGEANNOTATOR_H
