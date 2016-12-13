#pragma once

#define SHELLHOOK_NAME L"SHELLHOOK"

class message_listener : private message_filter_impl_base {
public:
	// doesn't actually register a message since foobar has already registered it; just receives the message's number
	message_listener() : message_filter_impl_base() { WM_SHELLHOOKMESSAGE = RegisterWindowMessage(SHELLHOOK_NAME); }
	bool pretranslate_message(MSG* p_msg);

private:
	UINT WM_SHELLHOOKMESSAGE;

};
