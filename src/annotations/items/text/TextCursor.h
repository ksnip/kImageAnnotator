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

#ifndef KIMAGEANNOTATOR_TEXTCURSOR_H
#define KIMAGEANNOTATOR_TEXTCURSOR_H

#include <QTimer>
#include <QTextDocument>
#include <QTextBlock>

namespace kImageAnnotator {

class TextCursor : public QObject
{
Q_OBJECT
public:
    explicit TextCursor(QTextDocument *document);
	TextCursor(const TextCursor &other);
    ~TextCursor() override;
    void start();
    void stop();
    int position() const;
    void setPosition(int newPosition);
    bool isVisible() const;
	void insertText(const QString &text);
	void deleteChar();
	void deletePreviousChar();
	void movePosition(QTextCursor::MoveOperation operation);
	QString	selectedText() const;
	void removeSelectedText();
	void select(QTextCursor::SelectionType selection);

signals:
    void tick() const;

private:
	QTextCursor *mInnerTextCursor;
    int mBlinkIntervalInMs = 800;
    QTimer *mBlinkTimer;
    bool mIsVisible = false;

	void connectSlots();
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_TEXTCURSOR_H
