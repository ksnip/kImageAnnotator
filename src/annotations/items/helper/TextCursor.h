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

#ifndef KIMAGEANNOTATOR_TEXTCURSOR_H
#define KIMAGEANNOTATOR_TEXTCURSOR_H

#include <QTimer>
#include <QTextDocument>
#include <QTextBlock>

#include "src/annotations/items/helper/TextPositions.h"

namespace kImageAnnotator {

class TextCursor : public QObject
{
Q_OBJECT
public:
    explicit TextCursor();
    ~TextCursor() override;
    void move(TextPositions direction, const QString &text);
    void start();
    void stop();
    int position() const;
    void setPosition(int newPosition);
    bool isVisible() const;

signals:
    void tick() const;

private:
    int mBlinkIntervalInMs = 1000;
    QTimer *mBlinkTimer;
    int mPosition = 0;
    bool mIsVisible = false;

    void moveCursorForward(const QString &text);
    void moveCursorBack(const QString &text);
    void moveCursorUp(const QString &text);
    void moveCursorDown(const QString &text);
    void fitPositionToNewBlock(int positionInBlock, const QTextBlock &targetBlock);
    void movePositionToEndOfBlock(const QTextBlock &targetBlock);
    void moveToSamePositionInNewBlock(int positionInBlock, const QTextBlock &targetBlock);
};

} // namespace kImageAnnotator
#endif //KIMAGEANNOTATOR_TEXTCURSOR_H
