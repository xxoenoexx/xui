#include <xui/xui.hpp>

// Padding between children.
static xui::vector_2d <> g_Child_spacing ( 15U , 15U );

// Run command against page object input.
void xui::object_page::input ( xui::input_command& command ) {
	// Object is disabled.
	if ( m_Flags.test ( xui::OBJECT_FLAG_DISABLED ) ) {

		// Reset hovered/interaction flag.
		m_Flags.reset ( xui::OBJECT_FLAG_HOVERED );
		m_Flags.reset ( xui::OBJECT_FLAG_INTERACTION );

		return;
	};

	// Set hovered flag.
	m_Flags.set ( xui::OBJECT_FLAG_HOVERED ,
		// Is in header region.
		command.mouse_location ( ).inside ( m_Location , m_Size ) ||
		// Is already in an interaction.
		m_Flags.test ( xui::OBJECT_FLAG_INTERACTION ) );

	// Enables page.
	if ( m_Flags.test ( xui::OBJECT_FLAG_HOVERED ) &&
		command.key_in < xui::KEY_ACTIVITY_PRESS > ( VK_LBUTTON ) &&
		m_Flags.test ( xui::OBJECT_FLAG_INTERACTION ) ) {

		// Focus to parent.
		self_focus ( m_Parent_ptr );

		// Enable interaction flag.
		m_Flags.flip ( xui::OBJECT_FLAG_INTERACTION );
	};

	// Enable page.
	if ( m_Flags.test ( xui::OBJECT_FLAG_INTERACTION ) &&
		command.key_in < xui::KEY_ACTIVITY_RELEASE > ( VK_LBUTTON ) ) {

		// Remove interaction flag
		m_Flags.flip ( xui::OBJECT_FLAG_INTERACTION );

		// Enable the page.
		m_Flags.set ( xui::OBJECT_FLAG_COGITABLE );
		
		// Unfocus self.
		self_unfocus ( m_Parent_ptr );
	};

	// Has no children and or isn't opened.
	if ( !m_Flags.test ( xui::OBJECT_FLAG_COGITABLE ) || m_Children_ptrs.empty ( ) )
		return;

	// Rows
	std::vector <
		// Objects within row.
		std::list <
		// Objects location | Objects size.
		std::pair < xui::vector_2d <> , xui::vector_2d <> >
		>
	> previous_data;

	// Full content width.
	std::uint32_t total_width { };

	// Pass command to children.
	for ( auto& next_child : m_Children_ptrs ) {
		if ( !next_child->m_Api_ptr )
			next_child->m_Api_ptr = xui::g_Api.get ( );

		if ( !next_child->m_Parent_ptr )
			next_child->m_Parent_ptr = this;

		// Disable object while another is enabled.
		if ( m_Focused_ptr && m_Focused_ptr != next_child.get ( ) &&
			!next_child->m_Flags.test ( xui::OBJECT_FLAG_DISABLED ) )
			next_child->m_Flags.flip ( xui::OBJECT_FLAG_DISABLED );

		// Re-enable objects that weren't focused.
		if ( !m_Focused_ptr && next_child->m_Flags.test ( xui::OBJECT_FLAG_DISABLED ) )
			next_child->m_Flags.flip ( xui::OBJECT_FLAG_DISABLED );

		{ // Setup location of child.
			// Get the current objects row.
			std::uint16_t row = ( total_width + next_child->m_Size [ 0 ] + g_Child_spacing [ 0 ] ) / m_Parent_ptr->m_Size [ 0 ];

			// Remove previous padding.
			std::uint32_t row_offset = total_width - ( row * m_Parent_ptr->m_Size [ 0 ] ) + ( g_Child_spacing [ 0 ] * 0.5f );

			// Setup x location
			next_child->m_Location [ 0 ] = m_Location [ 0 ] + row_offset;

			// No previous row data.
			if ( previous_data [ std::max ( row - 1U , 0U ) ].empty ( ) )
				next_child->m_Location [ 0 ] = m_Parent_ptr->m_Location [ 1 ] + m_Parent_ptr->m_Header_height + g_Child_spacing [ 1 ] * 0.5f;
			else {
				std::uint32_t column_y { };

				for ( auto& data : previous_data [ row ] ) {
					auto& [object_location , object_size ] = data;		

					// Doesn't overlap.
					if ( object_location [ 0 ] < ( next_child->m_Location [ 0 ] + next_child->m_Size [ 0 ] )
						&& ( object_location [ 0 ] + object_size [ 0 ] ) < next_child->m_Location [ 0 ] )
						continue;

					// Objects far y.
					auto object_far = object_location [ 1 ] + object_size [ 1 ];

					if ( object_far <= column_y )
						continue;

					// Farthest determined y on this columnn.
					column_y = object_far;
				};

				// Setup y location.
				next_child->m_Location [ 1 ] = column_y + ( g_Child_spacing [ 1 ] * 0.5f );
			};

			// Pushback object details.
			previous_data [ row ].push_back ( { next_child->m_Location [ 0 ] , next_child->m_Size + g_Child_spacing } );

			// Add the next objects width.
			total_width += next_child->m_Size [ 0 ] + g_Child_spacing [ 0 ];
		};

		// Run objects input against command.
		next_child->input ( command );
	};
};

// Render page object.
void xui::object_page::render ( void ) {	
	/*
	
	...Render...
	
	*/

	if ( !m_Flags.test ( xui::OBJECT_FLAG_COGITABLE ) || m_Children_ptrs.empty ( ) )
		return;
	
	for ( auto iter = m_Children_ptrs.rbegin ( );  iter != m_Children_ptrs.rend ( ); ++iter )
		iter->get ( )->render ( );
};