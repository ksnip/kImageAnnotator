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

#ifndef ANNOTATIONITEMFACTORY_H
#define ANNOTATIONITEMFACTORY_H

#include <QObject>

#include "AnnotationItemProperties.h"
#include "AnnotationLine.h"
#include "AnnotationArrow.h"
#include "AnnotationRect.h"
#include "AnnotationEllipse.h"
#include "../ToolTypes.h"

class AnnotationItemFactory : public QObject
{
    Q_OBJECT
public:
    explicit AnnotationItemFactory();
    ~AnnotationItemFactory();

    AbstractAnnotationItem* createItem(const QPointF& initPosition, ToolTypes tool) const;

public slots:
    void setColor(const QColor& color);
    void setSize(int size);
    void setFillType(FillTypes fillType);

private:
    AnnotationItemProperties *mItemProperties;
};

#endif // ANNOTATIONITEMFACTORY_H
