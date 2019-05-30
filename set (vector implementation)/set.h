#ifndef SET_INCLUDED
#define SET_INCLUDED    1 

#include <iostream>
#include <string>
#include <vector>

class set
{
   std::vector< std::string > data;
      // data must never contain repeated elements.

public: 
   set( ) = default;   // empty set.
   set( const set& s ) = default;
   set& operator = ( const set& s ) = default; 
   ~set( ) = default;
      // Instead of writing '= default', these 4 methods 
      // can be completely omitted.

   set( std::initializer_list< std::string > init )  {
         for ( auto el : init ) {
		if ( !contains(el) )
			data.push_back(el);
	}
    }
      // Be sure to remove repeated elements.
 
   bool contains( const std::string& s ) const;
    
   bool insert( const std::string& s );
      // Returns true if the insertion took place.

   size_t insert( const set& s );
      // Inserts s. Returns the number of elements that were
      // inserted. (were not present) 

   bool remove( const std::string& s );
      // Returns true if s was present. 

   size_t remove( const set& s );
      // Returns number of elements removed. (that were present).
 
   size_t size( ) const {
	return data.size();
   }
   void clear( ) {
  	for (size_t i = size(); i >= 0; i--)
		data.pop_back();
   }


   using const_iterator = std::vector< std::string > :: const_iterator;
   const_iterator begin( ) const { return data. begin( ); }
   const_iterator end( ) const { return data. end( ); }

   static bool equal( const std::string& s1, const std::string& s2 );
};


std::ostream& operator << ( std::ostream& out, const set& s );

bool subset( const set& s1, const set& s2 );

inline bool equal( const set& s1, const set& s2 )
{
   return subset( s1, s2 ) && subset( s2, s1 );
}

#endif


