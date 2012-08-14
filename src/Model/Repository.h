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
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef GRUB_CUSTOMIZER_REPOSITORY_INCLUDED
#define GRUB_CUSTOMIZER_REPOSITORY_INCLUDED
#include "Script.h"
#include "ProxyScriptData.h"
#include "PscriptnameTranslator.h"
#include <sys/stat.h>
#include <dirent.h>
#include <map>
#include "../presenter/commonClass.h"

struct Model_Repository : public std::list<Model_Script>, public CommonClass {
	void load(std::string const& directory, bool is_proxifiedScript_dir);
	Model_Script* getScriptByFilename(std::string const& fileName, bool createScriptIfNotFound = false);
	Model_Script* getScriptByName(std::string const& name);
	Model_Script* getScriptByEntry(Model_Entry const& entry);
	Model_Script const* getScriptByEntry(Model_Entry const& entry) const;
	Model_Script* getCustomScript();
	Model_Script* getNthScript(int pos);
	void deleteAllEntries();
	Model_Script* createScript(std::string const& name, std::string const& fileName, std::string const& content);
	std::map<std::string, Model_Script*> getScriptPathMap();
};

#endif
