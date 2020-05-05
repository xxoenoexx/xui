#ifndef xui_api_object_frame
#define xui_api_object_frame

namespace xui {
	class object_frame : public xui::immediate_child_of < xui::object_page > ,
		public xui::immediate_parent < object_frame > {
	protected:
		// Title.
		std::string m_Title;

		// Previous mouse location.
		xui::vector_2d <> m_Previous_mouse_location;
	public:
		// Constructor.
		object_frame ( std::string title , xui::vector_2d <> size ) : 
			xui::immediate_child_of < xui::object_page > ( size ) , m_Title { title } ,
			xui::immediate_parent < object_frame > ( ) , m_Previous_mouse_location { } { };

		// Deconstructor.
		~object_frame ( void ) = default;

		// Process input for frame.
		virtual void input ( xui::input_command& ) { };

		// Render frame.
		virtual void render ( void ) { };
	};

	// Makes a unique pointer to a frame object.
	static auto make_frame ( std::string title , xui::vector_2d <> size ) {
		return std::make_unique < xui::object_frame > ( title , size );
	};
}; // !!! xui

#endif // !!! xui_api_object_frame
