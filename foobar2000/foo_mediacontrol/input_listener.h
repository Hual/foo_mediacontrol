#pragma once

ref class input_listener sealed {
public:
	void on_button_pressed(Windows::Media::SystemMediaTransportControls^ sender, Windows::Media::SystemMediaTransportControlsButtonPressedEventArgs^ args);

private:
	class media_notification_t : public main_thread_callback {
	public:
		inline media_notification_t(Windows::Media::SystemMediaTransportControlsButton button) : m_button(button) { }
		void callback_run() override;

	private:
		static_api_ptr_t<playback_control> m_playback_control;
		const Windows::Media::SystemMediaTransportControlsButton m_button;

	};
};
