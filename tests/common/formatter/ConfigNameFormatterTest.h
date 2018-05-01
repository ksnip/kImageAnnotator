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

#ifndef CONFIGNAMEFORMATTERTEST_H
#define CONFIGNAMEFORMATTERTEST_H

#include <QtTest>
#include <QList>

#include "../../../src/common/formatter/ConfigNameFormatter.h"
#include "../../../src/common/enum/ToolTypes.h"

class ConfigNameFormatterTest : public QObject
{
Q_OBJECT
private slots:
    void initTestCase();

    void TestToolString_Should_FormatToolStringCorrectly();
    void TestToolColorString_Should_FormatToolStringCorrectly();
    void TestToolSizeString_Should_FormatToolStringCorrectly();
    void TestToolFillTypeString_Should_FormatToolStringCorrectly();

private:
    QList<ToolTypes> toolList;
};

#endif // CONFIGNAMEFORMATTERTEST_H
