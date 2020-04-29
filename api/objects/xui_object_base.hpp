#pragma once

#ifndef xui_api_object_base
#define xui_api_object_base

namespace xui {
	// Object flag markers.
	enum object_flags {
		// Is disabled by parent.
		OBJECT_FLAG_DISABLED ,
		// Is hidden from view.
		OBJECT_FLAG_HIDDEN ,
		// Is being hovered.
		OBJECT_FLAG_HOVERED ,
		// Is in interaction.
		OBJECT_FLAG_INTERACTION ,
		// Is able to process input.
		OBJECT_FLAG_COGITABLE
	};

	class object_base {
	public:
		// Location and size of object.
		xui::vector_2d <> m_Location , m_Size;

		// Object active flags.
		std::bitset < 5 > m_Flags;

		// Parent.
		xui::object_base* m_Parent_ptr;

		// Api.
		xui::details::base_api* m_Api_ptr;

		// Process input for object.
		virtual void input ( xui::input_command& command ) = 0;

		// Render object.
		virtual void render ( void ) = 0;
	};
};


#endif // !!! xui_api_object_base
