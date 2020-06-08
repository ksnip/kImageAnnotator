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

#ifndef KIMAGEANNOTATOR_LISTMENUITEM_H
#define KIMAGEANNOTATOR_LISTMENUITEM_H

#include <QWidget>
#include <QStyleOptionMenuItem>
#include <QPaintEvent>
#include <QMouseEvent>

#include "src/common/constants/Constants.h"
#include "src/common/provider/ScaledSizeProvider.h"

namespace kImageAnnotator {

class ListMenuItem : public QWidget
{
Q_OBJECT
public:
	explicit ListMenuItem(const QIcon &icon, const QString &text, const QVariant &data, QWidget *parent);
	~ListMenuItem() override = default;
	QVariant data() const;
	QIcon icon() const;
	QString text() const;
	QSize minimumSizeHint() const override;
	bool isChecked() const;
	void setIsChecked(bool isChecked);

signals:
	void toggled(bool isChecked);

protected:
	void paintEvent(QPaintEvent* event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void leaveEvent(QEvent *event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;

private:
	QString mText;
	QIcon mIcon;
	bool mIsChecked;
	QVariant mData;
	QSize mIconSize;
	QSize mTextSize;
	QPoint mIconOffset;
	QPoint mTextOffset;
	int mMargin;
	int mSpacer;
	QSize mSize;
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_LISTMENUITEM_H
