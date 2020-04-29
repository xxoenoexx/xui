#pragma once

#ifndef xui_math_helper
#define xui_math_helper

namespace xui {
	namespace math {
		// Accumulation of tTy.
		template < typename tTy >
		auto accumulate ( tTy n ) { return n; };

		// Accumulation of tTy and tRest.
		template < typename tTy , typename... tRest >
		auto accumulate ( tTy n , tRest... rest ) { return n + accumulate ( rest... ); };
	}; // !!! math

	namespace concepts {
		// Accumulable operation of tTy and tRest.
		template < typename tTy , typename... tRest >
		concept iAccumulatable_variadic_operation =
			requires ( tTy n , tRest... q ) { accumulate ( n , q... ); };
	}; // !!! concepts

	// ---

	namespace math {
		// Accumulation of tTy and _Rest.
		template < typename tTy , typename... tRest > requires concepts::iAccumulatable_variadic_operation < tTy , tRest... >
			auto accumulate ( tTy n , tRest... q ) { return math::accumulate ( n , q... ); };

			// Sqr tTy.
			template < typename tTy >
			auto accumulate_sqr ( tTy n ) { return n * n; };

			// Accumulation of Sqr ( tTy ) and Sqr ( tRest ).
			template < typename tTy , typename... tRest >
			auto accumulate_sqr ( tTy n , tRest... q ) { return math::accumulate ( math::accumulate_sqr ( n ) , math::accumulate_sqr ( q... ) ); };
	}; // !!! math

	namespace concepts {
		// Sqrable operation of tTy and tRest.
		template < typename tTy , typename... tRest >
		concept iSqrable_variadic_operation =
			requires ( tTy n , tRest... q ) { sqrof ( n , q... ); };
	}; // !!! concepts

	namespace math {
		// Accumulation of Sqrd tTy and tRest.
		template < typename tTy , typename... tRest > requires concepts::iSqrable_variadic_operation < tTy , tRest... >
			auto accumulate_sqr ( tTy n , tRest... q ) { return math::accumulate_sqr ( n , q... ); };
	}; // !!! math

	// --

		///  Base vector class.
		//
		//		tSz = Vector maximum elements ( default: 2 ).
		//		tTy = Each elements type ( default: float ).
		// 
	template < std::size_t tSz = 2 , typename tTy = float >
	class vector {
	protected:
		// Element container.
		std::array < tTy , tSz > m_Elems;
	private:
		// For all plausible elements.
		template < std::size_t stSz , typename tFunc >
			auto& for_impl ( xui::vector < stSz , tTy > other , tFunc operation , std::size_t i = 0 ) {
				constexpr auto min_size = std::min ( tSz - 1 , stSz - 1 );
				
				// Operation.
				operation ( m_Elems [ i ] , other [ i ] );

				if ( i >= min_size )
					return *this;

				// Recursion.
				return for_impl ( other , operation , ++i );
			};

			// For all plausible elements.
			template < std::size_t stSz , typename tFunc >
			auto for_until_impl ( xui::vector < stSz , tTy > other , tFunc operation , std::size_t i = 0 ) const {
				constexpr auto min_size = std::min ( tSz - 1 , stSz - 1 );

				// Failed operation.
				if ( !operation ( m_Elems [ i ] , other [ i ] ) )
					return false;

				// Met maximum index.
				if ( i >= min_size )
					return true;

				// Recursion.
				return for_until_impl ( other , operation , ++i );
			};

			// Get length of m_Elems.
			template < std::size_t... tIns >
			auto length_impl ( std::index_sequence < tIns... > ) {
				return math::accumulate_sqr ( m_Elems [ tIns ]... );
			};
	public:
		// Construct.
		template < typename... tRest >
		vector ( tRest... rest ) : m_Elems { rest... } { };

		// Deconstruct.
		~vector ( void ) = default;

		// Gets m_Elems data.
		auto& data ( void ) {
			return m_Elems.data ( );
		};

		// --

			// Get begin iterator.
		auto begin ( void ) { return m_Elems.begin ( ); };

		// Get end iterator.
		auto end ( void ) { return m_Elems.end ( ); };

		// --

		template < typename stTy >
		auto& operator + ( const stTy right ) const {
			// return vec.
			auto Return_vec { *this };

			// Add to return vec.
			Return_vec += right;

			// Return vec.
			return Return_vec;
		};

		template < typename stTy >
		auto& operator - ( const stTy right ) const {
			// return vec.
			auto Return_vec { *this };

			// Subtract from return vec.
			Return_vec -= right;

			// Return vec.
			return Return_vec;
		};

