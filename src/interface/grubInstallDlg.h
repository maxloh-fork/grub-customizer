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

#ifndef GRUBINSTALLDLG_H_
#define GRUBINSTALLDLG_H_
#include "evt_grubInstallDlg.h"

/**
 * Interface for dialogs which helps users to install grub into the MBR
 */
class GrubInstallDlg {
public:
	//show this dialog
	virtual void show()=0;
	//show the information that grub has been installed completely
	virtual void showMessageGrubInstallCompleted(std::string const& msg)=0;
	//assign the event listener
	virtual void setEventListener(EventListener_grubInstallDlg& eventListener)=0;
};

#endif