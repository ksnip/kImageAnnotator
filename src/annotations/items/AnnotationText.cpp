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

#include "AnnotationText.h"

#include <QFocusEvent>

AnnotationText::AnnotationText(const QPointF &startPosition, const AnnotationProperties &properties) :
    AbstractAnnotationRect(startPosition, properties)
{
    setFlag(QGraphicsItem::ItemIsFocusable, true);
}

void AnnotationText::updateShape()
{
    QPainterPath path;
    path.addRect(*mRect);
    setShape(path);
}

void AnnotationText::focusOutEvent(QFocusEvent *event)
{
    auto reason = event->reason();
    qDebug("Focus out %s", qPrintable(QString::number((int) reason)));
    QGraphicsItem::focusOutEvent(event);
}

void AnnotationText::focusInEvent(QFocusEvent *event)
{
    qDebug("Focus in");
    QGraphicsItem::focusInEvent(event);
}

void AnnotationText::keyPressEvent(QKeyEvent *event)
{
    qDebug("Key press");
}

void AnnotationText::finish()
{
    setFocus();
}
