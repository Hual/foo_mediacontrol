#include "stdafx.h"

#include "input_listener.h"
#include "media_controls.h"

void input_listener::on_button_pressed(Windows::Media::SystemMediaTransportControls^ sender, Windows::Media::SystemMediaTransportControlsButtonPressedEventArgs^ args) {
	// create a notification object
	service_ptr_t<media_notification> notification_ptr = new service_impl_t<media_notification>(args->Button);
	// run the code on main thread as playback_control only works from the main thread
	static_api_ptr_t<main_thread_callback_manager>()->add_callback(notification_ptr.get_ptr());
}

void input_listener::media_notification::callback_run() {
	switch (m_button) {
	case Windows::Media::SystemMediaTransportControlsButton::Play:
		m_playback_control->play_or_unpause();

		break;
	case Windows::Media::SystemMediaTransportControlsButton::Pause:
		m_playback_control->pause(true);

		break;
	case Windows::Media::SystemMediaTransportControlsButton::Stop:
		m_playback_control->stop();

		break;
	case Windows::Media::SystemMediaTransportControlsButton::Next:
		media_controls::get().set_status(Windows::Media::MediaPlaybackStatus::Changing);
		m_playback_control->next();

		break;
	case Windows::Media::SystemMediaTransportControlsButton::Previous:
		media_controls::get().set_status(Windows::Media::MediaPlaybackStatus::Changing);
		m_playback_control->previous();

		break;
	}
}
