#pragma once

#define SHELLHOOK_NAME L"SHELLHOOK"

class message_listener : private message_filter_impl_base {
public:
	// doesn't actually register a message since foobar has already registered it; just receives the message's number
	message_listener(t_uint32 message = RegisterWindowMessage(SHELLHOOK_NAME)) : message_filter_impl_base(message, message) { }
	bool pretranslate_message(MSG* p_msg);

};

#undef SHELLHOOK_NAME
