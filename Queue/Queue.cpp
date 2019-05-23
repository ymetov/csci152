#include "queue.h"

void queue::ensure_capacity( size_t c ) 
{
   if( current_capacity < c )
   {
      // New capacity will be the greater of c and
      // 2 * current_capacity. 

      if( c < 2 * current_capacity )
         c = 2 * current_capacity;

      if( c < 8 ) 
         c = 8;
 
      double* newdata = new double[c];
      for( size_t s = 0; s < current_size; ++ s )
      {
         newdata[s] = data[ begin ];
         begin = next( begin );
      }

      current_capacity = c;
      begin = 0;
      end = current_size;

      delete[] data;
      data = newdata;
   }
}
void queue::printfields( std::ostream& out ) const
{
   out << "   current_size =     " << current_size << "\n";
   out << "   current_capacity = " << current_capacity << "\n";
   out << "   begin =            " << begin << "\n";
   out << "   end =              " << end << "\n";
}

void queue::checkinvariant( ) const 
{

   if( current_capacity == 0 )
   {
      std::cout << "current capacity == 0\n";
      printfields( std::cout ); 
      std::abort( );
   }

   if( begin >= current_capacity ) 
   {
      std::cout << "begin >= current_capacity\n";
      printfields( std::cout ); 
      std::abort( );
   }

   if( end >= current_capacity )
   {
      std::cout << "end >= current_capacity\n";
      printfields( std::cout ); 
      std::abort( );
   }

   if( current_size > current_capacity )
   {
      std::cout << "current_size > current_capacity\n";
      printfields( std::cout ); 
      std::abort( );
   }

   if( ( begin + current_size ) % current_capacity != end )
   {
      std::cout << 
         "distance between begin and end does not fit to current_size\n";
      printfields( std::cout );  
      std::abort( );
   }
}
std::ostream& operator << ( std::ostream& out, const queue& q )
{

   out << "[";
   size_t i = q. begin; 
   for( size_t s = 0; s < q. size( ); ++ s )
   {
      if(s) out << ", ";
      else out << " ";
      out << q. data[i];

      i = q.next(i); 
   }
   out << " ]";

   return out;
}
