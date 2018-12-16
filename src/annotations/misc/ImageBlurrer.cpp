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

#include "ImageBlurrer.h"

/*
 * Solution provided by liuyanghejerry
 * See: https://stackoverflow.com/questions/3903223/qt4-how-to-blur-qpixmap-image
 */

namespace kImageAnnotator {

QImage ImageBlurrer::blurred(const QImage &image, int radius, bool alphaOnly)
{
	qDebug("blur");
	int tab[] = { 14, 10, 8, 6, 5, 5, 4, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2 };
	int alpha = getAlpha(radius, tab);

	auto result = image.convertToFormat(QImage::Format_ARGB32_Premultiplied);
	auto r1 = image.rect().top();
	auto r2 = image.rect().bottom();
	auto c1 = image.rect().left();
	auto c2 = image.rect().right();

	auto bpl = result.bytesPerLine();
	int rgba[4];
	unsigned char *p;

	int i1 = 0;
	int i2 = 3;

	if (alphaOnly) {
		i1 = i2 = 3;
	}

	for (auto col = c1; col <= c2; col++) {
		p = result.scanLine(r1) + col * 4;
		for (auto i = i1; i <= i2; i++) {
			rgba[i] = p[i] << 4;
		}

		p += bpl;
		for (auto j = r1; j < r2; j++, p += bpl) {
			for (auto i = i1; i <= i2; i++) {
				p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
			}
		}
	}

	for (auto row = r1; row <= r2; row++) {
		p = result.scanLine(row) + c1 * 4;
		for (auto i = i1; i <= i2; i++) {
			rgba[i] = p[i] << 4;
		}

		p += 4;
		for (auto j = c1; j < c2; j++, p += 4) {
			for (auto i = i1; i <= i2; i++) {
				p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
			}
		}
	}

	for (auto col = c1; col <= c2; col++) {
		p = result.scanLine(r2) + col * 4;
		for (auto i = i1; i <= i2; i++) {
			rgba[i] = p[i] << 4;
		}

		p -= bpl;
		for (auto j = r1; j < r2; j++, p -= bpl) {
			for (auto i = i1; i <= i2; i++) {
				p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
			}
		}
	}

	for (auto row = r1; row <= r2; row++) {
		p = result.scanLine(row) + c2 * 4;
		for (auto i = i1; i <= i2; i++) {
			rgba[i] = p[i] << 4;
		}

		p -= 4;
		for (auto j = c1; j < c2; j++, p -= 4) {
			for (auto i = i1; i <= i2; i++) {
				p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
			}
		}
	}

	return result;
}

int ImageBlurrer::getAlpha(int radius, const int *tab) const
{
	return (radius < 1) ? 16 : (radius > 17) ? 1 : tab[radius - 1];
}

} // namespace kImageAnnotator
