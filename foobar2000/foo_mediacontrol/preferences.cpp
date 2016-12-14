#include "stdafx.h"

#include "preferences.h"

const GUID preferences::guid_cfg_setting_passthrough = { 0x7d8a2294, 0x36d0, 0x4ee9, {0xaa, 0x71, 0x36, 0x70, 0x5f, 0x0f, 0x43, 0xac } };
const GUID preferences::guid_advconfig_branch = { 0x1260bbfa, 0x0806, 0x434e, {0x91, 0x7c, 0xc8, 0x91, 0x89, 0xd3, 0x9c, 0x54 } };

cfg_bool preferences::cfg_setting_passthrough(guid_cfg_setting_passthrough, false);
advconfig_branch_factory preferences::g_advconfig_branch(PREFERENCES_SECTION_NAME, guid_advconfig_branch, advconfig_branch::guid_branch_tools, 0);

BOOL preferences::on_init(CWindow, LPARAM) {
	uButton_SetCheck(this->m_hWnd, IDC_PREFERENCES_PASSTHROUGH, cfg_setting_passthrough);

	return FALSE;
}

void preferences::on_edit(UINT, int, CWindow) {
	on_changed();
}

void preferences::on_changed() {
	m_callback->on_state_changed();
}

t_uint32 preferences::get_state() {
	t_uint32 state = preferences_state::resettable;
	if (uButton_GetCheck(this->m_hWnd, IDC_PREFERENCES_PASSTHROUGH) != cfg_setting_passthrough) {
		state |= preferences_state::changed;
	}

	return state;
}

void preferences::apply() {
	cfg_setting_passthrough = uButton_GetCheck(this->m_hWnd, IDC_PREFERENCES_PASSTHROUGH);

	on_changed();
}

void preferences::reset() {
	cfg_setting_passthrough = false;

	on_changed();
}

static preferences_page_factory_t<preferences_page_custom_impl> g_preferences_page_factory;
