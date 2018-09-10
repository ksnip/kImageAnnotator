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

#ifndef KIMAGEANNOTATOR_IGNORESHORTCUTSFILTER_H
#define KIMAGEANNOTATOR_IGNORESHORTCUTSFILTER_H

#include <QCoreApplication>
#include <QApplication>
#include <QShortcutEvent>
#include <QKeyEvent>
#include <QWidget>

class IgnoreShortcutsFilter : public QObject
{
public:
    explicit IgnoreShortcutsFilter() = default;
    ~IgnoreShortcutsFilter() override = default;
    void apply();
    void remove();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
    bool ignoreShortcut(const QString &shortcutString) const;
    QKeyEvent *createKeyEvent(const QString &text) const;
};

#endif //KIMAGEANNOTATOR_IGNORESHORTCUTSFILTER_H
