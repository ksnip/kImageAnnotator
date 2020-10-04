/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
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

#include "AnnotationTabContextMenuTest.h"

void AnnotationTabContextMenuTest::TestCustomActionTriggered_Should_CallInnerActionWithCorrectTabIndexSetInData()
{
    auto tabIndex = 22;
    QAction customAction;
    QSignalSpy spy(&customAction, &QAction::triggered);
    QWidget parent;
    AnnotationTabContextMenu menu(&parent);
    menu.addCustomActions(QList<QAction*>{&customAction});
    auto outerAction = menu.actions().last();
    QTimer::singleShot(300, outerAction, &QAction::trigger);
    QTimer::singleShot(400, &menu, &QMenu::close);

    menu.show(tabIndex, {});

    QCOMPARE(customAction.data().toInt(), tabIndex);
    QCOMPARE(spy.count(), 1);
}

void AnnotationTabContextMenuTest::TestAddCustomActions_Should_SetTextIconAndToolTipInOuterAction() 
{
    QAction customAction;
    customAction.setText(QLatin1Literal("LaLa"));
    customAction.setToolTip(QLatin1Literal("Hello Hello"));
    customAction.setIcon(QIcon());
    QWidget parent;
    AnnotationTabContextMenu menu(&parent);
    menu.addCustomActions(QList<QAction*>{&customAction});
    auto outerAction = menu.actions().last();

    QCOMPARE(customAction.text(), outerAction->text());
    QCOMPARE(customAction.toolTip(), outerAction->toolTip());
    QCOMPARE(customAction.icon(), outerAction->icon());
}

void AnnotationTabContextMenuTest::TestCustomActionChanged_Should_UpdateEnabledStateOfOuterAction()
{
    QAction customAction;
    customAction.setEnabled(false);
    QWidget parent;
    AnnotationTabContextMenu menu(&parent);
    menu.addCustomActions(QList<QAction*>{&customAction});
    auto outerAction = menu.actions().last();
    QCOMPARE(customAction.isEnabled(), outerAction->isEnabled());

    customAction.setEnabled(true);

    QCOMPARE(customAction.isEnabled(), outerAction->isEnabled());
}

QTEST_MAIN(AnnotationTabContextMenuTest);