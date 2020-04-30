#ifndef xui_api_object_base
#define xui_api_object_base

namespace xui {
	// Objects that are dependent on this object.
	template < typename tTy > requires std::is_class < tTy >::value
	using dependency_vector = std::vector < std::unique_ptr < tTy > >;

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
		// Is able to use the command,
		// serves more as an 'is awake' flag.
		OBJECT_FLAG_COGITABLE
	};

	class object_base {
	private:
		// Is this object focused.
		template < typename tTy > requires std::is_pointer < tTy >::value
		std::optional < bool > any_focus ( tTy& parent ) const {
			// Is there an actively focused object.
			if ( parent->focused ( ) )
				// Is this object focused.
				return m_Api_ptr->focused ( ) == this;

			// No object has focus.
			return std::nullopt;
		};
	protected:
		// Sets parents focus on self.
		template < typename tTy > requires std::is_pointer < tTy >::value
		auto self_focus ( tTy& parent ) {
			// No object has focus.
			if ( auto focus = any_focus ( parent ); !focus.has_value ( ) )
				// Set self to focus.
				parent->focused ( ) = this;
		};

		// Sets parents focus on self.
		template < typename tTy > requires std::is_pointer < tTy >::value
		auto self_unfocus ( tTy& parent ) {
			// Ensure we're the object that's focused.
			if ( auto focus = any_focus ( parent ); focus.has_value ( ) && *focus )
				// Empty focus object.
				parent->focused ( ) = { };
		};
	public:
		// Constructor.
		object_base ( xui::vector_2d <> location , xui::vector_2d <> size ) : m_Location { location } , m_Size { size } { };

		// Deconstructor.
		~object_base ( void ) = default;

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
}; // !!! xui


#endif // !!! xui_api_object_base
