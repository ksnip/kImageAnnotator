/*
 * Copyright (C) 2018 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
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

#ifndef KIMAGEANNOTATOR_KEYINPUTHELPER_H
#define KIMAGEANNOTATOR_KEYINPUTHELPER_H

#include <QKeyEvent>

#include "TextPositions.h"
#include "CapsLockStatusChecker.h"

namespace kImageAnnotator {

class KeyInputHelper : public QObject
{
Q_OBJECT
public:
	explicit KeyInputHelper() = default;
	~KeyInputHelper() override = default;
	void handleKeyPress(const QKeyEvent *event) const;
	bool isShiftPressed(const QKeyEvent *event) const;
	bool isControlPressed(const QKeyEvent *event) const;
	QString getTextWithCorrectCase(const QKeyEvent *event) const;

signals:
	void remove(TextPositions position) const;
	void insert(const QString &text) const;
	void move(TextPositions position) const;
	void paste() const;
	void escape() const;

private:
	bool isModifierPressed(const QKeyEvent *event, Qt::KeyboardModifier modifier) const;
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_KEYINPUTHELPER_H
