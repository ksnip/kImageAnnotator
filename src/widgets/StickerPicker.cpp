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
	QStringList defaultStickers{ QStringLiteral("face_blowing_a_kiss"),
	                             QStringLiteral("face_savoring_food"),
	                             QStringLiteral("grinning_face_with_big_eyes"),
	                             QStringLiteral("grinning_face_with_smiling_eyes"),
	                             QStringLiteral("grinning_face_with_sweat"),
	                             QStringLiteral("grinning_squinting_face"),
	                             QStringLiteral("hushed_face"),
	                             QStringLiteral("nerd_face"),
	                             QStringLiteral("neutral_face"),
	                             QStringLiteral("smiling_face_with_heart_eyes"),
	                             QStringLiteral("smiling_face_with_hearts"),
	                             QStringLiteral("confused_face"),
	                             QStringLiteral("face_with_symbols_on_mouth"),
	                             QStringLiteral("pouting_face"),
	                             QStringLiteral("smiling_face_with_sunglasses"),
	                             QStringLiteral("check_mark"),
	                             QStringLiteral("cross_mark")
	};

	for(const auto& sticker : defaultStickers) {
		addItem(getResourcePath(sticker));
	}
}

QString StickerPicker::getResourcePath(const QString &name) const
{
	return QStringLiteral(":/stickers/") + name + QStringLiteral(".svg");
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
