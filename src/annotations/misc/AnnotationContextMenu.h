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

#ifndef KIMAGEANNOTATOR_ANNOTATIONCONTEXTMENU_H
#define KIMAGEANNOTATOR_ANNOTATIONCONTEXTMENU_H

#include <QMenu>

namespace kImageAnnotator {

class AnnotationContextMenu : public QMenu
{
Q_OBJECT
public:
	explicit AnnotationContextMenu();
	~AnnotationContextMenu() = default;
	void setOverItem(bool isOverItem);
	void setPastEnabled(bool enabled);
	void exec(const QPointF &position);

signals:
	void bringToFront() const;
	void bringForward() const;
	void sendBackward() const;
	void sendToBack() const;
	void copy(const QPointF &position) const;
	void paste(const QPointF &position) const;
	void erase() const;

private:
	QMenu *mArrangeMenu;
	QAction *mCopyAction;
	QAction *mPastAction;
	QAction *mSelectThis;
	QAction *mDeleteAction;
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_ANNOTATIONCONTEXTMENU_H
