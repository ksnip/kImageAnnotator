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

#ifndef KIMAGEANNOTATOR_ANNOTATIONNUMBER_H
#define KIMAGEANNOTATOR_ANNOTATIONNUMBER_H

#include "AbstractAnnotationRect.h"

namespace kImageAnnotator {

class AnnotationNumber : public AbstractAnnotationRect
{
public:
    AnnotationNumber(const QPointF &centerPosition, int number, const AnnotationProperties &properties);
    ~AnnotationNumber();
    virtual void addPoint(const QPointF &position, bool modified = false) override;

protected:
    virtual void updateShape() override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    QString mNumberString;
    QFont *mFont;

    void updateFontSize();
};

} // namespace kImageAnnotator

#endif // KIMAGEANNOTATOR_ANNOTATIONNUMBER_H