		template < typename stTy >
		auto& operator * ( const stTy right ) const {
			// return vec.
			auto Return_vec { *this };

			// Multiply return vec.
			Return_vec *= right;

			// Return vec.
			return Return_vec;
		};

		// --

			// Gets element at 'i'.
		auto& operator [] ( const std::size_t i ) {
			return m_Elems [ i ];
		};

		template < typename stTy >
		auto& operator += ( const stTy right ) {
			for ( auto& Elem : m_Elems )
				Elem += right;

			// Return this.
			return *this;
		};

		template < typename stTy >
		auto& operator -= ( const stTy right ) {
			for ( auto& Elem : m_Elems )
				Elem -= right;

			// Return this.
			return *this;
		};

		template < typename stTy >
		auto& operator *= ( const stTy right ) {
			for ( auto& Elem : m_Elems )
				Elem *= right;

			// Return this.
			return *this;
		};

		template < typename stTy >
		auto& operator /= ( const stTy right ) {
			for ( auto& Elem : m_Elems )
				Elem *= right;

			// Return this.
			return *this;
		};

		// --


		template < std::size_t stSz >
		auto& operator = ( const xui::vector < stSz , tTy > right ) {
			return for_impl ( right , [ ] ( tTy& n , const tTy q ) { return n = q; } );
		};

		template < typename... tRest >
		auto& operator () ( tRest... rest ) {
			m_Elems = { rest... };

			return *this;
		};

		template < std::size_t stSz >
		auto& operator -= ( const xui::vector < stSz , tTy > right ) {
			return for_impl ( right , [ ] ( tTy& n , const tTy q ) { return n -= q; } );
		};

		template < std::size_t stSz >
		auto& operator += ( const xui::vector < stSz , tTy > right ) {
			return for_impl ( right , [ ] ( tTy& n , const tTy q ) { return n += q; } );
		};

		template < std::size_t stSz >
		auto& operator /= ( const xui::vector < stSz , tTy > right ) {
			return for_impl ( right , [ ] ( tTy& n , const tTy q ) { return n /= q; } );
		};

		template < std::size_t stSz >
		auto& operator *= ( const xui::vector < stSz , tTy > right ) {
			return for_impl ( right , [ ] ( tTy& n , const tTy q ) { return n *= q; } );
		};

		// Is greater than.
		template < std::size_t stSz >
		auto operator > ( const xui::vector < stSz , tTy > right ) const {
			return for_until_impl ( right , [ ] ( const tTy n , const tTy q ) { return  n > q; } );
		};

		// Is less than.
		template < std::size_t stSz >
		auto operator < ( const xui::vector < stSz , tTy > right ) const {
			return for_until_impl ( right , [ ] ( const tTy n , const tTy q ) { return  n < q; } );
		};

		// Is greater than or equal to.
		template < std::size_t stSz >
		auto operator >= ( const xui::vector < stSz , tTy > right ) const {
			return for_until_impl ( right , [ ] ( const tTy n , const tTy q ) { return  n >= q; } );
		};

		// Is less than or equal to.
		template < std::size_t stSz >
		auto operator <= ( const xui::vector < stSz , tTy > right ) const {
			return for_until_impl ( right , [ ] ( const tTy n , const tTy q ) { return  n <= q; } );
		};

		// Is equal to.
		template < std::size_t stSz >
		auto operator == ( const xui::vector < stSz , tTy > right ) const {
			return for_until_impl ( right , [ ] ( const tTy n , const tTy q ) { return  n == q; } );
		};

		// Isn't equal to.
		template < std::size_t stSz >
		auto operator != ( const xui::vector < stSz , tTy > right ) const {
			return for_until_impl ( right , [ ] ( const tTy n , const tTy q ) { return  n != q; } );
		};

		// --

			// Get length of vector of size 'stSz'.
		template < std::size_t stSz = tSz >
		auto length ( void ) const {
			return length_impl ( std::make_index_sequence < stSz > ( ) );
		};

		// Is inside boundaries of a begin point and designated size.
		bool inside ( const xui::vector < tSz , tTy > begin , const xui::vector < tSz , tTy > size ) const {
			// initialize to start point.
			auto end { begin };
			
			// Get to the end point.
			end += size;

			// Is inside of begin and end.
			return ( *this >= begin ) && ( *this <= end );
		};
	};

	// Default vector 2d.
	template < typename tTy = unsigned int >
	using vector_2d = xui::vector < 2 , tTy >;
}; // !!! xui

#endif // !!! xui_math_helper