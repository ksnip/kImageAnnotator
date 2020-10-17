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
	QWidget(parent),
	mLayout(new QHBoxLayout(this)),
	mLabel(new QLabel(this)),
	mToolButton(new GridMenuToolButton(this))
{
	init();
}

StickerPicker::~StickerPicker()
{
	delete mLayout;
	delete mLabel;
	delete mToolButton;
}

void StickerPicker::setSticker(const QString &name)
{
	mToolButton->setCurrentData(name);
}

QString StickerPicker::sticker() const
{
	return mToolButton->currentData().toString();
}

void StickerPicker::init()
{
	mLayout->setContentsMargins(0, 0, 0, 0);

	auto icon = IconLoader::load(QLatin1Literal("sticker.svg"));
	mLabel->setPixmap(icon.pixmap(Constants::SettingsWidgetIconSize));
	mLabel->setToolTip(tr("Sticker"));

	mToolButton->setFixedSize(Constants::SettingsWidgetSize);
	mToolButton->setIconSize(Constants::ToolButtonIconSize);
	mToolButton->setFocusPolicy(Qt::NoFocus);
	mToolButton->setPopupMode(QToolButton::InstantPopup);

	connect(mToolButton, &GridMenuToolButton::selectionChanged, this, &StickerPicker::selectionChanged);

	addDefaultStickers();

	mLayout->addWidget(mLabel);
	mLayout->addWidget(mToolButton);

	setLayout(mLayout);
	setFixedSize(sizeHint());
}

void StickerPicker::addDefaultStickers()
{
	QStringList defaultStickers{ QLatin1Literal("face_blowing_a_kiss"),
								 QLatin1Literal("face_savoring_food"),
								 QLatin1Literal("grinning_face_with_big_eyes"),
								 QLatin1Literal("grinning_face_with_smiling_eyes"),
								 QLatin1Literal("grinning_face_with_sweat"),
								 QLatin1Literal("grinning_squinting_face"),
								 QLatin1Literal("hushed_face"),
								 QLatin1Literal("nerd_face"),
								 QLatin1Literal("neutral_face"),
								 QLatin1Literal("smiling_face_with_heart_eyes"),
								 QLatin1Literal("smiling_face_with_hearts"),
								 QLatin1Literal("confused_face"),
								 QLatin1Literal("face_with_symbols_on_mouth"),
								 QLatin1Literal("pouting_face"),
								 QLatin1Literal("smiling_face_with_sunglasses"),
								 QLatin1Literal("check_mark"),
								 QLatin1Literal("cross_mark")
	};

	for(const auto& sticker : defaultStickers) {
		addItem(getResourcePath(sticker));
	}
}

QString StickerPicker::getResourcePath(const QString &name) const
{
	return QLatin1Literal(":/stickers/") + name + QLatin1Literal(".svg");
}

void StickerPicker::addItem(const QString &path)
{
	auto icon = QIcon(path);
	auto filename = PathHelper::extractFilename(path);
	filename = PathHelper::prettyFilename(filename);
	mToolButton->addItem(icon, filename, path);
}

void StickerPicker::selectionChanged()
{
	emit stickerSelected(sticker());
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

} // namespace kImageAnnotator
