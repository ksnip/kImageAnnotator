/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef KIMAGEANNOTATOR_ANNOTATIONTEXTHANDLER_H
#define KIMAGEANNOTATOR_ANNOTATIONTEXTHANDLER_H

#include <QPainter>
#include <QApplication>
#include <QClipboard>
#include <QTextCursor>

#include "src/annotations/items/text/TextCursor.h"
#include "src/common/filter/IgnoreShortcutsFilter.h"
#include "src/annotations/items/text/KeyInputHelper.h"

namespace kImageAnnotator {

class AnnotationTextHandler : public QObject
{
	Q_OBJECT
public:
	explicit AnnotationTextHandler();
	AnnotationTextHandler(const AnnotationTextHandler &other);
	~AnnotationTextHandler() override = default;
	void insertText(const QString &text);
	void enableEditing();
	void disableEditing();
	void paintText(QPainter *painter, QRectF *rect, const QFont &font, const QColor &color, int margin, bool isShadowEnabled);
	void updateRect(QRectF *rect, const QFont &font, int margin) const;
	QRect getTextRect(QRectF *rect, const QFont& font, int margin) const;
	void handleKeyEvent(QKeyEvent *event);

signals:
	void changed() const;
	void finished() const;

private:
	IgnoreShortcutsFilter mIgnoreShortcutsFilter;
	bool mIsInEditMode;
	QPen mEditModeOutlinePen;
	KeyInputHelper mKeyInputHelper;
	QTextDocument *mTextDocument;
	TextCursor *mTextCursor;

	bool isCursorInBlock(int blockPosition, int blockLength) const;
	void setupEditModeOutlinePen();
	void connectSlots();
	void removeText(QTextCursor::MoveOperation operation);
	void moveCursor(QTextCursor::MoveOperation operation);
	void pasteText();
	void cutText();
	void copyText();
	void selectAllText();
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_ANNOTATIONTEXTHANDLER_H
