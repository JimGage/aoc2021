#include <iostream>
#include <vector>

int64_t solve_compact( std::vector< int32_t > const & lanternFishInput, int32_t const numDays )
{
   int64_t lanternFishPerDay[9] = { 0 }, sum{ 0 };
   for ( int32_t const index : lanternFishInput ) lanternFishPerDay[index]++;
   for ( int32_t i = 0; i <= numDays; ++i ) lanternFishPerDay[(i + 6) % 9] += lanternFishPerDay[(i + 8) % 9];
   for ( int64_t const count : lanternFishPerDay ) sum += count;
   return sum;
}

int main( int argc, char * argv[] )
{
   std::cout << "Test 1 " << solve_compact( { 3,4,3,1,2 }, 80 ) << std::endl;
   std::cout << "Test 2 " << solve_compact( { 3,4,3,1,2 }, 256 ) << std::endl;
   return 0;
}
