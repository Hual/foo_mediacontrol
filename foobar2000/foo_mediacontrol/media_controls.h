#pragma once

#include "input_listener.h"
#include "track_data.h"

class media_controls {
public:
	inline static media_controls& get() {
			static media_controls controls;
			return controls;
		}

	media_controls();
	~media_controls();
	media_controls& toggle(bool toggle);
	media_controls& begin_update();
	void end_update();
	media_controls& set_thumbnail(album_art_data::ptr data);
	media_controls& set_title(std::wstring title);
	media_controls& set_title(const wchar_t* title);
	media_controls& set_artist(std::wstring artist);
	media_controls& set_artist(const wchar_t* artist);
	media_controls& set_album(std::wstring album);
	media_controls& set_album(const wchar_t* album);
	media_controls& set_album_artist(std::wstring artist);
	media_controls& set_album_artist(const wchar_t* artist);
	media_controls& set_track_number(std::wstring number);
	media_controls& set_track_number(const wchar_t* number);
	media_controls& set_genres(genre_data_vector& genres);
	void play();
	void pause();
	void stop();

private:
	Windows::Media::SystemMediaTransportControls^ m_controls;
	Windows::Media::SystemMediaTransportControlsDisplayUpdater^ m_updater;
	Windows::Media::MusicDisplayProperties^ m_props;

	IStream* m_art_stream;

	Windows::Foundation::EventRegistrationToken m_event_id;
	input_listener^ m_input_listener;
};
