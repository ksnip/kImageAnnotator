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

#ifndef KIMAGEANNOTATOR_FLOWLAYOUT_H
#define KIMAGEANNOTATOR_FLOWLAYOUT_H

#include <QLayout>
#include <QStyle>
#include <QWidget>

namespace kImageAnnotator {

class FlowLayout : public QLayout
{
public:
	explicit FlowLayout(QWidget *parent);
	~FlowLayout() override;
	void addItem(QLayoutItem *item) override;
	int horizontalSpacing() const;
	int verticalSpacing() const;
	Qt::Orientations expandingDirections() const override;
	bool hasHeightForWidth() const override;
	int heightForWidth(int) const override;
	int count() const override;
	QLayoutItem *itemAt(int index) const override;
	QSize minimumSize() const override;
	void setGeometry(const QRect &rect) override;
	QSize sizeHint() const override;
	QLayoutItem *takeAt(int index) override;
	void setSpacing(int horizontal, int vertical);

private:
	QList<QLayoutItem *> mItems;
	int mHorizontalSpacing;
	int mVerticalSpacing;

	int calculateLayout(const QRect &rect, bool applyChanged) const;
	int smartSpacing(QStyle::PixelMetric pixelMetric) const;
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_FLOWLAYOUT_H
