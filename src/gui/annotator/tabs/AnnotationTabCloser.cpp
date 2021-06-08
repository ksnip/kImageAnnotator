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

#include "AnnotationTabCloser.h"

namespace kImageAnnotator {

AnnotationTabCloser::AnnotationTabCloser(QTabWidget *parent) :
	QObject(parent),
	mTabWidget(parent)
{
	Q_ASSERT(mTabWidget != nullptr);
}

void AnnotationTabCloser::closeTabTriggered(int index)
{
	mTabWidget->tabCloseRequested(getValidIndex(index));
}

void AnnotationTabCloser::closeOtherTabsTriggered(int index)
{
	auto selectedWidget = mTabWidget->widget(getValidIndex(index));
	auto tabCount = mTabWidget->count();
	for(auto i = tabCount - 1; i >= 0; i--) {
		auto currentWidget = mTabWidget->widget(i);
		if(currentWidget != selectedWidget) {
			mTabWidget->tabCloseRequested(i);
		}
	}
}

void AnnotationTabCloser::closeAllTabsTriggered()
{
	auto tabCount = mTabWidget->count();
	for(auto i = tabCount - 1; i >= 0; i--) {
		mTabWidget->tabCloseRequested(i);
	}
}

void AnnotationTabCloser::closeAllTabsToLeftTriggered(int index)
{
	for(auto i = index - 1; i >= 0; i--) {
		mTabWidget->tabCloseRequested(i);
	}
}

void AnnotationTabCloser::closeAllTabsToRightTriggered(int index)
{
	auto tabCount = mTabWidget->count();
	for(auto i = tabCount - 1; i > index; i--) {
		mTabWidget->tabCloseRequested(i);
	}
}

int AnnotationTabCloser::getValidIndex(int index) const
{
	return index >= 0 && index < mTabWidget->count() ? index : mTabWidget->currentIndex();
}

} // namespace kImageAnnotator
