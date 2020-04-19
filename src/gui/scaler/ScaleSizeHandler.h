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

#ifndef KIMAGEANNOTATOR_SCALESIZEHANDLER_H
#define KIMAGEANNOTATOR_SCALESIZEHANDLER_H

#include <QObject>
#include <QSize>

namespace kImageAnnotator {

class ScaleSizeHandler : public QObject
{
Q_OBJECT
public:
	explicit ScaleSizeHandler() = default;
	~ScaleSizeHandler() override = default;
	void setSize(QSize size);
	QSize size() const;

signals:
	void widthPixelChanged(int width) const;
	void widthPercentChanged(float width) const;
	void heightPixelChanged(int height) const;
	void heightPercentChanged(float height) const;

public slots:
	void setAspectRatio(bool keepAspectRatio);
	void setWidthPixel(int width);
	void setWidthPercent(float width);
	void setHeightPixel(int height);
	void setHeightPercent(float height);

private:
	bool mKeepAspectRatio;
	QSize mSize;

	float calculatePercent(int newValue, int baseValue) const;
	void setHeight(float percent) const;
	void setWidth(float percent) const;
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_SCALESIZEHANDLER_H
