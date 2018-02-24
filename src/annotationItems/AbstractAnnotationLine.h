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

#ifndef ABSTRACTANNOTATIONLINE_H
#define ABSTRACTANNOTATIONLINE_H

#include "AbstractAnnotationItem.h"

class AbstractAnnotationLine : public AbstractAnnotationItem
{
public:
    AbstractAnnotationLine(const QPointF& startPosisition, const AnnotationItemProperties& properties);
    ~AbstractAnnotationLine();
    void addPoint(const QPointF & position) override;
    void moveTo(const QPointF & newPosition) override;
    QLineF line() const;
    void setLine(const QLineF& line);
    void setPointAt(const QPointF& point, int index);

protected:
    QLineF* mLine;
};

#endif // ABSTRACTANNOTATIONLINE_H
