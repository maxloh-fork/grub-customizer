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

#include "EntryEditControllerImpl.h"

EntryEditControllerImpl::EntryEditControllerImpl(Model_Env& env)
	: grublistCfg(NULL),
	 env(env), contentParserFactory(NULL), currentContentParser(NULL),
	 deviceDataList(NULL), view(NULL)
{
}

void EntryEditControllerImpl::setListCfg(Model_ListCfg& grublistCfg){
	this->grublistCfg = &grublistCfg;
}

void EntryEditControllerImpl::setContentParserFactory(ContentParserFactory& contentParserFactory) {
	this->contentParserFactory = &contentParserFactory;
}

void EntryEditControllerImpl::setDeviceDataList(Model_DeviceDataList& deviceDataList){
	this->deviceDataList = &deviceDataList;
}

void EntryEditControllerImpl::setView(View_EntryEditor& view) {
	this->view = &view;
}


void EntryEditControllerImpl::applyAction() {
	Model_Rule* rulePtr = static_cast<Model_Rule*>(this->view->getRulePtr());
	bool isAdded = false;
	if (rulePtr == NULL) { // insert
		Model_Script* script = this->grublistCfg->repository.getCustomScript();
		script->entries().push_back(Model_Entry("new", "", ""));

		Model_Rule newRule(script->entries().back(), true, *script);

		std::list<Model_Proxy*> proxies = this->grublistCfg->proxies.getProxiesByScript(*script);
		for (std::list<Model_Proxy*>::iterator proxyIter = proxies.begin(); proxyIter != proxies.end(); proxyIter++) {
			(*proxyIter)->rules.push_back(newRule);
			newRule.isVisible = false; // if there are more rules of this type, add them invisible
		}
		assert(proxies.size() != 0); // there should at least one proxy related to the custom script
		rulePtr = &proxies.front()->rules.back();
		isAdded = true;
	} else { // update
		Model_Script* script = this->grublistCfg->repository.getScriptByEntry(*rulePtr->dataSource);
		assert(script != NULL);

		if (!script->isCustomScript) {
			script = this->grublistCfg->repository.getCustomScript();
			script->entries().push_back(*rulePtr->dataSource);

			Model_Rule ruleCopy = *rulePtr;
			rulePtr->setVisibility(false);
			ruleCopy.dataSource = &script->entries().back();
			Model_Proxy* proxy = this->grublistCfg->proxies.getProxyByRule(rulePtr);
			std::list<Model_Rule>& ruleList = proxy->getRuleList(proxy->getParentRule(rulePtr));

			Model_Rule dummySubmenu(Model_Rule::SUBMENU, std::list<std::string>(), "DUMMY", true);
			dummySubmenu.subRules.push_back(ruleCopy);
			std::list<Model_Rule>::iterator iter = ruleList.insert(proxy->getListIterator(*rulePtr, ruleList), dummySubmenu);

			Model_Rule& insertedRule = iter->subRules.back();
			rulePtr = &this->grublistCfg->moveRule(&insertedRule, -1);

			std::list<Model_Proxy*> proxies = this->grublistCfg->proxies.getProxiesByScript(*script);
			for (std::list<Model_Proxy*>::iterator proxyIter = proxies.begin(); proxyIter != proxies.end(); proxyIter++) {
				if (!(*proxyIter)->getRuleByEntry(*rulePtr->dataSource, (*proxyIter)->rules, rulePtr->type)) {
					(*proxyIter)->rules.push_back(Model_Rule(*rulePtr->dataSource, false, *script));
				}
			}
		}
	}

	std::string newCode = this->view->getSourcecode();
	rulePtr->dataSource->content = newCode;
	rulePtr->dataSource->isModified = true;

	this->getAllControllers().masterclass_deprecated->setModificationsUnsaved(true);
	this->getAllControllers().masterclass_deprecated->syncListView_load();

	this->getAllControllers().masterclass_deprecated->selectRule(rulePtr, isAdded);

	this->currentContentParser = NULL;
}

void EntryEditControllerImpl::showAction(void* rule) {
	// FIXME: this action must be used to show this dialog
	this->view->setRulePtr(rule);
	this->view->setSourcecode(((Model_Rule*)rule)->dataSource->content);
	this->syncEntryEditDlg(false);
	this->view->show();
}

void EntryEditControllerImpl::syncEntryEditDlg(bool useOptionsAsSource) {
	try {
		if (useOptionsAsSource) {
			assert(this->currentContentParser != NULL);
			this->currentContentParser->setOptions(this->view->getOptions());
			this->view->setSourcecode(this->currentContentParser->buildSource());
		} else {
			this->currentContentParser = this->contentParserFactory->create(this->view->getSourcecode());
			this->view->setOptions(this->currentContentParser->getOptions());
		}
		this->view->selectType(this->contentParserFactory->getNameByInstance(*this->currentContentParser));
	} catch (ContentParserFactory::Exception const& e) {
		this->view->selectType("");
		this->view->setOptions(std::map<std::string, std::string>());
	}
}


void EntryEditControllerImpl::syncOptionsAction() {
	this->syncEntryEditDlg(false);
}
void EntryEditControllerImpl::syncSourceAction() {
	this->syncEntryEditDlg(true);
}

void EntryEditControllerImpl::switchTypeAction(std::string const& newType) {
	std::string partition;
	if (this->deviceDataList->size()) {
		partition = this->deviceDataList->begin()->second["UUID"];
	}

	if ((this->currentContentParser || partition != "") && newType != "") {
		if (this->currentContentParser) {
			partition = this->currentContentParser->getOption("partition_uuid");
		}
		this->currentContentParser = this->contentParserFactory->createByName(newType);
		this->currentContentParser->buildDefaultEntry(partition);

		// sync
		this->view->setSourcecode(this->currentContentParser->buildSource());
		this->view->setOptions(this->currentContentParser->getOptions());
	} else {
		this->view->setOptions(std::map<std::string, std::string>());
		this->view->setSourcecode("");
	}
}

void EntryEditControllerImpl::showCreatorAction() {
	this->view->setRulePtr(NULL);
	this->view->setSourcecode("");
	this->view->selectType("");
	this->view->setOptions(std::map<std::string, std::string>());
	this->view->show();
}
