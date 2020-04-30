#ifndef xui_api_utility
#define xui_api_utility

namespace xui {
	class object_base;

	namespace details {
		class base_api {
		protected:
			// Actively focused child object.
			xui::object_base* m_Focused_ptr;

			// Define friendship between Base Api and Input Distribution.
			friend xui::details::input_distribution;
		public:
			// Constructor.
			base_api ( void ) : m_Focused_ptr { } { };

			// Deconstructor.
			~base_api ( void ) = default;

			// Get active ptr.
			auto& focused ( void ) {
				return m_Focused_ptr;
			};
		};
	}; // !!! details
}; // !!! xui


#endif // !!! xui_api_utility
