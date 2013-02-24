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

#ifndef SETTING_DLG_GTK_INCLUDED
#define SETTING_DLG_GTK_INCLUDED
#include <gtkmm.h>
#include "../Settings.h"
#include <libintl.h>
#include "../ColorChooser.h"
#include <string>
#include "../../lib/CommonClass.h"
#include "../../Controller/SettingsController.h"
#include "../../lib/assert.h"


//a gtkmm combobox with colorful foreground and background. useful to choose an item of a predefined color set
class View_Gtk_Settings_ColorChooser : public Gtk::ComboBox, public View_ColorChooser {
	struct Columns : public Gtk::TreeModelColumnRecord {
		Gtk::TreeModelColumn<Glib::ustring> name;
		Gtk::TreeModelColumn<Glib::ustring> idName;
		Gtk::TreeModelColumn<Glib::ustring> colorCode_background;
		Gtk::TreeModelColumn<Glib::ustring> colorCode_foreground;
		Columns();
	};
	Columns columns;
	Glib::RefPtr<Gtk::ListStore> refListStore;
	public:
	View_Gtk_Settings_ColorChooser();
	void addColor(std::string const& codeName, std::string const& outputName, std::string const& cell_background, std::string const& cell_foreground);
	void selectColor(std::string const& codeName);
	std::string getSelectedColor() const;
	Pango::Color getSelectedColorAsPangoObject() const;
	bool event_lock;
};

//a color chooser with predefined colors for grub
class GrubColorChooser : public View_Gtk_Settings_ColorChooser {
public:
	GrubColorChooser(bool blackIsTransparent = false);
};

class View_Gtk_Settings : public Gtk::Dialog, public View_Settings, public CommonClass {
	struct AdvancedSettingsTreeModel : public Gtk::TreeModelColumnRecord {
		Gtk::TreeModelColumn<bool> active;
		Gtk::TreeModelColumn<Glib::ustring> name;
		Gtk::TreeModelColumn<Glib::ustring> old_name;
		Gtk::TreeModelColumn<Glib::ustring> value;
		AdvancedSettingsTreeModel();
	};
	struct CustomOption_obj : public CustomOption {
		CustomOption_obj(std::string name, std::string old_name, std::string value, bool isActive);
	};
	AdvancedSettingsTreeModel asTreeModel;
	Glib::RefPtr<Gtk::ListStore> refAsListStore;
	bool event_lock;
	SettingsController* eventListener;
	
	Gtk::Notebook tabbox;
	Gtk::ScrolledWindow scrAllEntries;
	Gtk::TreeView tvAllEntries;
	Gtk::VBox vbAllEntries;
	Gtk::HBox hbAllEntriesControl;
	Gtk::Button bttAddCustomEntry, bttRemoveCustomEntry;

	Gtk::VBox vbCommonSettings, vbAppearanceSettings;
	Gtk::Alignment alignCommonSettings;
	
	Pango::AttrList attrDefaultEntry;
	Pango::Attribute aDefaultEntry;
	//default entry group
	Gtk::Frame groupDefaultEntry;
	Gtk::Alignment alignDefaultEntry;
	Gtk::Label lblDefaultEntry;
	//Gtk::Table tblDefaultEntry;
	Gtk::RadioButton rbDefPredefined, rbDefSaved;
	Gtk::RadioButtonGroup rbgDefEntry;
	Gtk::VBox vbDefaultEntry;
	Gtk::HBox hbDefPredefined;
	//Gtk::SpinButton spDefPosition;
	Gtk::ComboBoxText cbDefEntry;
	std::map<int, std::string> defEntryValueMapping;
	
	//view group
	Gtk::Frame groupView;
	Gtk::Alignment alignView;
	Gtk::Label lblView;
	Gtk::VBox vbView;
	Gtk::CheckButton chkShowMenu, chkOsProber;
	Gtk::HBox hbTimeout;
	Gtk::Label lblTimeout;
	Gtk::SpinButton spTimeout;
	Gtk::Label lblTimeout2;
	
	//kernel parameters
	Gtk::Frame groupKernelParams;
	Gtk::Alignment alignKernelParams;
	Gtk::Label lblKernelParams;
	Gtk::VBox vbKernelParams;
	Gtk::Entry txtKernelParams;
	Gtk::CheckButton chkGenerateRecovery;
	
	//screen resolution
	Gtk::Alignment alignResolutionAndTheme;
	Gtk::HBox hbResolutionAndTheme;
	Gtk::HBox hbResolution;
	Gtk::CheckButton chkResolution;
	Gtk::ComboBoxText cbResolution;
	
	//theme chooser
	Gtk::HBox hbTheme;
	Gtk::Label lblTheme;
	Gtk::ComboBox cbTheme;

