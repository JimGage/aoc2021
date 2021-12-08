#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

//--------------------------------------------------------------------------------------------------------------
// Reusable Bits

std::vector<std::string> read_file( char const * const fileName )
{
   std::vector<std::string> result;
   std::ifstream inFile( fileName );

   while ( inFile )
   {
      std::string str;
      std::getline( inFile, str );
      result.push_back( str );
   }
   return result;
}

std::vector<std::string> split_strings( std::vector< std::string > const & inStrings, std::string const & token )
{
   std::vector<std::string> result;
   for ( std::string const & inString : inStrings )
   {
      std::string remainingString = inString;

      while ( !remainingString.empty() )
      {
         size_t const tokenPos = remainingString.find( token );

         if ( tokenPos == std::string::npos )
         {
            break;
         }

         result.push_back( remainingString.substr( 0, tokenPos ) );
         remainingString = remainingString.substr( tokenPos + token.size() );
      }

      if ( !remainingString.empty() )
      {
         result.push_back( remainingString );
      }
   }

   return result;
}

std::vector<std::string> split_string( std::string const & inString, std::string const & token )
{
   return split_strings( { inString }, token );
}

std::vector<int32_t> to_int( std::vector<std::string> const & strings )
{
   std::vector< int32_t > result;
   for ( std::string const & str : strings )
   {
      result.push_back( atoi( str.c_str() ) );
   }
   return result;
}

// End Reusable Bits
//--------------------------------------------------------------------------------------------------------------


int64_t solve_part1( std::vector<std::string> const & values )
{
   int32_t count = 0;
   for ( std::string const & str : values )
   {
      if ( str.empty() ) continue;
      std::vector<std::string> split = split_string( str, " | " );
      std::string const result = split[1];

      auto outputValues = split_string( result, " " );

      for ( std::string const & singleDigitOutput : outputValues )
      {
         switch ( singleDigitOutput.size() )
         {
         case 2:
         case 3:
         case 4:
         case 7:
            count++;
            break;
         }
      }
   }
   return count;
}

bool has_all_letters( std::string const & larger, std::string const & smaller )
{
   for ( char const c : smaller )
   {
      if ( larger.find( c ) == std::string::npos )
      {
         return false;
      }
   }

   return true;
}

