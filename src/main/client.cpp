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

#include <iostream>

#include "../Bootstrap/Regex.hpp"
#include "../Bootstrap/Thread.hpp"
#include "../Bootstrap/View.hpp"
#include "../Bootstrap/Application.hpp"
#include "../lib/ArrayStructure.hpp"
#include "../lib/ContentParser/Chainloader.hpp"
#include "../lib/ContentParser/FactoryImpl.hpp"
#include "../lib/ContentParser/Linux.hpp"
#include "../lib/ContentParser/LinuxIso.hpp"
#include "../lib/ContentParser/Memtest.hpp"
#include "../lib/Logger/Stream.hpp"
#include "../Mapper/EntryNameImpl.hpp"
#include "../Model/Env.hpp"
#include "../Model/ThemeManager.hpp"
#include "../config.hpp"
#include "../Controller/AboutController.hpp"
#include "../Controller/EntryEditController.hpp"
#include "../Controller/EnvEditorController.hpp"
#include "../Controller/ErrorController.hpp"
#include "../Controller/InstallerController.hpp"
#include "../Controller/MainController.hpp"
#include "../Controller/SettingsController.hpp"
#include "../Controller/ThemeController.hpp"
#include "../Controller/TrashController.hpp"



int main(int argc, char** argv){
	if (getuid() != 0 && (argc == 1 || argv[1] != std::string("no-fork"))) {
		return system((std::string("pkexec ") + argv[0] + (argc == 2 ? std::string(" ") + argv[1] : "") + " no-fork").c_str());
	}
	setlocale( LC_ALL, "");
	bindtextdomain( "grub-customizer", LOCALEDIR);
	textdomain( "grub-customizer" );

	Logger_Stream logger(std::cout);

	try {
		Model_Env env;

		Bootstrap_Application application(argc, argv);
		Bootstrap_View view;
		Bootstrap_Thread thread;
		Bootstrap_Regex regex;

		Model_ListCfg listcfg;
		Model_SettingsManagerData settings;
		Model_SettingsManagerData settingsOnDisk;
		Model_Installer installer;
		Model_MountTable mountTable;
		Model_ListCfg savedListCfg;
		Model_FbResolutionsGetter fbResolutionsGetter;
		Model_DeviceDataList deviceDataList;
		ContentParser_FactoryImpl contentParserFactory;
		Mapper_EntryNameImpl entryNameMapper;
		Model_ThemeManager themeManager;
		Model_DeviceMap deviceMap;

		deviceMap.setRegexEngine(*regex.engine);

		entryNameMapper.setView(*view.main);

		view.setDeviceDataList(deviceDataList);

		EntryEditController entryEditController;
		entryEditController.setContentParserFactory(contentParserFactory);
		entryEditController.setView(*view.entryEditor);
		entryEditController.setDeviceDataList(deviceDataList);
		entryEditController.setListCfg(listcfg);
		entryEditController.setApplicationObject(application.applicationObject);

		MainController mainController;
		mainController.setListCfg(listcfg);
		mainController.setSettingsManager(settings);
		mainController.setSettingsBuffer(settingsOnDisk);
		mainController.setSavedListCfg(savedListCfg);
		mainController.setFbResolutionsGetter(fbResolutionsGetter);
		mainController.setDeviceDataList(deviceDataList);
		mainController.setMountTable(mountTable);
		mainController.setContentParserFactory(contentParserFactory);
		mainController.setView(*view.main);
		mainController.setEntryNameMapper(entryNameMapper);
		mainController.setApplicationObject(application.applicationObject);

		SettingsController settingsController;
		settingsController.setListCfg(listcfg);
		settingsController.setView(*view.settings);
		settingsController.setSettingsManager(settings);
		settingsController.setFbResolutionsGetter(fbResolutionsGetter);
		settingsController.setApplicationObject(application.applicationObject);

		EnvEditorController envEditController;
		envEditController.setMountTable(mountTable);
		envEditController.setView(*view.envEditor);
		envEditController.setDeviceMap(deviceMap);
		envEditController.setApplicationObject(application.applicationObject);

		TrashController trashController;
		trashController.setEntryNameMapper(entryNameMapper);
		trashController.setListCfg(listcfg);
		trashController.setDeviceDataList(deviceDataList);
		trashController.setContentParserFactory(contentParserFactory);
		trashController.setView(*view.trash);
		trashController.setApplicationObject(application.applicationObject);

		InstallerController installController;
		installController.setInstaller(installer);
		installController.setView(*view.installer);
		installController.setApplicationObject(application.applicationObject);

		AboutController aboutController;
		aboutController.setView(*view.about);
		aboutController.setApplicationObject(application.applicationObject);

		ErrorController errorController;
		errorController.setView(*view.error);
		errorController.setApplicationObject(application.applicationObject);

		ThemeController themeController;
		themeController.setView(*view.theme);
		themeController.setThemeManager(themeManager);
		themeController.setSettingsManager(settings);
		themeController.setListCfg(listcfg);
		themeController.setApplicationObject(application.applicationObject);

		mainController.setThreadHelper(*thread.threadHelper);
		settingsController.setThreadHelper(*thread.threadHelper);
		installController.setThreadHelper(*thread.threadHelper);
		errorController.setThreadHelper(*thread.threadHelper);
		entryEditController.setThreadHelper(*thread.threadHelper);
		themeController.setThreadHelper(*thread.threadHelper);

		//assign logger
		listcfg.setLogger(logger);
		view.main->setLogger(logger);
		settings.setLogger(logger);
		settingsOnDisk.setLogger(logger);
		installer.setLogger(logger);
		view.installer->setLogger(logger);
		view.trash->setLogger(logger);
		view.entryEditor->setLogger(logger);
		mountTable.setLogger(logger);
		savedListCfg.setLogger(logger);
		fbResolutionsGetter.setLogger(logger);
		view.settings->setLogger(logger);
		deviceDataList.setLogger(logger);
		view.about->setLogger(logger);
		thread.mutex1->setLogger(logger);
		thread.mutex2->setLogger(logger);
		env.setLogger(logger);
		view.envEditor->setLogger(logger);
		mainController.setLogger(logger);
		entryEditController.setLogger(logger);
		settingsController.setLogger(logger);
		envEditController.setLogger(logger);
		trashController.setLogger(logger);
		errorController.setLogger(logger);
		installController.setLogger(logger);
		aboutController.setLogger(logger);
		view.theme->setLogger(logger);
		themeController.setLogger(logger);
		thread.threadHelper->setLogger(logger);

		// configure logger
		logger.setLogLevel(Logger_Stream::LOG_EVENT);
		if (argc > 1) {
			std::string logParam = argv[1];
			if (logParam == "debug") {
				logger.setLogLevel(Logger_Stream::LOG_DEBUG_ONLY);
			} else if (logParam == "log-important") {
				logger.setLogLevel(Logger_Stream::LOG_IMPORTANT);
			} else if (logParam == "quiet") {
				logger.setLogLevel(Logger_Stream::LOG_NOTHING);
			} else if (logParam == "verbose") {
				logger.setLogLevel(Logger_Stream::LOG_VERBOSE);
			}
		}

		//configure contentParser factory
		ContentParser_Linux linuxParser(deviceMap);
		ContentParser_LinuxIso linuxIsoParser(deviceMap);
		ContentParser_Chainloader chainloadParser(deviceMap);
		ContentParser_Memtest memtestParser(deviceMap);

		contentParserFactory.registerParser(linuxParser, gettext("Linux"));
		contentParserFactory.registerParser(linuxIsoParser, gettext("Linux-ISO"));
		contentParserFactory.registerParser(chainloadParser, gettext("Chainloader"));
		contentParserFactory.registerParser(memtestParser, gettext("Memtest"));

		linuxParser.setRegexEngine(*regex.engine);
		linuxIsoParser.setRegexEngine(*regex.engine);
		chainloadParser.setRegexEngine(*regex.engine);
		memtestParser.setRegexEngine(*regex.engine);

		view.entryEditor->setAvailableEntryTypes(contentParserFactory.getNames());

		//set env
		listcfg.setEnv(env);
		savedListCfg.setEnv(env);
		settings.setEnv(env);
		settingsOnDisk.setEnv(env);
		installer.setEnv(env);
		themeManager.setEnv(env);
		entryEditController.setEnv(env);
		mainController.setEnv(env);
		settingsController.setEnv(env);
		envEditController.setEnv(env);
		trashController.setEnv(env);
		installController.setEnv(env);
		themeController.setEnv(env);
		deviceMap.setEnv(env);

		//set mutex
		listcfg.setMutex(*thread.mutex1);
		savedListCfg.setMutex(*thread.mutex2);

		mainController.initAction();
		errorController.setApplicationStarted(true);

		application.applicationObject->run();
	} catch (Exception const& e) {
		logger.log(e, Logger::ERROR);
		return 1;
	}
}

