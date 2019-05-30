#include "map.h"

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
map::listofpairs::const_iterator 
map::find( const listofpairs& lst, const std::string& key )
{
   auto p = lst. begin( );
   while( p != lst. end( ) && !equal( p -> first, key ))
      ++ p;
   return p; 
}

map::listofpairs::iterator
map::find( listofpairs& lst, const std::string& key )
{
   auto p = lst. begin( );
   while( p != lst. end( ) && !equal( p -> first, key ))
      ++ p;
   return p;
}
size_t hash( const std::string& st ) {
	size_t hash_val = 0;
	for(size_t i = 0; i < st.length(); i++) 
		hash_val = hash_val* 349 + tolower(st[i]);	
	return hash_val;
}

bool map::contains_key( const std::string& key ) const {
	const listofpairs& temp = getbucket(key);
	auto p = temp. begin( );
   	while( p != temp. end( )) {
		if(equal( p -> first, key ))
			return true;
		p++;
	}	
	return false;
}

bool map::insert( const std::string& key, unsigned int val ) {
	listofpairs& temp = getbucket(key);
	map::listofpairs::iterator it = find(temp, key);
	if( it != temp.end() ) 
		return false;
	temp.push_back({key, val});
	map_size++;
	check_rehash();
	return true;
}

unsigned int& map::operator[] ( const std::string& key ) {
	if(contains_key(key)) {
		listofpairs& temp = getbucket(key);
		map::listofpairs::iterator it = find(temp, key);
		return (*it).second;
	} else {
		listofpairs& temp = getbucket(key);
		temp.push_back({key, 0});
		map_size++;
		check_rehash();
		return temp.back().second;
	}
}
unsigned int& map::at( const std::string& key ) {
	if(contains_key(key)) {
		listofpairs& temp = getbucket(key);
		map::listofpairs::iterator it = find(temp, key);
		return (*it).second;
	} else {
		throw std::out_of_range( "string not found" );
	}


}
unsigned int map::at( const std::string& key ) const {
	if(contains_key(key)) {
		const map::listofpairs& temp = getbucket(key);
		map::listofpairs::const_iterator it = find(temp, key);
		return (*it).second;
	} else {
		throw std::out_of_range( "string not found" );
	}


}

void map::rehash( size_t newbucketsize ) {
	if( newbucketsize < 4 )
		newbucketsize = 4;
	std::vector< listofpairs > newbuckets{ newbucketsize };
	for(size_t i = 0; i < buckets.size(); i++) {
		for(auto it = buckets[i].begin(); it != buckets[i].end(); it++) 
			newbuckets[hash((*it).first) % newbucketsize].push_back(*it);
	}
	buckets = newbuckets;

}
void map::check_rehash( ) {
	if(map_size > buckets.size() * max_load_factor)
		rehash(2*buckets.size());
}

bool map::remove( const std::string& key ) {
	listofpairs& temp = getbucket(key);
	map::listofpairs::iterator it = find(temp, key);
	if( it == temp.end() ) return false;
	temp.erase(it);
	map_size--;
	return true;
}


double map::standarddev( ) const  
{
   double sum = 0.0;
   double lf = loadfactor();

   for ( const auto& l : buckets )
   {
      double dif = l.size() - lf;
      sum += dif*dif;
   }

   return sqrt( sum / buckets. size( ));
}

void map::clear( ) 
{
   for( auto& l : buckets )
      l. clear( ); 

   map_size = 0; 
}

std::ostream& map::print( std::ostream& out ) const {	
	
	for(size_t i = 0; i < buckets.size(); i++) {
		out << "bucket[" << i << "]: { ";
		auto p = buckets[i]. begin( );
		while( p != buckets[i]. end( )) {
			if (p != buckets[i].begin())
				out << ", ";
			out << (*p).first << "/" << (*p).second;
			++ p;
		}
		out << " }\n";
	}
	return out;
}


std::ostream& map::printstatistics( std::ostream& out ) const
{
   out << "set size =            " << size( ) << "\n";
   out << "load factor =         " << loadfactor( ) << " ( max = " << 
                                      max_load_factor << " )\n";
   out << "standard deviation =  " << standarddev( ) << "\n";
   return out;
}


