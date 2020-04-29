#include <xui/xui.hpp>

// Run command against form object input.
void xui::object_form::input ( xui::input_command& command ) {
	// Flip cogitable status.
	if ( command.key_in < xui::KEY_ACTIVITY_PRESS > ( VK_DELETE ) )
		m_Flags.flip ( xui::OBJECT_FLAG_COGITABLE );

	// Object wasn't cogitable.
	if ( !m_Flags.test ( xui::OBJECT_FLAG_COGITABLE ) )
		return;

	// Mouse initial press in header area.
	if ( command.key_in < xui::KEY_ACTIVITY_PRESS > ( VK_LBUTTON ) &&
		m_Flags [ xui::OBJECT_FLAG_HOVERED ] ) {
		// Set current mouse location.
		m_Previous_mouse_location = command.mouse_location ( );

		// Set interaction flag.
		if ( !m_Flags.test ( xui::OBJECT_FLAG_INTERACTION ) )
			m_Flags.flip ( xui::OBJECT_FLAG_INTERACTION );
	};

	// Update location drag.
	if ( m_Flags [ xui::OBJECT_FLAG_INTERACTION ] ) {
		auto next_location { m_Location };

		// Get the delta between previous/current location.
		next_location += command.mouse_location ( );
		next_location -= m_Previous_mouse_location;

		// Setup for next location.
		// Please, clamp this to resolution size.
		m_Location = next_location;

		// Store current mouse location.
		m_Previous_mouse_location = command.mouse_location ( );
	};

	// Set hovered flag.
	m_Flags [ xui::OBJECT_FLAG_HOVERED ] = command.mouse_location ( ).inside 
	( m_Location , xui::vector_2d <> ( m_Size [ 0 ] , 21U ) ) || m_Flags [ xui::OBJECT_FLAG_INTERACTION ];

	for ( auto& next_child : m_Children_ptrs ) {
		if ( !next_child->m_Api_ptr )
			next_child->m_Api_ptr = xui::g_Api.get ( );

		if ( !next_child->m_Parent_ptr )
			next_child->m_Parent_ptr = this;

		// Run child input against command.
		next_child->input ( command );
	};
};

// Render form object.
void xui::object_form::render ( void ) {

};