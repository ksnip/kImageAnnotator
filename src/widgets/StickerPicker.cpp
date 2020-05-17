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

	insertItem(getResourcePath(QStringLiteral("face_blowing_a_kiss")));
	insertItem(getResourcePath(QStringLiteral("face_savoring_food")));
	insertItem(getResourcePath(QStringLiteral("grinning_face_with_big_eyes")));
	insertItem(getResourcePath(QStringLiteral("grinning_face_with_smiling_eyes")));
	insertItem(getResourcePath(QStringLiteral("grinning_face_with_sweat")));
	insertItem(getResourcePath(QStringLiteral("grinning_squinting_face")));
	insertItem(getResourcePath(QStringLiteral("hushed_face")));
	insertItem(getResourcePath(QStringLiteral("nerd_face")));
	insertItem(getResourcePath(QStringLiteral("neutral_face")));
	insertItem(getResourcePath(QStringLiteral("smiling_face_with_heart_eyes")));
	insertItem(getResourcePath(QStringLiteral("smiling_face_with_hearts")));
	insertItem(getResourcePath(QStringLiteral("thinking_face")));

	mComboBox->setFixedSize(ScaledSizeProvider::getScaledSize(Constants::SettingsWidgetSize));
	mComboBox->setIconSize(ScaledSizeProvider::getScaledSize(QSize(30, 30)));
	mComboBox->setToolTip(tooltip);
	mComboBox->setFocusPolicy(Qt::NoFocus);

	mLayout->addWidget(mLabel);
	mLayout->addWidget(mComboBox);

	setLayout(mLayout);
	setFixedSize(sizeHint());
}

QString StickerPicker::getResourcePath(const QString &name) const
{
	return QStringLiteral(":/stickers/stickers/") + name + QStringLiteral(".svg");
}

void StickerPicker::insertItem(const QString &path)
{
	auto icon = QIcon(path);
	mComboBox->addItem(icon, path, path);
}

void StickerPicker::selectionChanged()
{
	emit stickerSelected(sticker());
}

} // namespace kImageAnnotator
