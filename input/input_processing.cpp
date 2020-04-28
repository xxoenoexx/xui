
#include <xui/xui.hpp>

// Wndproc implementation.
LRESULT _stdcall wndproc_impl ( HWND hwnd , UINT msg , WPARAM wparam , LPARAM lparam ) {
	// XUI input processing.
	if ( xui::input_distribution->process ( hwnd , msg , wparam , lparam ) )
		return TRUE;

	// Return original wndproc.
	return CallWindowProcA ( xui::input_distribution->wndproc ( ) , hwnd , msg , wparam , lparam );
};

// distribution of input command.
auto xui::details::input_distributor::distribute ( xui::input_command& command ) {

	command.key_in < xui::input_command::KEY_ACTIVITY_PRESSED > ( VK_INSERT );



	// Distribute input.
	return true;
};

// Process.
bool xui::details::input_distributor::process ( HWND hwnd , UINT msg , WPARAM wparam , LPARAM lparam ) {
	// Create new command.
	xui::input_command command ( &m_Keys );

	// Add a new key to the held ptr.
	auto add_key = [ ] ( xui::input_command command , std::uint16_t virtual_key ) {
		// Test if actively held.
		if ( command.m_Keys_ptr->test ( virtual_key ) )
			return;

		// Flip as a actively held key.
		command.m_Keys_ptr->flip ( virtual_key );

		//Flip as a newly pressed key.
		command.m_Keys_action.flip ( virtual_key );
	};

	// Add a new key to the held ptr.
	auto remove_key = [ ] ( xui::input_command command , std::uint16_t virtual_key ) {
		// Test if actively held.
		if ( command.m_Keys_ptr->test ( virtual_key ) ) {
			// Flip as a actively held key.
			command.m_Keys_ptr->flip ( virtual_key );

			//Flip as a newly released key.
			command.m_Keys_action.flip ( virtual_key );
		};
	};

	// Distribute input.
	return distribute ( command );
};

// Construction.
xui::details::input_distributor::input_distributor ( HWND hwnd ) {
	// Get wndproc.
	m_Wndproc = reinterpret_cast < WNDPROC > ( SetWindowLongA ( hwnd , GWLP_WNDPROC , reinterpret_cast < LONG > ( wndproc_impl ) ) );
};

// Deconstruction.
xui::details::input_distributor::~input_distributor ( void ) {


};