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

#ifndef KIMAGEANNOTATOR_ANNOTATIONTEXT_H
#define KIMAGEANNOTATOR_ANNOTATIONTEXT_H

#include <QClipboard>
#include <QtMath>

#include "AbstractAnnotationRect.h"
#include "interfaces/EditableItem.h"
#include "src/annotations/properties/AnnotationTextProperties.h"
#include "src/annotations/items/helper/TextCursor.h"
#include "src/annotations/items/helper/KeyInputHelper.h"
#include "src/common/filter/IgnoreShortcutsFilter.h"

namespace kImageAnnotator {

class AnnotationText : public AbstractAnnotationRect, public EditableItem
{
Q_OBJECT
public:
	AnnotationText(const QPointF &startPosition, AnnotationTextProperties *properties);
	AnnotationText(const AnnotationText &other);
	~AnnotationText() override = default;
	void finish() override;
	const AnnotationTextProperties *properties() const override;
	ToolTypes toolType() const override;
	QPainterPath shape() const override;
	void enableEditing() override ;
	void disableEditing() override ;

protected:
	void updateShape() override;
	void focusOutEvent(QFocusEvent *event) override;
	void keyPressEvent(QKeyEvent *event) override;
	void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;

private:
	QString mText;
	KeyInputHelper mKeyInputHelper;
	TextCursor mTextCursor;
	IgnoreShortcutsFilter mIgnoreShortcutsFilter;
	bool mIsInEditMode;
	QPen mEditModeOutlinePen;

	void connectSlots();
	QRect getTextRect() const;
	void setupEditModeOutlinePen();

private slots:
	void removeText(TextPositions direction);
	void insertText(const QString &text);
	void moveCursor(TextPositions direction);
	void pasteText();
	void escape();
	void adjustRect();
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_ANNOTATIONTEXT_H
