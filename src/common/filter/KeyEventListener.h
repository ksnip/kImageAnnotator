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

#ifndef KIMAGEANNOTATOR_KEYEVENTLISTENER_H
#define KIMAGEANNOTATOR_KEYEVENTLISTENER_H

#include <QObject>
#include <QKeyEvent>
#include <QCoreApplication>

namespace kImageAnnotator {

class KeyEventListener : public QObject
{
	Q_OBJECT
public:
	explicit KeyEventListener();
	~KeyEventListener() override;

signals:
	void keyPressed(QKeyEvent *event);
	void keyReleased(QKeyEvent *event);

protected:
	bool eventFilter(QObject *watched, QEvent *event) override;
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_KEYEVENTLISTENER_H
