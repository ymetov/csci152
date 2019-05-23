
#include "stack.h"

void stack::ensure_capacity( size_t c ) 
{
   if( current_capacity < c )
   {
      // New capacity will be the greater of c and
      // 2 * current_capacity. 

      if( c < 2 * current_capacity )
         c = 2 * current_capacity;

      double* newdata = new double[ c ];
      for( size_t i = 0; i < current_size; ++ i )
         newdata[i] = data[i];

      current_capacity = c;
      delete[] data;
      data = newdata;
   }
}
// 1
stack::stack() : current_size {0}, current_capacity {10}, data {new double[10]} {}
// 2
stack::stack(const stack& s) 
{
	current_capacity = s.current_capacity;
	data = new double [ s.current_capacity ];
	for (current_size = 0; current_size < s.current_size; current_size++)
		data[current_size] = s.data[current_size];	
	
}
//3
stack::~stack() 
{
	delete [] data;
}
//4
const stack& stack::operator = ( const stack& s )
{
	ensure_capacity( s.current_size + 1 );
	for (current_size = 0; current_size < s.current_size; current_size++)
		data[current_size] = s.data[current_size];
	return s;
}
//5
stack::stack( std::initializer_list<double> d ) 
{
	current_size = 0;
	current_capacity = d.size();
	data = new double[d.size()];
	for( double b : d )
	{
		data[current_size ++] = b;
	}
		
}
//6
void stack::push( double d )
{	
	
	if ( current_size == current_capacity )
		ensure_capacity( current_size + 1 );
	data[current_size] = d;
	current_size++;
}
//7
void stack::pop()
{	
	if ( current_size != 0)
		current_size--;
}
//8
void stack::clear()
{
	for (size_t i = 0; i < current_size; i++)
		data[i] = 0;
	current_size = 0;
}
//9
void stack::reset( size_t s ) 
{
	if ( s < current_size)
	{
		double* newdata = new double[ s ];
		for (size_t i = 0; i < s; i++)
			newdata[i] = data[i];
		delete[] data;
		data = newdata;
		current_capacity = s;
		
	}
}
//10
double stack::peek() const 
{
	if ( current_size != 0 ){	
		return data[current_size - 1];
	}
}
//11
size_t stack::size( ) const
{
	return current_size;
}
//12
bool stack::empty( ) const
{
	return (current_size == 0);
}
//13
std::ostream& operator << ( std::ostream& out, const stack& s )
{
	for (size_t i = 0; i < s.current_size; i++)
		out << s.data[i] << ' ';
	return out;
}
