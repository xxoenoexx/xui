#ifndef xui_api_object_page
#define xui_api_object_page

namespace xui {
	class object_page : public xui::immediate_child_of < xui::object_form > ,
		public xui::immediate_parent < object_page > {
		// Title of page.
		std::string m_Title;
	public:
		// Constructor
		object_page ( std::string title ) 
					: m_Title ( title ) , xui::immediate_child_of < xui::object_form > ( ) { };

		// Deconstructor.
		virtual ~object_page ( void ) = default;

		// Process input for page.
		virtual void input ( xui::input_command& );

		// Render page.
		virtual void render ( void );
	};

	// Makes a unique pointer to a page object.
	static auto make_page ( std::string title ) {
		return std::make_unique < xui::object_page > ( title );
	};
}; // !!! xui

#endif // !!! xui_api_object_page
