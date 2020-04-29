#pragma once

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
	// Objects that are dependent on this object.
	template < typename tTy >
	using dependency_vector = std::vector < std::unique_ptr < tTy > >;

	namespace details {
		class api_director : public base_api {
		private:
			// Forms.
			dependency_vector < xui::object_base > m_Forms;

			// Input distribution.
			std::unique_ptr < xui::details::input_distributor > m_Input_distribution;

			friend class xui::details::input_distributor;
		public:
			// Constructor.
			api_director ( HWND hwnd ) : base_api ( ) { 
				// Setup input distribution.
				m_Input_distribution = std::make_unique < xui::details::input_distributor > ( hwnd );
			};

			auto input_distribution ( ) {
				return m_Input_distribution.get ( );
			};

			// Deconstructor.
			~api_director ( void ) = default;
		};
	};

	// API
	extern std::unique_ptr < details::api_director > g_Api;
};

// Initializex xui::g_Api.
#define INIT_XUI( n ) xui::g_Api = std::make_unique < xui::details::api_director > ( n );

#endif // !!! xui_api
