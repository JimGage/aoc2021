
#define NUM_FISH 5
#define NUM_DAYS 80

struct SInputFormat
{
   uint input[NUM_FISH];
};

struct SOutputFormat
{
   double output;
};

StructuredBuffer<SInputFormat> inputData : register(t0);
RWStructuredBuffer< SOutputFormat> outputData : register(u0);

[numthreads(1, 1, 1)]
void main( uint3 DTid : SV_DispatchThreadID )
{
   if ( DTid.x == 0 )
   {
      double lanternFishPerDay[9] = 
      { 
         0., 0., 0., 
         0., 0., 0., 
         0., 0., 0., 
      };

      uint i;
      for ( i = 0; i < NUM_FISH; ++i )
      {
         lanternFishPerDay[inputData[0].input[i]]++;
      }

      for ( i = 0; i <= NUM_DAYS; ++i )
      {
         lanternFishPerDay[(i + 6) % 9] += lanternFishPerDay[(i + 8) % 9];
      }

      outputData[0].output = 0;

      for ( i = 0; i < 9; ++i )
      { 
         outputData[0].output += lanternFishPerDay[ i ];
      }
   }
}