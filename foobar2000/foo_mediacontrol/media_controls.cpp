#include "stdafx.h"

#include "media_controls.h"

#include <shcore.h>
#include <Windows.storage.streams.h>


media_controls::media_controls() {
	m_controls = Windows::Media::Playback::BackgroundMediaPlayer::Current->SystemMediaTransportControls;
	m_updater = m_controls->DisplayUpdater;
	m_input_listener = ref new input_listener();

	m_controls->PlaybackStatus = Windows::Media::MediaPlaybackStatus::Closed;
	m_updater->Type = Windows::Media::MediaPlaybackType::Music;

	m_props = m_updater->MusicProperties;

	m_controls->IsEnabled = false;
	m_controls->IsPlayEnabled = true;
	m_controls->IsPauseEnabled = true;
	m_controls->IsStopEnabled = true;
	m_controls->IsPreviousEnabled = true;
	m_controls->IsNextEnabled = true;
	
	m_event_id = (m_controls->ButtonPressed += ref new Windows::Foundation::TypedEventHandler<Windows::Media::SystemMediaTransportControls^, Windows::Media::SystemMediaTransportControlsButtonPressedEventArgs^>(m_input_listener, &input_listener::on_button_pressed));
	
	m_art_stream = nullptr;
}

media_controls::~media_controls() {
	m_controls->ButtonPressed -= m_event_id;
	begin_update();
}

media_controls& media_controls::toggle(bool toggle) {
	m_controls->IsEnabled = toggle;

	return *this;
}

media_controls& media_controls::set_title(const wchar_t* title) {
	m_props->Title = Platform::StringReference(title);

	return *this;
}

media_controls& media_controls::set_title(std::wstring title) {
	return set_title(title.c_str());
}

media_controls& media_controls::set_artist(const wchar_t* artist) {
	m_props->Artist = Platform::StringReference(artist);
	
	return *this;
}

media_controls& media_controls::set_artist(std::wstring artist) {
	return set_artist(artist.c_str());
}

media_controls& media_controls::set_album(const wchar_t* album) {
	m_props->AlbumTitle = Platform::StringReference(album);

	return *this;
}

media_controls& media_controls::set_album(std::wstring album) {
	return set_album(album.c_str());
}

media_controls& media_controls::set_album_artist(const wchar_t* artist) {
	m_props->AlbumArtist = Platform::StringReference(artist);

	return *this;
}

media_controls& media_controls::set_album_artist(std::wstring artist) {
	return set_album_artist(artist.c_str());
}

media_controls& media_controls::set_track_number(const wchar_t* number) {
	m_props->TrackNumber = _wtoi(number);

	return *this;
}

media_controls& media_controls::set_track_number(std::wstring number) {
	return set_track_number(number.c_str());
}

media_controls& media_controls::set_genres(genre_data_vector& genres) {
	m_props->Genres->ReplaceAll(Platform::ArrayReference<Platform::String^>(genres.data(), genres.size()));

	return *this;
}

media_controls& media_controls::set_status(Windows::Media::MediaPlaybackStatus status) {
	m_controls->PlaybackStatus = status;
}

void media_controls::play()
{
	m_controls->PlaybackStatus = Windows::Media::MediaPlaybackStatus::Playing;
	m_controls->IsEnabled = true;
}

void media_controls::pause()
{
	m_controls->PlaybackStatus = Windows::Media::MediaPlaybackStatus::Paused;
}

void media_controls::stop()
{
	m_controls->PlaybackStatus = Windows::Media::MediaPlaybackStatus::Stopped;
	m_controls->IsEnabled = false;
}

media_controls& media_controls::begin_update() {
	m_updater->ClearAll();
	m_updater->Type = Windows::Media::MediaPlaybackType::Music;

	if (m_art_stream) {
		m_art_stream->Release();
		m_art_stream = nullptr;
	}

	return *this;
}

void media_controls::end_update() {
	m_updater->Update();
}

media_controls& media_controls::set_thumbnail(album_art_data::ptr data) {
	if (data != nullptr)
	{
		if (m_art_stream = SHCreateMemStream(reinterpret_cast<const BYTE*>(data->get_ptr()), data->get_size())) {
			Windows::Storage::Streams::IRandomAccessStream^ stream;

			if (CreateRandomAccessStreamOverStream(m_art_stream, BSOS_DEFAULT, ABI::Windows::Storage::Streams::IID_IRandomAccessStream, reinterpret_cast<void**>(&stream)) == S_OK)
				m_updater->Thumbnail = Windows::Storage::Streams::RandomAccessStreamReference::CreateFromStream(stream);
			else
				popup_message::g_show("Failed to create over stream.", "Error");

		}
		else
			popup_message::g_show("Could not create stream.", "Error");
	}

	return *this;
}
