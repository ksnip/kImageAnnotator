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

#include "AbstractAnnotationRect.h"
#include "helper/KeyInputHelper.h"
#include "helper/TextCursor.h"
#include "../../common/filter/IgnoreShortcutsFilter.h"

class AnnotationText : public QObject, public AbstractAnnotationRect
{
Q_OBJECT
public:
    AnnotationText(const QPointF &startPosition, const QFont &font, const AnnotationProperties &properties);
    ~AnnotationText() override = default;
    void finish() override;

protected:
    void updateShape() override;
    void focusOutEvent(QFocusEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;

private:
    QString mText;
    KeyInputHelper mKeyInputHelper;
    TextCursor mTextCursor;
    QFont mFont;
    IgnoreShortcutsFilter mIgnoreShortcutsFilter;

private slots:
    void removeText(TextPositions direction);
    void insertText(const QString &text);
    void moveCursor(TextPositions direction);
    void pasteText();
    void escape();
};

#endif //KIMAGEANNOTATOR_ANNOTATIONTEXT_H
