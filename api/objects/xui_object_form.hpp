#ifndef xui_api_object_form
#define xui_api_object_form

namespace xui {
	class object_form : public xui::object_base {
	protected:
		// Title.
		std::string m_Title;

		// Actively focused child object.
		xui::object_base* m_Focused_ptr;

		// Previous mouse location.
		xui::vector_2d <> m_Previous_mouse_location;

		// Children objects unique ptrs.
		xui::dependency_vector < xui::object_base > m_Children_ptrs;
	public:
		// Constructor.
		object_form ( std::string title , xui::vector_2d <> size , xui::vector_2d <> location = { 150U , 250U } ) 
					: xui::object_base ( location , size ) , m_Title { title } , m_Previous_mouse_location { } { };

		// Deconstructor.
		~object_form ( void ) = default;

		// Process input for form.
		virtual void input ( xui::input_command& command );

		// Render form.
		virtual void render ( void );
	};
}; // !!! xui


#endif // !!! xui_api_object_form
