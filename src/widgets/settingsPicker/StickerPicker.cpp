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

#include "StickerPicker.h"

namespace kImageAnnotator {

StickerPicker::StickerPicker(QWidget *parent) :
	SettingsPickerWidget(parent),
	mLayout(new QHBoxLayout(this)),
	mLabel(new QLabel(this)),
	mToolButton(new GridMenuToolButton(this))
{
	init();
}

void StickerPicker::setSticker(const QString &name)
{
	mToolButton->setCurrentData(name);
}

QString StickerPicker::sticker() const
{
	return mToolButton->currentData().toString();
}

void StickerPicker::setStickers(const QStringList &stickerPaths, bool keepDefault)
{
	mToolButton->clear();

	if(keepDefault) {
		addDefaultStickers();
	}

	for(const auto& stickerPath : stickerPaths) {
		addItem(stickerPath);
	}
}

QWidget *StickerPicker::expandingWidget()
{
	return mToolButton;
}

void StickerPicker::init()
{
	mLayout->setContentsMargins(0, 0, 0, 0);

	auto icon = IconLoader::load(QLatin1String("sticker.svg"));
	mLabel->setPixmap(icon.pixmap(ScaledSizeProvider::settingsWidgetIconSize()));
	mLabel->setToolTip(tr("Sticker"));
	mLabel->setMargin(0);

	mToolButton->setFocusPolicy(Qt::NoFocus);
	mToolButton->setPopupMode(QToolButton::InstantPopup);

	connect(mToolButton, &GridMenuToolButton::selectionChanged, this, &StickerPicker::selectionChanged);

	addDefaultStickers();

	mLayout->addWidget(mLabel);
	mLayout->addWidget(mToolButton);
	mLayout->setAlignment(Qt::AlignLeft);

	setLayout(mLayout);
}

void StickerPicker::addDefaultStickers()
{
	QStringList defaultStickers{ QLatin1String("face_blowing_a_kiss"),
								 QLatin1String("face_savoring_food"),
								 QLatin1String("grinning_face_with_big_eyes"),
								 QLatin1String("grinning_face_with_smiling_eyes"),
								 QLatin1String("grinning_face_with_sweat"),
								 QLatin1String("grinning_squinting_face"),
								 QLatin1String("hushed_face"),
								 QLatin1String("nerd_face"),
								 QLatin1String("neutral_face"),
								 QLatin1String("smiling_face_with_heart_eyes"),
								 QLatin1String("smiling_face_with_hearts"),
								 QLatin1String("confused_face"),
								 QLatin1String("face_with_symbols_on_mouth"),
								 QLatin1String("pouting_face"),
								 QLatin1String("smiling_face_with_sunglasses"),
								 QLatin1String("check_mark"),
								 QLatin1String("cross_mark"),
								 QLatin1String("cursor")
	};

	for(const auto& sticker : defaultStickers) {
		addItem(getResourcePath(sticker));
	}
}

QString StickerPicker::getResourcePath(const QString &name)
{
	return QLatin1String(":/stickers/") + name + QLatin1String(".svg");
}

void StickerPicker::addItem(const QString &path)
{
	auto icon = QIcon(path);
	auto filename = PathHelper::extractFilename(path);
	filename = PathHelper::prettyFilename(filename);
	mToolButton->addItem(icon, filename, path);
}

void StickerPicker::selectionChanged() const
{
	emit stickerSelected(sticker());
}

} // namespace kImageAnnotator
