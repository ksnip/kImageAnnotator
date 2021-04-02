/*
 * Copyright (C) 2018 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
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

#ifndef KIMAGEANNOTATOR_TOOLPICKER_H
#define KIMAGEANNOTATOR_TOOLPICKER_H

#include <QWidget>
#include <QActionGroup>
#include <QToolButton>
#include <QVBoxLayout>
#include <QMenu>

#include "CustomToolButton.h"
#include "CustomToolButtonAction.h"
#include "src/common/enum/Tools.h"
#include "src/common/helper/IconLoader.h"

namespace kImageAnnotator {

class ToolPicker : public QWidget
{
Q_OBJECT
public:
	explicit ToolPicker(QWidget *parent);
	~ToolPicker() override;
	void setTool(Tools newTool);
	Tools tool();
	void setOrientation(Qt::Orientation orientation);

signals:
	void toolSelected(Tools newTool);

private:
	QActionGroup *mActionGroup;
	QBoxLayout *mLayout;
	Tools mSelectedToolType;
	QHash<QAction *, Tools> mActionToTool;
	QHash<QAction *, CustomToolButton *> mActionToButton;

	void initGui();
	QAction *createAction(const QString &tooltip, const QIcon &icon, Qt::Key shortcut, Tools toolType);
	CustomToolButton *createButton(QAction *defaultAction);
	CustomToolButton *createButton(QMenu *menu);

private slots:
	void actionTriggered(QAction *action);
	void setToolAndNotify(Tools newTool);
};

} // namespace kImageAnnotator

#endif // KIMAGEANNOTATOR_TOOLPICKER_H
