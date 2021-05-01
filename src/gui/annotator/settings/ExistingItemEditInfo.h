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

#ifndef KIMAGEANNOTATOR_EXISTINGITEMEDITINFO_H
#define KIMAGEANNOTATOR_EXISTINGITEMEDITINFO_H

namespace kImageAnnotator {

struct ExistingItemEditInfo {
public:
	ExistingItemEditInfo()
	{
		mIsEdit = false;
		mToolType = Tools::Select;
	}

	void startEdit(Tools tool)
	{
		mIsEdit = true;
		mToolType = tool;
	}

	void stopEdit()
	{
		mIsEdit = false;
	}

	bool isEdit() const
	{
		return mIsEdit;
	}

	Tools toolType() const
	{
		return mToolType;
	}

private:
	bool mIsEdit;
	Tools mToolType;
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_EXISTINGITEMEDITINFO_H
