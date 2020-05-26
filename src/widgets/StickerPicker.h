/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef KIMAGEANNOTATOR_STICKERPICKER_H
#define KIMAGEANNOTATOR_STICKERPICKER_H

#include <QWidget>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLabel>

#include "src/common/constants/Constants.h"
#include "src/common/helper/IconLoader.h"
#include "src/common/helper/PathHelper.h"
#include "src/common/provider/ScaledSizeProvider.h"

namespace kImageAnnotator {

class StickerPicker : public QWidget
{
Q_OBJECT
public:
	StickerPicker(const QIcon &icon, const QString &tooltip);
	~StickerPicker() override;
	void setSticker(const QString &name);
	QString sticker() const;
	void setStickers(const QStringList &stickerPaths, bool keepDefault);


signals:
	void stickerSelected(const QString &sticker) const;

private:
	QHBoxLayout *mLayout;
	QLabel *mLabel;
	QComboBox *mComboBox;

	void init(const QIcon &icon, const QString &tooltip);
	void addItem(const QString &path);

private slots:
	void selectionChanged();
	QString getResourcePath(const QString &name) const;
	void addDefaultStickers();
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_STICKERPICKER_H
