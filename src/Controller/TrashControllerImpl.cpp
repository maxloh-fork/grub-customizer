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

#include "TrashControllerImpl.h"

TrashControllerImpl::TrashControllerImpl(Model_Env& env)
	: ControllerAbstract("trash"),
	  grublistCfg(NULL),
	  view(NULL),
	 env(env),
	 entryNameMapper(NULL),
	 deviceDataList(NULL),
	 contentParserFactory(NULL)
{
}

void TrashControllerImpl::_refreshView() {
	assert(this->contentParserFactory != NULL);
	assert(this->deviceDataList != NULL);

	this->view->clear();

	std::list<Model_Entry*> removedEntries = this->grublistCfg->getRemovedEntries();

	for (std::list<Model_Entry*>::iterator iter = removedEntries.begin(); iter != removedEntries.end(); iter++) {
		Model_Script* script = this->grublistCfg->repository.getScriptByEntry(**iter);
		assert(script != NULL);

		std::string name = (*iter)->name;
		name = this->entryNameMapper->map(&**iter, name, script->name);

		View_Model_ListItem<Entry, Script> listItem;
		listItem.name = name;
		listItem.entryPtr = *iter;
		listItem.scriptPtr = NULL;
		listItem.is_placeholder = (*iter)->type == Model_Entry::PLAINTEXT || (*iter)->type == Model_Entry::SUBMENU || (*iter)->type == Model_Entry::SCRIPT_ROOT;
		listItem.scriptName = script->name;
		listItem.isVisible = true;
		listItem.options = Controller_Helper_DeviceInfo::fetch((*iter)->content, *this->contentParserFactory, *this->deviceDataList);

		this->view->addItem(listItem);
	}
}

// returns true, all selected entries are deletable
bool TrashControllerImpl::_isDeletable(std::list<Entry*> const& selectedEntries) {
	for (std::list<Entry*>::const_iterator iter = selectedEntries.begin(); iter != selectedEntries.end(); iter++) {
		if (Model_Entry::fromPtr(*iter).type != Model_Entry::MENUENTRY) {
			continue;
		}
		Model_Script* script = this->grublistCfg->repository.getScriptByEntry(Model_Entry::fromPtr(*iter));
		assert(script != NULL);
		if (!script->isCustomScript) {
			return false;
		}
	}

	return true;
}

void TrashControllerImpl::setListCfg(Model_ListCfg& grublistCfg){
	this->grublistCfg = &grublistCfg;
}

void TrashControllerImpl::setView(View_Trash& scriptAddDlg){
	this->view = &scriptAddDlg;
}

void TrashControllerImpl::setEntryNameMapper(Mapper_EntryName& mapper) {
	this->entryNameMapper = &mapper;
}

void TrashControllerImpl::setDeviceDataList(Model_DeviceDataListInterface& deviceDataList){
	this->deviceDataList = &deviceDataList;
}

void TrashControllerImpl::setContentParserFactory(ContentParserFactory& contentParserFactory) {
	this->contentParserFactory = &contentParserFactory;
}

void TrashControllerImpl::updateAction(std::map<ViewOption, bool> const& viewOptions){
	this->logActionBegin("update");
	try {
		this->view->setOptions(viewOptions);
		this->_refreshView();
	} catch (Exception const& e) {
		this->getAllControllers().errorController->errorAction(e);
	}
	this->logActionEnd();
}

void TrashControllerImpl::applyAction(){
	this->logActionBegin("apply");
	try {
		std::list<Entry*> entries = view->getSelectedEntries();
		this->getAllControllers().mainController->addEntriesAction(entries);
	} catch (Exception const& e) {
		this->getAllControllers().errorController->errorAction(e);
	}
	this->logActionEnd();
}


void TrashControllerImpl::hideAction() {
	this->logActionBegin("hide");
	try {
		this->view->hide();
	} catch (Exception const& e) {
		this->getAllControllers().errorController->errorAction(e);
	}
	this->logActionEnd();
}

void TrashControllerImpl::deleteCustomEntriesAction() {
	this->logActionBegin("delete-custom-entries");
	try {
		std::list<Entry*> deletableEntries = this->view->getSelectedEntries();
		for (std::list<Entry*>::iterator iter = deletableEntries.begin(); iter != deletableEntries.end(); iter++) {
			this->grublistCfg->deleteEntry(Model_Entry::fromPtr(*iter));
		}
		this->_refreshView();
	} catch (Exception const& e) {
		this->getAllControllers().errorController->errorAction(e);
	}
	this->logActionEnd();
}

void TrashControllerImpl::selectEntriesAction(std::list<Entry*> const& entries) {
	this->logActionBegin("select-entries");
	try {
		this->view->selectEntries(entries);
	} catch (Exception const& e) {
		this->getAllControllers().errorController->errorAction(e);
	}
	this->logActionEnd();
}

void TrashControllerImpl::updateSelectionAction(std::list<Entry*> const& selectedEntries) {
	this->logActionBegin("update-selection");
	try {
		if (selectedEntries.size()) {
			this->getAllControllers().mainController->selectRulesAction(std::list<Rule*>());
			this->view->setRestoreButtonSensitivity(true);
			this->view->setDeleteButtonVisibility(this->_isDeletable(selectedEntries));
		} else {
			this->view->setRestoreButtonSensitivity(false);
			this->view->setDeleteButtonVisibility(false);
		}
	} catch (Exception const& e) {
		this->getAllControllers().errorController->errorAction(e);
	}
	this->logActionEnd();
}
