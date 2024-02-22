/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
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

#include "KeyEventFilter.h"

namespace kImageAnnotator {

KeyEventFilter::KeyEventFilter():
	mKeyEventListener(nullptr)
{
	QCoreApplication::instance()->installEventFilter(this);
}

KeyEventFilter::~KeyEventFilter()
{
	QCoreApplication::instance()->removeEventFilter(this);
}

void KeyEventFilter::setListener(IKeyEventListener *listener)
{
	mKeyEventListener = listener;
}

bool KeyEventFilter::eventFilter(QObject *watched, QEvent *event)
{
	if (event->type() == QEvent::KeyPress) {
		handleKeyPressed(event);
	} else if (event->type() == QEvent::KeyRelease) {
		handleKeyReleased(event);
	}

	return QObject::eventFilter(watched, event);
}

void KeyEventFilter::handleKeyReleased(QEvent *event)
{
	auto keyEvent = dynamic_cast<QKeyEvent *>(event);

	if(mPressedKeyCodes.contains(keyEvent->key())) {
		mPressedKeyCodes.removeAll(keyEvent->key());

		if(isListenerSet()) {
			mKeyEventListener->keyReleased(keyEvent);
		}
	}
}

void KeyEventFilter::handleKeyPressed(QEvent *event)
{
	auto keyEvent = dynamic_cast<QKeyEvent *>(event);

	if(isListenerSet() && !mPressedKeyCodes.contains(keyEvent->key())) {
		mPressedKeyCodes.append(keyEvent->key());

		if(isListenerSet()) {
			mKeyEventListener->keyPressed(keyEvent);
		}
	}
}

bool KeyEventFilter::isListenerSet()
{
	return mKeyEventListener != nullptr;
}

} // namespace kImageAnnotator