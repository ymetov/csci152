

#include "set.h"
#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
bool set::equal( const std::string& s1, const std::string& s2 ) {
	
	if ( s1.length() == s2.length() ) {
		for ( size_t i = 0; i < s1.length(); i++)
		{
			if ( tolower(s1[i]) != tolower(s2[i]) ) 
				return false;	
		}
		return true;
	}
	return false;
}
bool set::contains( const std::string& el ) const {
	
	for ( size_t i = 0; i < data.size(); i++ ) {
		if(set::equal(data[i], el))
			return true;			
	}
	return false;	

}
bool set::insert( const std::string& el ) {
	if ( !set::contains(el) ) {
		data.push_back(el);
		return true;
	}
	return false;
}
size_t set::insert( const set& s ) {

	size_t n = 0;
	for ( size_t i = 0; n < s.data.size(); i++) {
		if ( !set::contains(s.data[i]) ) {
			data.push_back(s.data[i]);
			n++;
		}	
	}
	return n;
}
bool set::remove( const std::string& el ) {
	for ( size_t i = 0; i < data.size(); i++ ) {
		if(set::equal(data[i], el)) {
			std::swap(data[i], data[data.size() - 1]);
			data.pop_back();		
			return true;
		}				
	}
	return false;	
}

size_t set::remove( const set& s ) {
	size_t n = 0;
	for ( size_t i = 0; i < s.data.size(); i++ ) {
		if(set::remove(s.data[i]))
			n++;			
	}
	return n;
}
std::ostream& operator << ( std::ostream& out, const set& s ) {
	out << "{";
	   for( std::vector< std::string > :: const_iterator it =  s.begin( ); it != s.end( ); ++ it )
	   {
	     if ( it != s.end() && it != s.begin())
		 out << ", ";
	      out << *it;
	   }
	   out << "}";
	   return out;
}
bool subset( const set& s1, const set& s2 ) {
	for( std::vector< std::string > :: const_iterator it =  s1.begin( ); it != s1.end( ); ++ it )
	   {
	      if ( !s2.contains (*it) )
		return false;
	   }
	return true;
}

