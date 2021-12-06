fn solve( input : &str, day_count : u32 ) -> u64
{
    let nums : Vec<u32> = input.lines().next().unwrap().split_terminator(',').map(|num| num.parse().unwrap() ).collect();

    let mut lantern_fish_per_day : Vec<u64> = vec![0;9]; // 0-8 is 9 entries

    for elem in nums.iter()
    {
        lantern_fish_per_day[ *elem as usize ] += 1;
    }

/*
    for _ in 0..day_count
    {
        let count = lantern_fish_per_day.remove( 0 ); // remove fish that are done
        lantern_fish_per_day.push( count );           // spawn new fish
        lantern_fish_per_day[6] += count;             // reset the removed fish
    }
*/

for _ in 0..day_count
{
    lantern_fish_per_day.rotate_left(1);
    lantern_fish_per_day[6] += lantern_fish_per_day[8];
}


    lantern_fish_per_day.iter().sum()
}

fn main()
{
    println!("Sample Problem 1 {}", solve( "3,4,3,1,2", 80 ) );
    println!("Sample Problem 2 {}", solve( "3,4,3,1,2", 256 ) );

    let input = std::fs::read_to_string("input.txt");
    if input.is_err()     
    {
        println!("Unable to open input.txt");
    }
    else 
    {
        let input_str = &input.ok().unwrap();
        println!("problem 1 {}", solve( input_str as &str, 80 ) );
        println!("problem 2 {}", solve( input_str as &str, 256 ) );
    }
}