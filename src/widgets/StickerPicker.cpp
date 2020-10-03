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
	mToolButton(new GridMenuToolButton(this))
{
	init(icon, tooltip);
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

void StickerPicker::init(const QIcon &icon, const QString &tooltip)
{
	mLayout->setContentsMargins(0, 0, 0, 0);

	mLabel->setPixmap(icon.pixmap(Constants::SettingsWidgetIconSize));
	mLabel->setToolTip(tooltip);

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
	QStringList defaultStickers{ QStringLiteral("heart_eyes"),
	                             QStringLiteral("sunglasses"),
	                             QStringLiteral("stuck_out_tongue"),
	                             QStringLiteral("stuck_out_tongue_closed_eyes"),
	                             QStringLiteral("sweat_smile"),
	                             QStringLiteral("grimacing"),
	                             QStringLiteral("rage"),
	                             QStringLiteral("astonished"),
	                             QStringLiteral("hushed"),
	                             QStringLiteral("laughing"),
	                             QStringLiteral("kissing_heart"),
	                             QStringLiteral("pushpin"),
	                             QStringLiteral("hearts"),
	                             QStringLiteral("ballot_box_with_check"),
	                             QStringLiteral("negative_squared_cross_mark"),
	                             QStringLiteral("bulb")
                                                 
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
