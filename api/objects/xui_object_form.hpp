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
		xui::immediate_children_vector < xui::object_form > m_Children_ptrs;
	public:
		// Constructor.
		object_form ( std::string title , xui::vector_2d <> size , xui::vector_2d <> location ) 
					: xui::object_base ( location , size ) , m_Title { title } , m_Previous_mouse_location { } { };

		// Add child to form.
		template < typename tTy > requires 
			std::is_base_of < xui::immediate_child_of < xui::object_form > , tTy >::value
			auto add_child ( xui::unique_object_ptr < tTy > object ) {
			m_Children_ptrs.push_back ( std::move ( object ) );
		};

		// Deconstructor.
		~object_form ( void ) = default;

		// Process input for form.
		virtual void input ( xui::input_command& );

		// Render form.
		virtual void render ( void );
	};

	// Makes a unique pointer to a form object.
	static auto begin_form ( std::string title , xui::vector_2d <> size , xui::vector_2d <> location = { 150U , 250U } ) {
		// Make and return.
		return std::make_unique < xui::object_form > ( title , size , location );
	};
}; // !!! xui


#endif // !!! xui_api_object_form