int64_t solve_part2( std::vector<std::string> const & values )
{
   int64_t sum = 0;

   for ( std::string const & str : values )
   {
      if ( str.empty() ) continue;
      std::vector<std::string> split = split_string( str, " | " );
      std::string const cypherSourceInput = split[0];
      std::string const resultInput = split[1];
      
      auto cypherSourceValues = split_string( cypherSourceInput, " " );

      // sort the values
      for ( std::string & s : cypherSourceValues)
      {
         std::sort( s.begin(), s.end() );
      }

      int32_t indexArray[10] = { 0 };

      // find the known entries
      for ( int32_t i = 0; i < 10; ++i )
      {
         switch ( cypherSourceValues[i].size() )
         {
         case 2:
            indexArray[1] = i;
            break;
         case 3:
            indexArray[7] = i;
            break;
         case 4:
            indexArray[4] = i;
            break;
         case 7:
            indexArray[8] = i;
            break;
         }
      }

      // Have: 1, 4, 7, 8
      for ( int32_t i = 0; i < 10; ++i )
      {
         // search for 6, only six-segment to not share a segment with 1
         if ( cypherSourceValues[i].size() == 6 )
         {
            if ( !has_all_letters( cypherSourceValues[i], cypherSourceValues[indexArray[1]] ) )
            {
               indexArray[6] = i;
            }
         }

         // search for 3, only five-segment to share a segment with 1
         if ( cypherSourceValues[i].size() == 5 )
         {
            if ( has_all_letters( cypherSourceValues[i], cypherSourceValues[indexArray[1]] ) )
            {
               indexArray[3] = i;
            }
         }
      }

      // Have: 1, 3, 4, 6, 7, 8
      for ( int32_t i = 0; i < 10; ++i )
      {
         // search for 9, only six-segment to share all segments with 3
         if ( cypherSourceValues[i].size() == 6 && i != indexArray[6] )
         {
            if ( has_all_letters( cypherSourceValues[i], cypherSourceValues[indexArray[3]] ) )
            {
               indexArray[9] = i;
            }
         }

         // search for 5, only five-segment to share all segments with 6
         if ( cypherSourceValues[i].size() == 5 )
         {
            if ( has_all_letters( cypherSourceValues[indexArray[6]], cypherSourceValues[i] ) )
            {
               indexArray[5] = i;
            }
         }
      }

      // Have: 1, 3, 4, 5, 6, 7, 8, 9
      for ( int32_t i = 0; i < 10; ++i )
      {
         // search for 0, only six-segment remaining
         if ( cypherSourceValues[i].size() == 6 && i != indexArray[6] && i != indexArray[9] )
         {
            indexArray[0] = i;
         }
         // search for 2, only five-segment remaining
         if ( cypherSourceValues[i].size() == 5 && i != indexArray[3] && i != indexArray[5] )
         {
            indexArray[2] = i;
         }
      }

      // now just get the values
      auto resultSourceValues = split_string( resultInput, " " );

      int32_t num = 0;
      for ( std::string sourceDigit : resultSourceValues )
      {
         // make sure we're sorted
         std::sort( sourceDigit.begin(), sourceDigit.end() );
         for ( int32_t i = 0; i < 10; ++i )
         {
            if ( sourceDigit == cypherSourceValues[indexArray[i]] )
            {
               num = num * 10 + i;
               break;
            }
         }
      }

      sum += num;
   }

   return sum;
}

void test_input()
{
   std::vector< std::string > const testInput(
      {
         "be cfbegad cbdgef fgaecd cgeb fdcge agebfd fecdb fabcd edb | fdgacbe cefdb cefbgd gcbe",
         "edbfga begcd cbg gc gcadebf fbgde acbgfd abcde gfcbed gfec | fcgedb cgb dgebacf gc",
         "fgaebd cg bdaec gdafb agbcfd gdcbef bgcad gfac gcb cdgabef | cg cg fdcagb cbg",
         "fbegcd cbd adcefb dageb afcb bc aefdc ecdab fgdeca fcdbega | efabcd cedba gadfec cb",
         "aecbfdg fbg gf bafeg dbefa fcge gcbea fcaegb dgceab fcbdga | gecf egdcabf bgf bfgea",
         "fgeab ca afcebg bdacfeg cfaedg gcfdb baec bfadeg bafgc acf | gebdcfa ecba ca fadegcb",
         "dbcfg fgd bdegcaf fgec aegbdf ecdfab fbedc dacgb gdcebf gf | cefg dcbef fcge gbcadfe",
         "bdfegc cbegaf gecbf dfcage bdacg ed bedf ced adcbefg gebcd | ed bcgafe cdgba cbgef",
         "egadfb cdbfeg cegd fecab cgb gbdefca cg fgcdab egfdb bfceg | gbdfcae bgc cg cgb",
         "gcafb gcf dcaebfg ecagb gf abcdeg gaef cafbge fdbac fegbdc | fgae cfgab fg bagce"
      } );

   std::cout << "Test 1: " << solve_part1(testInput) << std::endl;
   std::cout << "Test 2:" << solve_part2( testInput ) << std::endl;
}

int main( int argc, char * argv[] )
{
   test_input();

   if ( argc != 2 )
   {
      return -1;
   }

   std::vector<std::string> const contents = read_file( argv[1] );

   int64_t const result1 = solve_part1( contents );
   std::cout << result1 << std::endl;

   int64_t const result2 = solve_part2( contents );
   std::cout << result2 << std::endl;

   return 0;
}
