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

#include "AttachedSeparator.h"

namespace kImageAnnotator {

AttachedSeparator::AttachedSeparator(SettingsPickerWidget *target) :
	QFrame(target),
	mTarget(target)
{
	Q_ASSERT(mTarget != nullptr);

	setContentsMargins(0, 3, 0, 3);

	setFrameShape(QFrame::VLine);
	setFrameShadow(QFrame::Sunken);

	connect(mTarget, &SettingsPickerWidget::visibilityChanged, this, &AttachedSeparator::targetVisibilityChanged);

	updateVisibility();
}

void AttachedSeparator::targetVisibilityChanged(bool visible)
{
	setVisible(visible && isEnabled());
}

void AttachedSeparator::changeEvent(QEvent *event)
{
	if(event->type() == QEvent::EnabledChange) {
		updateVisibility();
	}
	QFrame::changeEvent(event);
}

void AttachedSeparator::updateVisibility()
{
	targetVisibilityChanged(mTarget->isVisible());
}

} // namespace kImageAnnotator