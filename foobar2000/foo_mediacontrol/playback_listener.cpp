#include "stdafx.h"

#include "playback_listener.h"
#include "media_controls.h"
#include "track_data.h"

void playback_listener::on_playback_new_track(metadb_handle_ptr p_track) {
	try {
		// create new track data from metadb handle
		track_data data(p_track);

		// update the media controls
		media_controls::get()
			.begin_update()
			.toggle(true)
			.set_title(data.get_title())
			.set_artist(data.get_artist())
			.set_genres(data.get_genres())
			.set_album(data.get_album())
			.set_album_artist(data.get_album_artist())
			.set_track_number(data.get_track_number())
			.set_thumbnail(data.get_album_art())
			.end_update();
	}
	catch (pfc::exception e) {
		popup_message::g_show("Caught exception", "Error");
	}
}
