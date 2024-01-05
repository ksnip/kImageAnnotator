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

#include <QtGui/QPainter>
#include "ListMenuItem.h"

namespace kImageAnnotator {

ListMenuItem::ListMenuItem(const QIcon &icon, const QString &text, const QVariant &data, QWidget *parent) :
	QWidget(parent),
	mIcon(icon),
	mText(text),
	mData(data),
	mIsChecked(false),
	mSpacer(6),
	mMargin(5)
{
	setMouseTracking(true);

	mIconSize = ScaledSizeProvider::menuItemIconSize();
	auto offsetForTextWidth = 1.15; // Width not correct calculated on windows #117
	mTextSize = QSize(fontMetrics().horizontalAdvance(mText) * offsetForTextWidth, fontMetrics().height());
	mIconOffset = QPoint(mMargin, mMargin);
	mTextOffset = QPoint(mIconSize.width() + mIconOffset.x() + mSpacer, (mIconSize.height() - mTextSize.height()) / 2 + mIconOffset.y());
	mSize = QSize(mIconSize.width() + mTextSize.width() + mMargin * 2 + mSpacer, mIconSize.height() + mMargin * 2);
}

QVariant ListMenuItem::data() const
{
	return mData;
}

QIcon ListMenuItem::icon() const
{
	return mIcon;
}

QString ListMenuItem::text() const
{
	return mText;
}

QSize ListMenuItem::minimumSizeHint() const
{
	return mSize;
}

bool ListMenuItem::isChecked() const
{
	return mIsChecked;
}

void ListMenuItem::setIsChecked(bool isChecked)
{
	mIsChecked = isChecked;
	emit toggled(isChecked);
	update();
}

void ListMenuItem::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	QStyleOption styleOption;
	styleOption.initFrom(this);
	auto rect = event->rect().adjusted(0,0,-1,-1);

	if(styleOption.state & QStyle::State_MouseOver)
	{
		auto defaultBrush = painter.brush();
		auto defaultPen = painter.pen();
		painter.setBrush(Constants::HoverColor);
		painter.setPen(Constants::HoverColor);
		painter.drawRect(rect);
		painter.setBrush(defaultBrush);
		painter.setPen(defaultPen);
	}

	painter.drawPixmap(rect.topLeft() + mIconOffset, mIcon.pixmap(mIconSize));
	painter.drawText(QRect(rect.topLeft() + mTextOffset, mTextSize), Qt::AlignLeft | Qt::AlignVCenter, mText);

	if(mIsChecked) {
		painter.drawRect(rect);
	}
}

void ListMenuItem::mouseMoveEvent(QMouseEvent *event)
{
	update();
	QWidget::mouseMoveEvent(event);
}

void ListMenuItem::leaveEvent(QEvent *event)
{
	update();
	QWidget::leaveEvent(event);
}

void ListMenuItem::mouseReleaseEvent(QMouseEvent* event)
{
	QWidget::mouseReleaseEvent(event);

	QRect itemRect(QPoint(0, 0), mSize);
	if (isEnabled() && itemRect.contains(mapFromGlobal(QCursor::pos()))) {
		mIsChecked = true;
		emit toggled(mIsChecked);
	}
}

} // namespace kImageAnnotator