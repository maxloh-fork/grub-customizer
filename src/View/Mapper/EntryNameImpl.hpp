/*
 * Copyright (C) 2010-2011 Daniel Richter <danielrichter2007@web.de>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 */

#ifndef ENTRYNAMEIMPL_H_
#define ENTRYNAMEIMPL_H_

#include "../Main.hpp"
#include "../Trait/ViewAware.hpp"
#include "EntryName.hpp"

namespace Gc { namespace View { namespace Mapper { class EntryNameImpl :
	public Gc::View::Mapper::EntryName,
	public Gc::View::Trait::ViewAware<Gc::View::Main>
{
	public:	std::string map(
		std::shared_ptr<Gc::Model::ListCfg::Entry> sourceEntry,
		std::string const& defaultName, bool treatSubmenuAsPlaceholder
	) {
		assert(this->view != nullptr);
		std::string name;
		bool is_other_entries_ph = sourceEntry && treatSubmenuAsPlaceholder ? sourceEntry->type == Gc::Model::ListCfg::Entry::SUBMENU || sourceEntry->type == Gc::Model::ListCfg::Entry::SCRIPT_ROOT : false;
		bool is_plaintext = sourceEntry ? sourceEntry->type == Gc::Model::ListCfg::Entry::PLAINTEXT : false;
		if (is_other_entries_ph) {
			if (sourceEntry->type != Gc::Model::ListCfg::Entry::SCRIPT_ROOT) {
				name = this->view->createNewEntriesPlaceholderString(sourceEntry->name);
			} else {
				name = this->view->createNewEntriesPlaceholderString("");
			}
		} else if (is_plaintext) {
			name = this->view->createPlaintextString();
		} else {
			name = defaultName;
		}
		return name;
	}

};}}}


#endif /* ENTRYNAMEIMPL_H_ */