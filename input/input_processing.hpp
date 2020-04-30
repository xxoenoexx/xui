#ifndef xui_distrubution
#define xui_distrubution

namespace xui {
	// Key activities.
	enum key_activity : std::uint8_t {
		// Key initial release.
		KEY_ACTIVITY_RELEASE = 0U ,
		// Key initial press.
		KEY_ACTIVITY_PRESS ,
		// Key is held.
		KEY_ACTIVITY_HELD
	};

	// Input command for recursion.
	struct input_command {
		// Key bitset.
		using key_bitset = std::bitset < 256 >;

		struct {
			// Currently scrolled amount.
			std::int16_t m_Scroll;

			// Mouse location on screen.
			xui::vector_2d <> m_Location;
		} mouse;

		// Construction.
		input_command ( key_bitset* key_ptr ) : m_Keys_ptr { key_ptr } , m_Keys_action { } , mouse { 0 , { 0U , 0U } } { };
		~input_command ( void ) = default;


		// Action keys.
		key_bitset m_Keys_action;

		// Pointer to actively held keys.
		key_bitset* m_Keys_ptr;

		// Get mouse location.
		const auto& mouse_location ( void ) const {
			return mouse.m_Location;
		};

		// Mouse scroll amount.
		const auto& mouse_scroll ( void ) const {
			return mouse.m_Scroll;
		};

		template < key_activity tActivity >
		auto key_in ( std::size_t i ) {
			// Is key in release activity.
			if constexpr ( tActivity == KEY_ACTIVITY_RELEASE )
				return !m_Keys_ptr->test ( i ) && m_Keys_action.test ( i );

			// Is key in press activity.
			else if constexpr ( tActivity == KEY_ACTIVITY_PRESS )
				return m_Keys_ptr->test ( i ) && m_Keys_action.test ( i );

			// Is the key held.
			else if constexpr ( tActivity == KEY_ACTIVITY_HELD )
				return m_Keys_ptr->test ( i );
			else
				return false;
		};
	};
	

	namespace details {
		// Process input and recursively distrubute.
		class input_distribution {
		private:
			// Actively held keys.
			input_command::key_bitset m_Keys;

			// Original window proc.
			WNDPROC m_Wndproc;

			// Window.
			HWND m_Hwnd;
		public:
			// Get m_Wndproc.
			const WNDPROC& wndproc ( void ) const {
				return m_Wndproc; 
			};

			// Constructor.
			input_distribution ( HWND );
			
			// Deconstructor.
			~input_distribution ( void );

			// Process message.
			bool process ( HWND , UINT , WPARAM , LPARAM );

			// Distrubute message.
			auto distribute ( xui::input_command& );
		};
	}; // !!! details
}; // !!! xui

#endif // !!! xui_distrubution