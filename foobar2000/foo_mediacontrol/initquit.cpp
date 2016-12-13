#include "stdafx.h"

#include "playback_listener.h"
#include "message_listener.h"

class myinitquit : public initquit {
public:
	void on_init() {
		console::print("on_init()");

		// create a playback listener
		m_playback_listener = new playback_listener();
		m_message_listener = new message_listener();
	}
	void on_quit() {
		console::print("on_quit()");
		
		// free memory of playback listener
		delete m_playback_listener;
		delete m_message_listener;
	}

private:
	playback_listener* m_playback_listener;
	message_listener* m_message_listener;

};

static initquit_factory_t<myinitquit> g_myinitquit_factory;
