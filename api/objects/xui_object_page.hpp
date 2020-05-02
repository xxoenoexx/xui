#ifndef xui_api_object_page
#define xui_api_object_page

namespace xui {
	class object_page : public xui::immediate_child_of < xui::object_form > {
		// Title of page.
		std::string m_Title;

		// Actively focused child object.
		xui::object_base* m_Focused_ptr;

		// Children objects unique ptrs.
		xui::immediate_children_vector < xui::object_page > m_Children_ptrs;
	public:
		// Constructor
		object_page ( std::string title ) 
					: m_Title ( title ) , xui::immediate_child_of < xui::object_form > ( ) { };

		// Deconstructor.
		virtual ~object_page ( void ) = default;

		// Add child to page.
		template < typename tTy > 
		requires std::is_base_of < xui::immediate_child_of < xui::object_page > , tTy >::value
			auto add_child ( xui::unique_object_ptr < tTy > object ) {
			m_Children_ptrs.push_back ( std::move ( object ) );
		};

		// Get active ptr.
		auto& focused ( void ) {
			return m_Focused_ptr;
		};

		// Process input for page.
		virtual void input ( xui::input_command& );

		// Render page.
		virtual void render ( void );
	};

	// Makes a unique pointer to a form object.
	static auto make_page ( std::string title ) {
		// Make and return.
		return std::make_unique < xui::object_page > ( title );
	};
}; // !!! xui

#endif // !!! xui_api_object_page
