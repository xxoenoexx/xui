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
		class global_api : public base_api {
		private:
			// Children objects unique ptrs.
			xui::dependency_vector < xui::object_base > m_Children_ptrs;

			// Input distribution.
			std::unique_ptr < xui::details::input_distribution > m_Input_distribution_ptr;

			// Friendship between Api and Input distribution.
			friend class xui::details::input_distribution;
		public:
			// Deconstructor.
			~global_api ( void ) = default;

			// Constructor.
			global_api ( HWND hwnd ) : base_api ( ) { 
				// Setup input distribution.
				m_Input_distribution_ptr = std::make_unique < xui::details::input_distribution > ( hwnd );
			};

			// Get input distribution.
			auto input_distribution ( void ) {
				return m_Input_distribution_ptr.get ( );
			};
		};
	}; // !!! details

	// Api.
	extern std::unique_ptr < details::global_api > g_Api;

	// Initialize xui api and core components.
	template < typename tCompound > requires std::is_compound < tCompound >::value
	static auto init ( HWND n , tCompound operation ) {

		xui::g_Api = std::make_unique < xui::details::global_api > ( n );

		// Populate.
		operation ( );
	};
}; // !!! xui

#endif // !!! xui_api
