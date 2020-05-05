#ifndef xui_api_object_form
#define xui_api_object_form

namespace xui {
	class object_form : public xui::object_base , 
		public xui::immediate_parent < object_form > {
	protected:
		// Title.
		std::string m_Title;

		// Previous mouse location.
		xui::vector_2d <> m_Previous_mouse_location;
	public:
		// Height of header for form object.
		static constexpr auto m_Header_height = 30U;

		// Constructor.
		object_form ( std::string title , xui::vector_2d <> size , xui::vector_2d <> location ) 
					: xui::object_base ( location , size ) , m_Title { title } ,
					xui::immediate_parent < object_form > ( ) , m_Previous_mouse_location { } { };

		// Deconstructor.
		~object_form ( void ) = default;

		// Process input for form.
		virtual void input ( xui::input_command& );

		// Render form.
		virtual void render ( void );
	};

	// Makes a unique pointer to a form object.
	static auto begin_form ( std::string title , xui::vector_2d <> size , xui::vector_2d <> location = { 150U , 250U } ) {
		return std::make_unique < xui::object_form > ( title , size , location );
	};
}; // !!! xui

#endif // !!! xui_api_object_form
