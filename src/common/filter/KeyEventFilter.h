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

#ifndef KIMAGEANNOTATOR_KEYEVENTFILTER_H
#define KIMAGEANNOTATOR_KEYEVENTFILTER_H

#include <QObject>
#include <QKeyEvent>
#include <QCoreApplication>
#include <QList>

#include "IKeyEventListener.h"

namespace kImageAnnotator {

class KeyEventFilter : public QObject
{
	Q_OBJECT
public:
	explicit KeyEventFilter();
	~KeyEventFilter() override;
	void setListener(IKeyEventListener *listener);

protected:
	bool eventFilter(QObject *watched, QEvent *event) override;

private:
	QList<int> mPressedKeyCodes;
	IKeyEventListener *mKeyEventListener;

	void handleKeyPressed(QEvent *event);
	void handleKeyReleased(QEvent *event);
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_KEYEVENTFILTER_H
