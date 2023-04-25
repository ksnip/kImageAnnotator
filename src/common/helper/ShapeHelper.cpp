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

#include <QtGui/QPainterPath>
#include <QtMath>
#include "ShapeHelper.h"

namespace kImageAnnotator {

QPointF ShapeHelper::rectTopLeftWithOffset(const QRectF &rect, int offset)
{
	auto xOffset = invertOffsetIfLeftSmallerThenRight(rect, offset);
	auto yOffset = invertOffsetIfTopSmallerThenBottom(rect, offset);
	return { rect.topLeft().x() + xOffset, rect.topLeft().y() + yOffset };
}

QPointF ShapeHelper::rectTop(const QRectF &rect)
{
	return { rect.center().x(), rect.top() };
}

QPointF ShapeHelper::rectTopWithOffset(const QRectF &rect, int offset)
{
	offset = invertOffsetIfTopSmallerThenBottom(rect, offset);
	return { rect.center().x(), rect.top() + offset };
}

QPointF ShapeHelper::rectTopRightWithOffset(const QRectF &rect, int offset)
{
	auto xOffset = invertOffsetIfLeftSmallerThenRight(rect, -offset);
	auto yOffset = invertOffsetIfTopSmallerThenBottom(rect, offset);
	return { rect.topRight().x() + xOffset, rect.topRight().y() + yOffset };
}

QPointF ShapeHelper::rectRight(const QRectF &rect)
{
	return { rect.right(), rect.center().y() };
}

QPointF ShapeHelper::rectRightWithOffset(const QRectF &rect, int offset)
{
	offset = invertOffsetIfLeftSmallerThenRight(rect, -offset);
	return { rect.right() + offset, rect.center().y() };
}

QPointF ShapeHelper::rectBottomRightWithOffset(const QRectF &rect, int offset)
{
	auto xOffset = invertOffsetIfLeftSmallerThenRight(rect, -offset);
	auto yOffset = invertOffsetIfTopSmallerThenBottom(rect, -offset);
	return { rect.bottomRight().x() + xOffset, rect.bottomRight().y() + yOffset };
}

QPointF ShapeHelper::rectBottom(const QRectF &rect)
{
	return { rect.center().x(), rect.bottom() };
}

QPointF ShapeHelper::rectBottomWithOffset(const QRectF &rect, int offset)
{
	offset = invertOffsetIfTopSmallerThenBottom(rect, -offset);
	return { rect.center().x(), rect.bottom() + offset };
}

QPointF ShapeHelper::rectBottomLeftWithOffset(const QRectF &rect, int offset)
{
	auto xOffset = invertOffsetIfLeftSmallerThenRight(rect, offset);
	auto yOffset = invertOffsetIfTopSmallerThenBottom(rect, -offset);
	return { rect.bottomLeft().x() + xOffset, rect.bottomLeft().y() + yOffset };
}

QPointF ShapeHelper::rectLeft(const QRectF &rect)
{
	return { rect.left(), rect.center().y() };
}

QPointF ShapeHelper::rectLeftWithOffset(const QRectF &rect, int offset)
{
	offset = invertOffsetIfLeftSmallerThenRight(rect, offset);
	return { rect.left() + offset, rect.center().y() };
}

QLineF ShapeHelper::extendLine(const QLineF &line, int extendBy)
{
	QLineF newLine(line.p2().x(), line.p2().y(), line.p1().x(), line.p1().y());
	newLine.setLength(newLine.length() + extendBy / 2);
	newLine.setLine(newLine.p2().x(), newLine.p2().y(), newLine.p1().x(), newLine.p1().y());
	newLine.setLength(newLine.length() + extendBy / 2);
	return newLine;
}

QPointF ShapeHelper::rectPointAtIndex(const QRectF &rect, int index)
{
	if (index == 0) {
		return rect.topLeft();
	} else if (index == 1) {
		return ShapeHelper::rectTop(rect);
	} else if (index == 2) {
		return rect.topRight();
	} else if (index == 3) {
		return ShapeHelper::rectRight(rect);
	} else if (index == 4) {
		return rect.bottomRight();
	} else if (index == 5) {
		return ShapeHelper::rectBottom(rect);
	} else if (index == 6) {
		return rect.bottomLeft();
	} else if (index == 7) {
		return ShapeHelper::rectLeft(rect);
	} else {
		qCritical("Invalid rectangle index provided, returning empty point.");
		return {};
	}
}

QRectF ShapeHelper::setRectPointAtIndex(const QRectF &rect, int index, const QPointF &pos, bool keepAspectRatio)
{
	auto updatedRect = rect;
	if (index == 0) {
		if (keepAspectRatio) {
			const auto xDif = updatedRect.topLeft().x() - pos.x();
			const auto yDif = updatedRect.topLeft().y() - pos.y();
			const auto min = qMin(xDif, yDif);
			const auto newX = updatedRect.topLeft().x() - min;
			const auto newY = updatedRect.topLeft().y() - min;
			auto newTopLeft = QPointF(newX, newY);
			
			updatedRect.setTopLeft(newTopLeft);
		} else {
			updatedRect.setTopLeft(pos);
		}
	} else if (index == 1) {
		updatedRect.setTop(pos.y());
	} else if (index == 2) {
		if (keepAspectRatio) {
			const auto xDif = pos.x() - updatedRect.topRight().x();
			const auto yDif = updatedRect.topRight().y() - pos.y();
			const auto min = qMin(xDif, yDif);
			const auto newX = updatedRect.topRight().x() + min;
			const auto newY = updatedRect.topRight().y() - min;
			auto newTopRight = QPointF(newX, newY);
			
			updatedRect.setTopRight(newTopRight);
		} else {
			updatedRect.setTopRight(pos);
		}
	} else if (index == 3) {
		updatedRect.setRight(pos.x());
	} else if (index == 4) {
		if (keepAspectRatio) {
			const auto xDif = pos.x() - updatedRect.bottomRight().x();
			const auto yDif = pos.y() - updatedRect.bottomRight().y();
			const auto min = qMin(xDif, yDif);
			const auto newX = updatedRect.bottomRight().x() + min;
			const auto newY = updatedRect.bottomRight().y() + min;
			auto newBottomRight = QPointF(newX, newY);
			
			updatedRect.setBottomRight(newBottomRight);
		} else {
			updatedRect.setBottomRight(pos);
		}
	} else if (index == 5) {
		updatedRect.setBottom(pos.y());
	} else if (index == 6) {
		if (keepAspectRatio) {
			const auto xDif = updatedRect.bottomLeft().x() - pos.x();
			const auto yDif = pos.y() - updatedRect.bottomLeft().y();
			const auto min = qMin(xDif, yDif);
			const auto newX = updatedRect.bottomLeft().x() - min;
			const auto newY = updatedRect.bottomLeft().y() + min;
			auto newBottomLeft = QPointF(newX, newY);

			updatedRect.setBottomLeft(newBottomLeft);
		} else {
			updatedRect.setBottomLeft(pos);
		}
	} else if (index == 7) {
		updatedRect.setLeft(pos.x());
	} else {
		qCritical("Invalid rectangle index provided, returning unchanged rectangle.");
	}
	return updatedRect;
}

QPainterPath ShapeHelper::smoothOut(const QPainterPath &path, int smoothFactor)
{
	auto points = getPathPoints(path, smoothFactor);

	// Don't proceed if we only have 3 or less points.
	if (points.count() < 3) {
		return path;
	}

	return createSmoothPath(points);
}

QPainterPath ShapeHelper::createSmoothPath(const QList<QPointF> &points)
{
	QPointF point1, point2;
	QPainterPath smoothPath;

	smoothPath.moveTo(points[0]);
	smoothPath.lineTo(points[1]);
	for (auto i = 2; i < points.count() - 2; i++) {
		point1 = getBeginOfRounding(points[i], points[i + 1]);
		smoothPath.quadTo(points[i], point1);
		point2 = getEndOfRounding(points[i], points[i + 1]);
		smoothPath.lineTo(point2);
	}
	smoothPath.lineTo(points[points.count() - 1]);
	return smoothPath;
}

QList<QPointF> ShapeHelper::getPathPoints(const QPainterPath &path, int smootFactor)
{
	QList<QPointF> points;
	QPointF p;
	for (auto i = 0; i < path.elementCount() - 1; i++) {
		p = QPointF(path.elementAt(i).x, path.elementAt(i).y);

		// Except for first and last points, check what the distance between two
		// points is and if its less the min, don't add them to the list.
		if (points.count() > 1 && (i < path.elementCount() - 2) && (MathHelper::distanceBetweenPoints(points.last(), p) < smootFactor)) {
			continue;
		}
		points.append(p);
	}
	return points;
}

int ShapeHelper::invertOffsetIfLeftSmallerThenRight(const QRectF &rect, int xOffset)
{
	if (rect.left() < rect.right()) {
		xOffset *= -1;
	}
	return xOffset;
}

int ShapeHelper::invertOffsetIfTopSmallerThenBottom(const QRectF &rect, int yOffset)
{
	if (rect.top() < rect.bottom()) {
		yOffset *= -1;
	}
	return yOffset;
}

QPointF ShapeHelper::getBeginOfRounding(const QPointF &point1, const QPointF &point2)
{
	QPointF startPoint;
	auto rat = getRoundingRate(point1, point2);
	startPoint.setX((1.0 - rat) * point1.x() + rat * point2.x());
	startPoint.setY((1.0 - rat) * point1.y() + rat * point2.y());
	return startPoint;
}

QPointF ShapeHelper::getEndOfRounding(const QPointF &point1, const QPointF &point2)
{
	QPointF endPoint;
	auto rat = getRoundingRate(point1, point2);
	endPoint.setX(rat * point1.x() + (1.0 - rat) * point2.x());
	endPoint.setY(rat * point1.y() + (1.0 - rat) * point2.y());
	return endPoint;
}

double ShapeHelper::getRoundingRate(const QPointF &point1, const QPointF &point2)
{
	auto rat = 10.0 / MathHelper::distanceBetweenPoints(point1, point2);
	if (rat > 0.5) {
		rat = 0.5;
	}
	return rat;
}

QPointF ShapeHelper::intersectionBetweenRectAndLineFromCenter(const QLineF &line, const QRectF &rect)
{
	QLineF leftLine(rect.bottomLeft(), rect.topLeft());
	QLineF topLine(rect.topLeft(), rect.topRight());
	QLineF rightLine(rect.topRight(), rect.bottomRight());
	QLineF bottomLine(rect.bottomLeft(), rect.bottomRight());

	QPointF intersectionPoint;
	if(linesIntersect(line, leftLine, intersectionPoint)) {
		return intersectionPoint;
	} else if(linesIntersect(line, topLine, intersectionPoint)) {
		return intersectionPoint;
	} else if(linesIntersect(line, rightLine, intersectionPoint)) {
		return intersectionPoint;
	} else if(linesIntersect(line, bottomLine, intersectionPoint)) {
		return intersectionPoint;
	}
	return intersectionPoint;
}

bool ShapeHelper::linesIntersect(const QLineF &line1, const QLineF &line2, QPointF &intersection)
{
	return line1.intersect(line2, &intersection) == QLineF::BoundedIntersection;
}

} // namespace kImageAnnotator
