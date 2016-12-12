#pragma once

ref class input_listener sealed {
public:
	void on_button_pressed(Windows::Media::SystemMediaTransportControls^ sender, Windows::Media::SystemMediaTransportControlsButtonPressedEventArgs^ args);

};
