#include "stdafx.h"

#include "playback_listener.h"

class myinitquit : public initquit {
public:
	void on_init() {
		console::print("on_init()");

		// create a playback listener
		m_listener = new playback_listener();
	}
	void on_quit() {
		console::print("on_quit()");

		// free memory of playback listener
		delete m_listener;
	}

private:
	playback_listener* m_listener;
};

static initquit_factory_t<myinitquit> g_myinitquit_factory;
