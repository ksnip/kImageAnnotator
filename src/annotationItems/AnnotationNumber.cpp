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

#include "AnnotationNumber.h"

AnnotationNumber::AnnotationNumber(const QPointF& centerPosition, int number, const AnnotationProperties& properties) :
    AbstractAnnotationRect(centerPosition, properties)
{
    mFont = new QFont("Helvetica", QFont::Bold);
    mNumberString = QString::number(number);
    mRect->setHeight(50);
    mRect->setWidth(50);
    mRect->moveCenter(centerPosition);
    updateShape();
}

AnnotationNumber::~AnnotationNumber()
{
    delete mFont;
}

void AnnotationNumber::addPoint(const QPointF& position)
{
    Q_UNUSED(position);

    // Nothing to do here
}

void AnnotationNumber::updateShape()
{
    QPainterPath path  ;
    path.addEllipse(*mRect);
    setShape(path);

    updateFontSize();
}

void AnnotationNumber::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    AbstractAnnotationRect::paint(painter, option, widget);

    painter->setFont(*mFont);
    painter->setPen(QColor("white"));
    painter->drawText(boundingRect(), Qt::AlignCenter, mNumberString);
}

void AnnotationNumber::updateFontSize()
{
    auto mainRect = boundingRect().adjusted(5, 5, -10, -10);
    mFont->setPixelSize(mainRect.height());
    while(mFont->pixelSize() > 10) {
        QFontMetricsF metrics(*mFont);
        auto textRect = metrics.boundingRect(mNumberString);
        if(textRect.width() > mainRect.width() || textRect.height() > mainRect.height()) {
            mFont->setPixelSize(mFont->pixelSize() - 3);
        } else {
            break;
        }
    }
}
