/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KIMAGEANNOTATOR_ANNOTATIONTABCLOSER_H
#define KIMAGEANNOTATOR_ANNOTATIONTABCLOSER_H

#include <QTabWidget>

#include <QtWidgets/QTabWidget>

namespace kImageAnnotator {

class AnnotationTabCloser : public QObject
{
	Q_OBJECT
public:
	explicit AnnotationTabCloser(QTabWidget *tabWidget);
	~AnnotationTabCloser() override = default;

public slots:
	void closeTabTriggered(int index);
	void closeOtherTabsTriggered(int index);
	void closeAllTabsTriggered();
	void closeAllTabsToLeftTriggered(int index);
	void closeAllTabsToRightTriggered(int index);


private:
	QTabWidget *mTabWidget;

	int getValidIndex(int index) const;
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_ANNOTATIONTABCLOSER_H
