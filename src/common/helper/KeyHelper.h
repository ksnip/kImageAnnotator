/*
 * Copyright (C) 2018 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KEYHELPER_H
#define KEYHELPER_H

#include <QObject>
#include <QKeyEvent>

class KeyHelper : public QObject
{
    Q_OBJECT
public:
    explicit KeyHelper();
    ~KeyHelper() = default;

    void keyPress(QKeyEvent *keyEvent);
    void keyRelease(QKeyEvent *keyEvent);
    bool isControlPressed() const;
    bool isShiftPressed() const;

signals:
    void deleteReleased() const;
    void escapeReleased() const;
    void undoPressed() const;
    void redoPressed() const;

private:
    QHash<Qt::Key, bool> mKeyToIsPressed;

    void emitReleaseSignal(Qt::Key key);
    void emitPressSignal(Qt::Key key);
};

#endif // KEYHELPER_H