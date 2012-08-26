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

#include "eventListener.h"

EventListener::EventListener(GrubCustomizer& presenter, ControllerCollection& controllers)
	: presenter(presenter), _controllers(controllers)
{
}

void EventListener::rootSelectorCompleted(){
	this->_controllers.mainController->getThreadController().startLoadThread(false);
}


void EventListener::installGrub_request(std::string const& device){
	this->_controllers.installerController->getThreadController().startGrubInstallThread(device);
}

void EventListener::aboutDialog_requested(){
	presenter.showAboutDialog();
}

void EventListener::loadProgressChanged(){
	this->_controllers.mainController->syncLoadStateThreadedAction();
}

void EventListener::saveProgressChanged(){
	this->_controllers.mainController->syncSaveStateThreadedAction();
}

void EventListener::grubInstallCompleted(std::string const& msg){
	this->_controllers.installerController->showMessageAction(msg);
}


void EventListener::fb_resolutions_loaded(){
	this->_controllers.settingsController->getThreadController().updateSettingsDlgResolutionList();
}
