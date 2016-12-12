#include "stdafx.h"

#include "input_listener.h"

void input_listener::on_button_pressed(Windows::Media::SystemMediaTransportControls^ sender, Windows::Media::SystemMediaTransportControlsButtonPressedEventArgs^ args) {
	switch (args->Button)
	{
	case Windows::Media::SystemMediaTransportControlsButton::Play:

		break;
	}
}
