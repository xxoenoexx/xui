#ifndef xui_api
#define xui_api

// Utility.
#include <xui/api/objects/xui_object_utility.hpp>

// Object types.
#include <xui/api/objects/xui_object_base.hpp>
#include <xui/api/objects/xui_object_form.hpp>
#include <xui/api/objects/xui_object_frame.hpp>
#include <xui/api/objects/xui_object_checkbox.hpp>
#include <xui/api/objects/xui_object_slider.hpp>

namespace xui {
	namespace details {
		class api_director : public base_api {
		private:
			// Children objects unique ptrs.
			xui::dependency_vector < xui::object_base > m_Children_ptrs;

			// Input distribution.
			std::unique_ptr < xui::details::input_distribution > m_Input_distribution_ptr;

			// Friendship between Api and Input distribution.
			friend class xui::details::input_distribution;
		public:
			// Constructor.
			api_director ( HWND hwnd ) : base_api ( ) { 
				// Setup input distribution.
				m_Input_distribution_ptr = std::make_unique < xui::details::input_distribution > ( hwnd );
			};

			// Get input distribution.
			auto input_distribution ( void ) {
				return m_Input_distribution_ptr.get ( );
			};

			// Deconstructor.
			~api_director ( void ) = default;
		};
	}; // !!! details

	// Api.
	extern std::unique_ptr < details::api_director > g_Api;
};

// Initializex xui::g_Api.
#define INIT_XUI( n ) xui::g_Api = std::make_unique < xui::details::api_director > ( n );

#endif // !!! xui_api
