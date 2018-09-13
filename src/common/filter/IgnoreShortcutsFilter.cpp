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

#include "IgnoreShortcutsFilter.h"

namespace kImageAnnotator {

void IgnoreShortcutsFilter::apply()
{
    QCoreApplication::instance()->installEventFilter(this);
}

void IgnoreShortcutsFilter::remove()
{
    QCoreApplication::instance()->removeEventFilter(this);
}

bool IgnoreShortcutsFilter::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::Shortcut) {
        auto shortcutEvent = dynamic_cast<QShortcutEvent *>(event);
        auto shortcutString = shortcutEvent->key().toString().toLower();

        if (ignoreShortcut(shortcutString)) {
            return true;
        }

        if (shortcutString.contains(QStringLiteral("shift"))) {
            shortcutString = shortcutString.remove(QStringLiteral("shift+")).toUpper();
        }

        // Create new event and send it to the focused item.
        auto keyEvent = createKeyEvent(shortcutString);
        QCoreApplication::postEvent(QApplication::focusWidget(), keyEvent);
        return true;
    }

    return QObject::eventFilter(watched, event);
}

bool IgnoreShortcutsFilter::ignoreShortcut(const QString &shortcutString) const
{
    return shortcutString.contains(QStringLiteral("ctrl")) || shortcutString.contains(QStringLiteral("alt"));
}

QKeyEvent *IgnoreShortcutsFilter::createKeyEvent(const QString &text) const
{
    return new QKeyEvent(QEvent::KeyPress, Qt::Key_unknown, Qt::NoModifier, text);
}

} // namespace kImageAnnotator
