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

StickerPicker::StickerPicker(const QIcon &icon, const QString &tooltip) :
	mLayout(new QHBoxLayout(this)),
	mLabel(new QLabel(this)),
	mComboBox(new QComboBox(this))
{
	init(icon, tooltip);

	connect(mComboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::activated), this, &StickerPicker::selectionChanged);
}

StickerPicker::~StickerPicker()
{
	delete mLayout;
	delete mLabel;
	delete mComboBox;
}

void StickerPicker::setSticker(const QString &name)
{
	mComboBox->setCurrentText(name);
	selectionChanged();
}

QString StickerPicker::sticker() const
{
	return mComboBox->currentData(Qt::UserRole).toString();
}

void StickerPicker::init(const QIcon &icon, const QString &tooltip)
{
	mLayout->setContentsMargins(0, 0, 0, 0);

	mLabel->setPixmap(icon.pixmap(ScaledSizeProvider::getScaledSize(QSize(20, 20))));
	mLabel->setToolTip(tooltip);

	addDefaultStickers();

	mComboBox->setFixedSize(ScaledSizeProvider::getScaledSize(Constants::SettingsWidgetSize));
	mComboBox->setIconSize(ScaledSizeProvider::getScaledSize(QSize(30, 30)));
	mComboBox->setToolTip(tooltip);
	mComboBox->setFocusPolicy(Qt::NoFocus);

	mLayout->addWidget(mLabel);
	mLayout->addWidget(mComboBox);

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
	                             QStringLiteral("smiling_face_with_sunglasses")
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
	mComboBox->addItem(icon, filename, path);
}

void StickerPicker::selectionChanged()
{
	emit stickerSelected(sticker());
}

void StickerPicker::setStickers(const QStringList &stickerPaths, bool keepDefault)
{
	mComboBox->clear();

	if(keepDefault) {
		addDefaultStickers();
	}

	for(const auto& stickerPath : stickerPaths) {
		addItem(stickerPath);
	}
}

} // namespace kImageAnnotator
