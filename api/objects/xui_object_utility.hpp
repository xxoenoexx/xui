#ifndef xui_api_utility
#define xui_api_utility

namespace xui {
	class object_base;

	namespace details {
		class base_api {
		protected:
			// Currently active object.
			object_base* m_Active_ptr;

			friend input_distributor;
		public:
			// Constructor.
			base_api ( void ) : m_Active_ptr { } { };

			// Deconstructor.
			~base_api ( void ) = default;

			// Get active ptr.
			auto& active ( void ) {
				return m_Active_ptr;
			};
		};
	}; // !!! details
}; // !!! xui


#endif // !!! xui_api_utility
