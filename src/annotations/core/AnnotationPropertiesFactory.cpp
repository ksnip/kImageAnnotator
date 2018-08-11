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

#include "AnnotationPropertiesFactory.h"

AnnotationPropertiesFactory::AnnotationPropertiesFactory()
{
    mConfig = Config::instance();
}

AnnotationProperties AnnotationPropertiesFactory::createProperties(ToolTypes tool) const
{
    AnnotationProperties properties;

    setColor(properties, tool);
    setForegroundColor(tool, properties);
    setSize(tool, properties);
    setFill(tool, properties);
    setShadowEnabled(properties, tool);

    return properties;
}

void AnnotationPropertiesFactory::setColor(AnnotationProperties &properties, ToolTypes tool) const
{
    auto color = mConfig->toolColor(tool);

    if (tool == ToolTypes::Marker) {
        color.setAlpha(120);
    }

    properties.setColor(color);
}

void AnnotationPropertiesFactory::setForegroundColor(const ToolTypes &tool, AnnotationProperties &properties) const
{
    properties.setForegroundColor(mConfig->toolForegroundColor(tool));
}

void AnnotationPropertiesFactory::setSize(const ToolTypes &tool, AnnotationProperties &properties) const
{
    auto size = mConfig->toolSize(tool);

    if (tool == ToolTypes::Marker) {
        size = size * 3;
    }

    properties.setSize(size);
}

void AnnotationPropertiesFactory::setFill(const ToolTypes &tool, AnnotationProperties &properties) const
{
    properties.setFillType(mConfig->toolFillType(tool));
}

void AnnotationPropertiesFactory::setShadowEnabled(AnnotationProperties &properties, ToolTypes tool) const
{
    properties.setShadowEnabled(tool != ToolTypes::Marker);
}
