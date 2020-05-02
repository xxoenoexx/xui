#include <xui/xui.hpp>

// Height of header for form object.
static constexpr auto g_Header_height = 30U;

// Run command against page object input.
void xui::object_page::input ( xui::input_command& command ) {

	// Object is disabled.
	if ( m_Flags.test ( xui::OBJECT_FLAG_DISABLED ) ) {

		// Reset hovered/interaction flag.
		m_Flags.reset ( xui::OBJECT_FLAG_HOVERED );
		m_Flags.reset ( xui::OBJECT_FLAG_INTERACTION );

		// Discontinue.
		return;
	};

	// Set hovered flag.
	m_Flags.set ( xui::OBJECT_FLAG_HOVERED ,
		// Is in header region.
		command.mouse_location ( ).inside ( m_Location , m_Size ) ||
		// Is already in an interaction.
		m_Flags.test ( xui::OBJECT_FLAG_INTERACTION ) );

	// Enables page.
	if ( m_Flags.test ( xui::OBJECT_FLAG_HOVERED ) &&
		command.key_in < xui::KEY_ACTIVITY_PRESS > ( VK_LBUTTON ) ) {
		
		// Focus to parent.
		self_focus ( m_Parent_ptr );
	
		// Set into action.
		if ( m_Flags.test ( xui::OBJECT_FLAG_INTERACTION ) )
			m_Flags.flip ( xui::OBJECT_FLAG_INTERACTION );
	};

	// Enable page.
	if ( m_Flags.test ( xui::OBJECT_FLAG_INTERACTION ) && 
		command.key_in < xui::KEY_ACTIVITY_RELEASE > ( VK_LBUTTON ) )
		m_Flags.set ( xui::OBJECT_FLAG_COGITABLE );

	// Has no children and or isn't opened.
	if ( !m_Flags.test ( xui::OBJECT_FLAG_COGITABLE ) || m_Children_ptrs.empty ( ) )
		return;

	// Pass command to children.
	for ( auto& next_child : m_Children_ptrs ) {
		if ( !next_child->m_Api_ptr )
			next_child->m_Api_ptr = xui::g_Api.get ( );

		if ( !next_child->m_Parent_ptr )
			next_child->m_Parent_ptr = this;

		// Disable object while another is enabled.
		if ( m_Focused_ptr && m_Focused_ptr != next_child.get ( ) &&
			!next_child->m_Flags.test ( xui::OBJECT_FLAG_DISABLED ) )
			next_child->m_Flags.flip ( xui::OBJECT_FLAG_DISABLED );

		// Re-enable objects that weren't focused.
		if ( !m_Focused_ptr && next_child->m_Flags.test ( xui::OBJECT_FLAG_DISABLED ) )
			next_child->m_Flags.flip ( xui::OBJECT_FLAG_DISABLED );

		// Run objects input against command.
		next_child->input ( command );
	};
};

// Render page object.
void xui::object_page::render ( void ) {
	/*
	
	...Render...
	
	*/
};