	//color chooser
	Gtk::Frame groupColorChooser;
	Gtk::Alignment alignColorChooser;
	Gtk::Label lblColorChooser;
	Gtk::Table tblColorChooser;
	Gtk::Label lblforegroundColor, lblBackgroundColor, lblNormalColor, lblHighlightColor;
	GrubColorChooser gccNormalForeground, gccNormalBackground, gccHighlightForeground, gccHighlightBackground;

	//font selection and background image group
	Gtk::HBox hbFontAndBgImage;

	//font selection
	Gtk::Frame groupFont;
	Gtk::Label lblFont;
	Gtk::Alignment alignFont;
	Gtk::FontButton bttFont;
	Gtk::HBox hbFont;
	Gtk::Button bttRemoveFont;
	Gtk::Image imgRemoveFont;

	//background image
	Gtk::Frame groupBackgroundImage;
	Gtk::Alignment alignBackgroundImage;
	Gtk::Label lblBackgroundImage, lblBackgroundRequiredInfo;
	Gtk::VBox vbBackgroundImage;
	Gtk::HBox hbBackgroundImage;
	Gtk::FileChooserButton fcBackgroundImage;
	Gtk::DrawingArea drwBackgroundPreview;
	Glib::ustring backgroundImagePath;
	std::list<std::string> previewEntryTitles;
	Glib::Mutex previewEntryTitles_mutex;
	Gtk::HBox hbImgBtts;
	Gtk::VBox vbButtons;
	Gtk::Button bttCopyBackground, bttRemoveBackground;
	Gtk::Image imgRemoveBackground;



	void signal_setting_row_changed(const Gtk::TreeModel::Path& path, const Gtk::TreeModel::iterator& iter);
	void signal_add_row_button_clicked();
	void signal_remove_row_button_clicked();
	void signal_default_entry_predefined_toggeled();
	void signal_default_entry_saved_toggeled();
	void signal_default_entry_changed();
	void signal_showMenu_toggled();
	void signal_osProber_toggled();
	void signal_timeout_changed();
	void signal_kernelparams_changed();
	void signal_recovery_toggled();
	void signal_chkResolution_toggled();
	void signal_resolution_selected();
	void signal_color_changed(View_Gtk_Settings_ColorChooser& caller);
	void signal_font_changed();
	void signal_font_removed();
	void signal_other_image_chosen();
	void signal_bttRemoveBackground_clicked();
	bool signal_redraw_preview(const Cairo::RefPtr<Cairo::Context>& cr);
	void on_response(int response_id);
	public:
	View_Gtk_Settings();
	void setEventListener(SettingsController& eventListener);
	Gtk::VBox& getCommonSettingsPane();
	Gtk::VBox& getAppearanceSettingsPane();
	void show(bool burgMode);
	void hide();
	View_ColorChooser& getColorChooser(ColorChooserType type);
	std::string getFontName();
	int getFontSize();
	void setFontName(std::string const& value);
	void addEntryToDefaultEntryChooser(std::string const& labelPathValue, std::string const& labelPathLabel, std::string const& numericPathValue, std::string const& numericPathLabel);
	void clearDefaultEntryChooser();
	void clearResolutionChooser();
	void addResolution(std::string const& resolution);
	std::string getSelectedDefaultGrubValue();
	void addCustomOption(bool isActive, std::string const& name, std::string const& value);
	void selectCustomOption(std::string const& name);
	std::string getSelectedCustomOption();
	void removeAllSettingRows();
	CustomOption getCustomOption(std::string const& name);
	void setActiveDefEntryOption(DefEntryType option);
	DefEntryType getActiveDefEntryOption();
	void setDefEntry(std::string const& defEntry);
	void setShowMenuCheckboxState(bool isActive);
	bool getShowMenuCheckboxState();
	void setOsProberCheckboxState(bool isActive);
	bool getOsProberCheckboxState();
	void showHiddenMenuOsProberConflictMessage();
	void setTimeoutValue(int value);
	int getTimeoutValue();
	std::string getTimeoutValueString();
	void setKernelParams(std::string const& params);
	std::string getKernelParams();
	void setRecoveryCheckboxState(bool isActive);
	bool getRecoveryCheckboxState();
	void setResolutionCheckboxState(bool isActive);
	bool getResolutionCheckboxState();
	void setResolution(std::string const& resolution);
	std::string getResolution();
	Glib::RefPtr<Pango::Layout> createFormattedText(Cairo::RefPtr<Cairo::Context>& context, Glib::ustring const& text, std::string const& format, int r, int g, int b, int r_b, int g_b, int b_b, bool black_bg_is_transparent = true);
	void setBackgroundImagePreviewPath(std::string const& menuPicturePath, bool isInGrubDir);
	void redraw(std::string const& menuPicturePath, bool isInGrubDir, Cairo::RefPtr<Cairo::Context> const* cr = NULL);
	std::string getBackgroundImagePath();
	void setPreviewEntryTitles(std::list<std::string> const& entries);
};

#endif
