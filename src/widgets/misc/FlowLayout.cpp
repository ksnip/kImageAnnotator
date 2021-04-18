/*
 * Copyright (C) 2021 Damir Porobic <damir.porobic@gmx.com>
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

#include "FlowLayout.h"

/*
 * Implementation based on Qt FlowLayout Example https://doc.qt.io/qt-5/qtwidgets-layouts-flowlayout-example.html
 */

namespace kImageAnnotator {

FlowLayout::FlowLayout(QWidget *parent) :
	QLayout(parent),
	mHorizontalSpacing(-1),
	mVerticalSpacing(-1)
{
}

FlowLayout::~FlowLayout()
{
	qDeleteAll(mItems);
}

void FlowLayout::addItem(QLayoutItem *item)
{
	mItems.append(item);
}

int FlowLayout::horizontalSpacing() const
{
	return mHorizontalSpacing >= 0 ? mHorizontalSpacing : smartSpacing(QStyle::PM_LayoutHorizontalSpacing);
}

int FlowLayout::verticalSpacing() const
{
	return mVerticalSpacing >= 0 ? mVerticalSpacing : smartSpacing(QStyle::PM_LayoutVerticalSpacing);
}

int FlowLayout::count() const
{
	return mItems.size();
}

QLayoutItem *FlowLayout::itemAt(int index) const
{
	return mItems.value(index);
}

QLayoutItem *FlowLayout::takeAt(int index)
{
	if (index < 0 || index >= count()) {
		return nullptr;
	}
	return mItems.takeAt(index);
}

void FlowLayout::setSpacing(int horizontal, int vertical)
{
	mHorizontalSpacing = horizontal;
	mVerticalSpacing = vertical;
}

Qt::Orientations FlowLayout::expandingDirections() const
{
	return { };
}

bool FlowLayout::hasHeightForWidth() const
{
	return true;
}

int FlowLayout::heightForWidth(int width) const
{
	auto rect = QRect(0, 0, width, 0);
	auto height = calculateLayout(rect, false);
	return height;
}

void FlowLayout::setGeometry(const QRect &rect)
{
	QLayout::setGeometry(rect);
	calculateLayout(rect, true);
}

QSize FlowLayout::sizeHint() const
{
	return minimumSize();
}

QSize FlowLayout::minimumSize() const
{
	QSize size;
	for (auto item : qAsConst(mItems)) {
		size = size.expandedTo(item->minimumSize());
	}

	auto margins = contentsMargins();
	size += QSize(margins.left() + margins.right(), margins.top() + margins.bottom());
	
	return size;
}

int FlowLayout::calculateLayout(const QRect &rect, bool applyChanged) const
{
	auto margins = contentsMargins();
	auto effectiveRect = rect.adjusted(+margins.left(), +margins.top(), -margins.right(), -margins.bottom());
	auto x = effectiveRect.x();
	auto y = effectiveRect.y();
	auto spaceX = horizontalSpacing();
	auto spaceY = verticalSpacing();
	auto lineHeight = 0;

	auto largestItemWidth = 0;
	auto largestItemHeight = 0;
	auto minHorizontalWidth = 0;
	for (auto item : qAsConst(mItems)) {
		largestItemWidth = qMax(item->sizeHint().width(), largestItemWidth);
		largestItemHeight = qMax(item->sizeHint().height(), largestItemHeight);
		minHorizontalWidth += item->sizeHint().width();
	}

	auto isEqualWidthPerItemRequired = largestItemHeight * 2 > effectiveRect.height() || effectiveRect.width() >= minHorizontalWidth ;

	for (auto item : qAsConst(mItems)) {
		auto width = isEqualWidthPerItemRequired ? item->sizeHint().width() : largestItemWidth;
		auto nextX = x + width + spaceX;
		auto isOutsideCurrentRow = nextX - spaceX > effectiveRect.right() && lineHeight > 0;
		if (isOutsideCurrentRow) {
			x = effectiveRect.x();
			y = y + lineHeight + spaceY;
			nextX = x + width + spaceX;
			lineHeight = 0;
		}

		if (applyChanged) {
			item->setGeometry(QRect(QPoint(x, y), item->sizeHint()));
		}

		x = nextX;
		lineHeight = qMax(lineHeight, item->sizeHint().height());
	}
	return y + lineHeight - rect.y() + margins.bottom();
}

int FlowLayout::smartSpacing(QStyle::PixelMetric pixelMetric) const
{
	auto parent = this->parent();
	auto parentWidget = dynamic_cast<QWidget *>(parent);
	return parentWidget->style()->pixelMetric(pixelMetric, nullptr, parentWidget);
}

} // namespace kImageAnnotator
