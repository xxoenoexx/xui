#pragma once

#ifndef xui_distrubution

namespace xui {
	// Input command for recursion.
	struct input_command {
		// Key bitset.
		using key_bitset = std::bitset < 256 >;

		enum key_activity : std::uint8_t {
			KEY_ACTIVITY_RELEASE ,
			KEY_ACTIVITY_PRESSED ,
			KEY_ACTIVITY_OTHER
		};

		struct {
			// Currently scrolled amount.
			std::int32_t m_scroll;

			// Mouse location on screen.
			xui::vector_2d <> m_location;
		} m_Mouse;

		// Construction.
		input_command ( key_bitset* key_ptr ) : m_Keys_ptr { key_ptr } , m_Keys_action { } , m_Mouse { 0 , { 0U , 0U } } { };
		~input_command ( void ) = default;

		// Action keys.
		key_bitset m_Keys_action;

		// Pointer to actively held keys.
		key_bitset* m_Keys_ptr;

		template < key_activity tActivity >
		auto key_in ( std::size_t i ) {
			// Is key in release activity.
			if ( tActivity == KEY_ACTIVITY_RELEASE )
				return !m_Keys_ptr->test ( i ) && m_Keys_action.test ( i );

			// Is key in release activity.
			if ( tActivity == KEY_ACTIVITY_PRESSED )
				return m_Keys_ptr->test ( i ) && m_Keys_action.test ( i );

			// Is key in it's own special activity ( e.g. scroll ).
			if ( tActivity == KEY_ACTIVITY_OTHER )
				return m_Keys_action.test ( i );

			return false;
		};
	};
	

	namespace details {
		// Process input and recursively distrubute.
		class input_distributor {
		private:
			// Actively held keys.
			input_command::key_bitset m_Keys;

			// Original window Wndproc.
			WNDPROC m_Wndproc;

		public:
			// Get m_Wndproc.
			const WNDPROC& wndproc ( void ) const {
				return m_Wndproc; 
			};

			// Constructor.
			input_distributor ( HWND );
			
			// Deconstructor.
			~input_distributor ( void );

			// Process message.
			bool process ( HWND , UINT , WPARAM , LPARAM );

			// Distrubute message.
			auto distribute ( xui::input_command& );
		};
	}; // !!! details

	extern std::unique_ptr < details::input_distributor > input_distribution;
}; // !!! xui

#endif // !!! xui_distrubution