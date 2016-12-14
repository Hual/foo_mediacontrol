#pragma once

#include "resource.h"

#define PREFERENCES_SECTION_NAME "Windows 10 Media Controls"

class preferences : public CDialogImpl<preferences>, public preferences_page_instance {
public:
	preferences(preferences_page_callback::ptr callback) : m_callback(callback) {}

	enum { IDD = IDD_PREFERENCES };

	BEGIN_MSG_MAP(CPreferences)
		MSG_WM_INITDIALOG(on_init)
		COMMAND_HANDLER_EX(IDC_PREFERENCES_PASSTHROUGH, BN_CLICKED, on_edit)
	END_MSG_MAP()

	t_uint32 get_state();
	void apply();
	void reset();

	inline static bool get_setting_passthrough() { return cfg_setting_passthrough; }

private:
	BOOL on_init(CWindow, LPARAM);
	void on_edit(UINT, int, CWindow);
	void on_changed();

	preferences_page_callback::ptr m_callback;

	static const GUID guid_cfg_setting_passthrough;
	static const GUID guid_advconfig_branch;

	static cfg_bool cfg_setting_passthrough;

	static advconfig_branch_factory g_advconfig_branch;
};

class preferences_page_custom_impl : public preferences_page_impl<preferences> {
public:
	const char * get_name() { return PREFERENCES_SECTION_NAME; }
	GUID get_guid() {
		static const GUID guid = { 0x779304fc, 0x27da, 0x4bad,{ 0xaf, 0x72, 0x8c, 0x4b, 0xeb, 0x2c, 0xd4, 0xac } };
		return guid;
	}
	GUID get_parent_guid() { return guid_tools; }

};
