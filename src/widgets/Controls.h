/*
 * Copyright (C) 2021 Antonio Prcela <antonio.prcela@gmail.com>
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

#ifndef KIMAGEANNOTATOR_CONTROLS_H
#define KIMAGEANNOTATOR_CONTROLS_H

#include <QActionGroup>
#include <QUndoStack>
#include <QWidget>

#include "CustomToolButton.h"
#include "CustomToolButtonAction.h"
#include "src/common/helper/IconLoader.h"

namespace kImageAnnotator {

class Controls : public QWidget
{
Q_OBJECT
public:
	explicit Controls(QWidget *parent);
	~Controls() override = default;

Q_SIGNALS:
	void undo() const;
	void redo() const;
	void crop() const;
	void scale() const;
	void rotate() const;
	void modifyCanvas() const;

private:
	QHBoxLayout *mLayout;

	void initGui();
	QAction *createAction(const QString &tooltip, const QIcon &icon);
	CustomToolButton *createButton(QAction *defaultAction);

private slots:
	void undoTriggered() const;
	void redoTriggered() const;
	void cropTriggered() const;
	void scaleTriggered() const;
	void rotateTriggered() const;
	void modifyCanvasTriggered() const;
};

} // namespace kImageAnnotator

#endif // KIMAGEANNOTATOR_CONTROLS_H
