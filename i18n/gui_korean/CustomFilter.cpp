/*  Copyright (C) 2010-2012  kaosu (qiupf2000@gmail.com)
 *  This file is part of the Interactive Text Hooker.

 *  Interactive Text Hooker is free software: you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License as published
 *  by the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "CustomFilter.h"

void CustomFilter::Insert(WORD number)
{
	set.insert(number);
}

void CustomFilter::Erase(WORD number)
{
	set.erase(number);
}

bool CustomFilter::Find(WORD number) const
{
	return set.find(number) != set.end();
}

void CustomFilter::Clear()
{
	set.clear();
}

void CustomFilter::Traverse(CustomFilterCallBack callback, PVOID param)
{
	for (auto ch = set.begin(); ch != set.end(); ++ch)
		callback(*ch, param);
}
