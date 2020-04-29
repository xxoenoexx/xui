
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

	command.key_in < xui::KEY_ACTIVITY_HELD > ( VK_INSERT ); // Held.
	command.key_in < xui::KEY_ACTIVITY_RELEASE > ( VK_INSERT ); // Released.
	command.key_in < xui::KEY_ACTIVITY_PRESS > ( VK_INSERT ); // Pressed.

	command.mouse_location ( ).inside ( { 15U , 15U } , { 15U , 15U } );

	// Successfully distributed input.
	return true;
};

// Process.
bool xui::details::input_distributor::process ( HWND hwnd , UINT msg , WPARAM wparam , LPARAM lparam ) {
	// Create new command.
	xui::input_command command ( &m_Keys );

	// Add a new key to the held ptr.
	static auto add_key = [ ] ( xui::input_command command , std::uint16_t virtual_key ) {
		// Test if actively held.
		if ( command.m_Keys_ptr->test ( virtual_key ) )
			return;

		// Flip as a actively held key.
		command.m_Keys_ptr->flip ( virtual_key );

		//Flip as a newly pressed key.
		command.m_Keys_action.flip ( virtual_key );
	};

	// Add a new key to the held ptr.
	static auto remove_key = [ ] ( xui::input_command command , std::uint16_t virtual_key ) {
		// Test if actively held.
		if ( !command.m_Keys_ptr->test ( virtual_key ) )
			return;

		// Flip as a actively held key.
		command.m_Keys_ptr->flip ( virtual_key );

		//Flip as a newly released key.
		command.m_Keys_action.flip ( virtual_key );
	};

	switch ( msg ) {
	case WM_LBUTTONDOWN:
		add_key ( command , VK_LBUTTON );
		break;
	case WM_RBUTTONDOWN:
		add_key ( command , VK_RBUTTON );
		break;
	case WM_MBUTTONDOWN:
		add_key ( command , VK_MBUTTON );
		break;
	case WM_KEYDOWN:
		add_key ( command , wparam );
		break;
	case WM_LBUTTONUP:
		remove_key ( command , VK_LBUTTON );
		break;
	case WM_RBUTTONUP:
		remove_key ( command , VK_RBUTTON );
		break;
	case WM_MBUTTONUP:
		remove_key ( command , VK_MBUTTON );
		break;
	case WM_KEYUP:
		remove_key ( command , wparam );
		break;
	case WM_MOUSEWHEEL:
		command.mouse.m_Scroll = -( static_cast < std::int16_t > ( HIWORD ( wparam ) ) / 120 ) * 2;
		break;
	default:
		/// Update mouse location.
		if ( msg >= WM_MOUSEFIRST && msg <= WM_MOUSELAST ) {
			command.mouse.m_Location (	static_cast < std::uint32_t > ( LOWORD ( lparam ) ) ,	// X location.
										static_cast < std::uint32_t > ( HIWORD ( lparam ) ) );	// Y Location.
			break;
		};

		return FALSE;
	};

	// Distribute input.
	return distribute ( command );
};

// Construction.
xui::details::input_distributor::input_distributor ( HWND hwnd ) : m_Hwnd { hwnd } {
	// Get wndproc.
	m_Wndproc = reinterpret_cast < WNDPROC > ( SetWindowLongA ( hwnd , GWLP_WNDPROC , reinterpret_cast < LONG > ( wndproc_impl ) ) );
};

// Deconstruction.
xui::details::input_distributor::~input_distributor ( void ) {
	// Reset wndproc.
	SetWindowLongA ( m_Hwnd , GWLP_WNDPROC , reinterpret_cast < LONG > ( m_Wndproc ) );
};