#include "set.h"
#include <ctype.h>
// From previous task:

bool equal( const std::string& s1, const std::string& s2 ){

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

// Must be new written:
// It is important that equal and hash agree. That means:
//    If equal(s1,s2) then hash(s1) == hash(s2).

size_t hash( const std::string& st ) {
	size_t hash_val = 0;
	for(size_t i = 0; i < st.length(); i++) 
		hash_val = hash_val* 349 + tolower(st[i]);	
	return hash_val;
}
bool set::contains( const std::string& s ) const {
		for(auto it = buckets[hash(s)%buckets.size()].begin(); it != buckets[hash(s)%buckets.size()].end(); it++) {
			if (equal(*it, s))
				return true;
		}
	return false;
}

bool set::simp_insert( const std::string& s ){
	if(set::contains(s)) 
		return false;
	buckets[hash(s) % buckets.size()].push_back(s);
	set_size++;
	return true;

}

bool set::insert( const std::string& s ) {
	if ( !set::simp_insert( s ) ) {
		return false;
	}
	else {
		if ( max_load_factor < ((double)set_size / buckets.size()) )
			rehash(buckets.size() * 2);
		return true;
	}
}

void set::rehash( size_t newbucketsize ) {
	if( newbucketsize < 4 )
		newbucketsize = 4;
	std::vector< std::list< std::string >> newbuckets = std::vector< std::list< std::string >> ( newbucketsize );

	for(size_t i = 0; i < buckets.size(); i++) {
		for(auto it = buckets[i].begin(); it != buckets[i].end(); it++) 
			newbuckets[hash(*it) % newbucketsize].push_back(*it);
	}
	buckets = newbuckets;
}

bool set::remove( const std::string& s ) {
	
		for(auto it = buckets[hash(s)%buckets.size()].begin(); it != buckets[hash(s)%buckets.size()].end(); it++) {
			if (equal(*it, s)) {
				buckets[hash(s)%buckets.size()].erase(it);
				set_size--;
				return true;
			}
		}
	
	return false;

}

void set::clear( ) {
	for(size_t i = 0; i < buckets.size(); i++) 
		buckets[i].clear();
	set_size = 0;
}

std::ostream& set::print( std::ostream& out ) const {
	for(size_t i = 0; i < buckets.size(); i++) {
		out << "bucket[" << i << "]:\t{ ";
		for(auto it = buckets[i].begin(); it != buckets[i].end(); it++){
			if (it != buckets[i].begin())
				out << ", ";
			out << *it;
			
	}			
		out << " }\n";
	}
	return out;
}

std::ostream& set::printstatistics( std::ostream& out ) const
{
   std::cout << "set size =            " << size( ) << "\n";
   std::cout << "load factor =         " << loadfactor( ) << " ( max = " << max_load_factor << " )\n";
   std::cout << "standard deviation =  " << standarddev( ) << "\n";
   return out;
}


