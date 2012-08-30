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

#ifndef TRASHCONTROLLERIMPL_H_
#define TRASHCONTROLLERIMPL_H_

#include "../Model/ListCfg.h"
#include "../View/Main.h"
#include <libintl.h>
#include <locale.h>
#include <sstream>
#include "../config.h"

#include "../Model/Env.h"

#include "../Model/MountTable.h"

#include "../View/Trash.h"

#include "ThreadController.h"
#include "../View/EnvEditor.h"
#include "../Mapper/EntryName.h"

#include "../Controller/ControllerAbstract.h"

#include "TrashController.h"


class TrashControllerImpl : public ControllerAbstract, public TrashController {
	Model_Env& env;
	Model_ListCfg* grublistCfg;
	View_Trash* view;
	Mapper_EntryName* entryNameMapper;

	void _refreshView();
	std::list<Model_Entry*> _getDeletableEntries();
public:
	void setListCfg(Model_ListCfg& grublistCfg);
	void setView(View_Trash& scriptAddDlg);
	void setEntryNameMapper(Mapper_EntryName& mapper);

	TrashControllerImpl(Model_Env& env);
	
	void showAction();
	void applyAction();
	
	void showAboutDialog();

	void hideAction();

	void askForDeletionAction();
	void deleteCustomEntriesAction();
};

#endif