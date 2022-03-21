// YOU DEFINITELY NEED TO MODIFY THIS FILE.

#include "ball.hxx"
#include "game_config.hxx"

// Computes where starting piece should be before the game begins
static Position
above_block(
        Block const& block,
        Game_config const& config)
{

    return {210, 0};
}

four_pc_coord L_Block_1 = {{0,0},{0,30},{0,60},{-30,60}};
four_pc_coord L_Block_2 = {{-30,0},{-30,30},{0,30},{30,30}};
four_pc_coord L_Block_3 = {{0,0},{30,0},{0,30},{0,60}};
four_pc_coord L_Block_4 = {{-30,30},{0,30},{30,30},{30,60}};

position_set L_Block_Posn_Set= {L_Block_1, L_Block_2, L_Block_3, L_Block_4};

four_pc_coord I_Block_1{{0,0},{30,0},{60,0},{90,0}};
four_pc_coord I_Block_2{{30,-30},{30,0},{30,30},{30,60}};
four_pc_coord I_Block_3{{-30,0},{0,0},{30,0},{60,0}};
four_pc_coord I_Block_4{{30,-60},{30,-30},{30,0},{30,30}};

position_set I_Block_Posn_Set= {I_Block_1, I_Block_2, I_Block_3, I_Block_4};

four_pc_coord S_Block_1 = {{0,0},{30,0 },{0,30},{-30,30}};
four_pc_coord S_Block_2 = {{-30,0},{-30,30},{0,30},{0,60}};
four_pc_coord S_Block_3 = {{0,30},{0,0},{30,0},{-30,30}};
four_pc_coord S_Block_4 = {{-30,0},{-30,30},{0,30},{0,60}};
position_set S_Block_Posn_set= {S_Block_1, S_Block_2, S_Block_3, S_Block_4};


four_pc_coord O_Block_1 = {{0,0},{30,0 },{0,30},{30,30}};
four_pc_coord O_Block_2 = {{0,0},{30,0 },{0,30},{30,30}};
four_pc_coord O_Block_3 = {{0,0},{30,0 },{0,30},{30,30}};
four_pc_coord O_Block_4 = {{0,0},{30,0 },{0,30},{30,30}};
position_set O_Block_Posn_set= {O_Block_1, O_Block_2, O_Block_3, O_Block_4};



shape_set shapes_coords = {L_Block_Posn_Set, I_Block_Posn_Set,
                           S_Block_Posn_set, O_Block_Posn_set};



Ball::Ball(Block const& paddle, Game_config const& config)
        : dimensions(config.bit_block_dims),
          center(above_block(paddle, config)),
          velocity({0,150}),
          // tells which shape set to look at
          current_shape(0),
          // tells which rotation set to look at for a shape
          current_rotation(0),
          last_rotation(4),
          // gives the current shape
          sprite_set (shapes_coords),
          //shape_rot_set(config.shapes[current_rotation]),
          // current "overall" position
          current_position(210,0),

          // current position of all the blocks in time
          current_position_set({{210,0},{210,30},{210,60},{180,60}}),
          flip_next_bool(false),
          left_right(0),
          convert_to_bricks(false),
          sprite_transition(false),
          live(false)


{ }

four_pc_coord
Ball:: find_ball_bottom () const {
    // initialize bottom_vals vector
    four_pc_coord top_vals;
    // initialize an x vals vector
    std::vector<int> x_vals;

    // iterrate through the coordinates of the foru blocks
    for (int i=0; i<4; i++){
        // if the current position set x value is not in the x vals, add it
        if (std::count(x_vals.begin(), x_vals.end(), current_position_set[i]
                .x ) == 0) // if the current coordinate x being itterated on is NOT
            // in the x vals vector, add it !
        {
            x_vals.push_back(current_position_set[i].x);
        }
    }

    // now we have a vector of x values that have no duplicates !
    // now, we will itterate through these x values

    for (int m=0; m < x_vals.size(); m++){
        int current_lowest_y_val = 900;
        ge211::Posn<int> current_lowest_posn = {0,0};
        current_lowest_posn.x = x_vals[m];

        for (int i=0; i<4; i++){
            if (x_vals[m] == current_position_set[i].x ) {
                if (current_position_set[i].y < current_lowest_y_val) {
                    current_lowest_posn.y = current_position_set[i].y;

                }
            }
        }
        top_vals.push_back(current_lowest_posn);
    }
    return top_vals;
}


four_pc_coord
Ball:: find_ball_top () const {
    // initialize bottom_vals vector
    four_pc_coord bottom_vals;
    // initialize an x vals vector
    std::vector<int> x_vals;

    // iterrate through the coordinates of the foru blocks
    for (int i=0; i<4; i++){
        // if the current position set x value is not in the x vals, add it
        if (std::count(x_vals.begin(), x_vals.end(), current_position_set[i]
                .x ) == 0) // if the current coordinate x being itterated on is NOT
            // in the x vals vector, add it !
        {
            x_vals.push_back(current_position_set[i].x);
        }
    }

    // now we have a vector of x values that have no duplicates !
    // now, we will itterate through these x values

    for (int m=0; m < x_vals.size(); m++){
        int current_highest_y_val = 0;
        ge211::Posn<int> current_highest_posn = {0,0};
        current_highest_posn.x = x_vals[m];

        for (int i=0; i<4; i++){
            if (x_vals[m] == current_position_set[i].x ) {
                if (current_position_set[i].y > current_highest_y_val) {
                    current_highest_posn.y = current_position_set[i].y;

                }
            }
        }
        bottom_vals.push_back(current_highest_posn);
    }
    return bottom_vals;
}

four_pc_coord
Ball::find_ball_right()const{
    // initialize bottom_vals vector
    four_pc_coord right_vals;
    // initialize an x vals vector
    std::vector<int> y_vals;

    // iterrate through the coordinates of the foru blocks
    for (int i=0; i<4; i++){
        // if the current position set x value is not in the x vals, add it
        if (std::count(y_vals.begin(), y_vals.end(), current_position_set[i]
                .y ) == 0) // if the current coordinate x being itterated on
            // is NOT
            // in the x vals vector, add it !
        {
            y_vals.push_back(current_position_set[i].y);
        }
    }

    // now we have a vector of x values that have no duplicates !
    // now, we will itterate through these x values

    for (int m=0; m < y_vals.size(); m++){
        int current_highest_x_val = 0;
        ge211::Posn<int> current_highest_posn = {0,0};
        current_highest_posn.y = y_vals[m];

        for (int i=0; i<4; i++){
            if (y_vals[m] == current_position_set[i].y ) {
                if (current_position_set[i].x > current_highest_x_val) {
                    current_highest_posn.x = current_position_set[i].x;

                }
            }
        }
        right_vals.push_back(current_highest_posn);
    }
    return right_vals;
}


four_pc_coord
Ball::find_ball_left()const{
    // initialize bottom_vals vector
    four_pc_coord left_vals;
    // initialize an x vals vector
    std::vector<int> y_vals;

    // iterrate through the coordinates of the foru blocks
    for (int i=0; i<4; i++){
        // if the current position set x value is not in the x vals, add it
        if (std::count(y_vals.begin(), y_vals.end(), current_position_set[i]
                .y ) == 0) // if the current coordinate x being itterated on
            // is NOT
            // in the x vals vector, add it !
        {
            y_vals.push_back(current_position_set[i].y);
        }
    }

    // now we have a vector of x values that have no duplicates !
    // now, we will itterate through these x values

    for (int m=0; m < y_vals.size(); m++){
        int current_lowest_x_val = 800;
        ge211::Posn<int> current_lowest_posn = {0,0};
        current_lowest_posn.y = y_vals[m];

        for (int i=0; i<4; i++){
            if (y_vals[m] == current_position_set[i].y ) {
                if (current_position_set[i].x < current_lowest_x_val) {
                    current_lowest_posn.x = current_position_set[i].x;

                }
            }
        }
        left_vals.push_back(current_lowest_posn);
    }
    return left_vals;
}



four_pc_coord
Ball:: find_brick_top (std::vector<ge211::Posn<int>>& bricks) const
{
    four_pc_coord top_vals;
    // iterates through each x and y value of each brick position
    for (int i = 0; i < bricks.size(); i++) {
        int current_x_to_check = bricks[i].x;
        int current_y_to_check = bricks[i].y;
        int repeats = 0;

        for (int j = 0; j < bricks.size(); j++) {
            // if repeated x and y value
            if ((bricks[j].x == current_x_to_check) && (bricks[j].y+30 ==
                                                     current_y_to_check) ){

                repeats++;
            }
        }
        if (repeats == 0) {

            top_vals.push_back(bricks[i]);
        }
    }
    return top_vals;

}


four_pc_coord
Ball:: find_brick_right(std::vector<ge211::Posn<int>>& bricks) const {
    four_pc_coord right_vals;
    std::vector<int> y_vals;

    for (int i=0; i<bricks.size(); i++){
        if (std::count(y_vals.begin(), y_vals.end(), current_position_set[i]
                .y ) == 0)
        {
            y_vals.push_back(current_position_set[i].y);
        }
    }


    for (int m=0; m < y_vals.size(); m++)
    {
        ge211::Posn<int> current_highest_posn = {0,0};
        current_highest_posn.y = y_vals[m];

        for (int i=0; i<bricks.size(); i++){
            if (y_vals[m] == bricks[i].x ) {
                if (bricks[i].x > current_highest_posn.x)
                {
                    current_highest_posn.x = bricks[i].x;
                }
            }
        }

        right_vals.push_back(current_highest_posn);
    }
    return right_vals;
}


four_pc_coord
Ball:: find_brick_left(std::vector<ge211::Posn<int>>& bricks) const {
    four_pc_coord left_vals;
    std::vector<int> y_vals;

    for (int i=0; i<bricks.size(); i++){
        if (std::count(y_vals.begin(), y_vals.end(), current_position_set[i]
                .y ) == 0)
        {
            y_vals.push_back(current_position_set[i].y);
        }
    }


    for (int m=0; m < y_vals.size(); m++)
    {
        ge211::Posn<int> current_lowest_posn = {0,0};
        current_lowest_posn.y = y_vals[m];

        for (int i=0; i<bricks.size(); i++){
            if (y_vals[m] == bricks[i].x ) {
                if (bricks[i].x < current_lowest_posn.x)
                {
                    current_lowest_posn.x = bricks[i].x;
                }
            }
        }

        left_vals.push_back(current_lowest_posn);
    }
    return left_vals;
}








bool
Ball:: hits_top_of_block(std::vector<ge211::Posn<int>>& bricks) const{

    // if there are PLACED bricks...
    if (bricks.size() != 0) {
        four_pc_coord bottoms = find_ball_bottom();
        four_pc_coord tops = find_brick_top(bricks);


        for (int i = 0; i < bottoms.size(); i++) {

            for (int j = 0; j < tops.size(); j++) {
                if (bottoms[i].y == tops[j].y
                    &&
                    bottoms[i].x== tops[j].x)
                {

                    return true;
                }

            }
        }
    }

    return false;


}


bool
Ball:: hits_side_of_block(std::vector<ge211::Posn<int>>& bricks) const{
    // iterates through the coords of the current piece
    for (int i=0; i<4; i++){
        for (int j = 0; j<bricks.size(); j++){
            if (current_position_set[i].y == bricks[j].y

                &&
                current_position_set[i].x == bricks[j].x )
                return true;

        }
    }
    return false;

}



bool
Ball::hits_bottom(Game_config const& config) const
{
    int highest_y_value = 0;
    int current_y_value = 0;
    for (int i = 0; i < 4; i++){
        current_y_value = current_position_set[i].y + config.bit_block_dims
                .height;
        if (current_y_value > highest_y_value ){
            highest_y_value = current_y_value;
            // finds 'highest' y value
        }
    }

    // if the highest y value is greater than or equal to the scene
    // dimensions height, return TRUE (hit the bottom)
    if (highest_y_value >= config.scene_dims.height+30)
    {
        return true;

    }

    return false;
}

// The ball hits the top when the y coordinate of its top is less than
// 0. (Note that the parameter isn't used.)
bool
Ball::hits_top(Game_config const& config,std::vector<ge211::Posn<int>>& bricks) const
{
    int lowest_y_value = 751;
    int current_y_value = 751;
    for (int i = 0; i<bricks.size(); i++){
        current_y_value = bricks[i].y;
        if (current_y_value <  lowest_y_value ){
            lowest_y_value = current_y_value;

            // finds 'lowest' y value (highest on screen)
        }
    }

    // if the lowest y value is less 0...
    // dimensions height, return TRUE (hit the top)
    if ( lowest_y_value <= 30 )
    {

        return true;

    }

    return false;
}



bool
Ball::hits_side(Game_config const& config) const
{

    int lowest_x_value =  500;
    int current_x_value = 0;
    int highest_x_value = 0;

    for (int i = 0; i < 4; i++){
        current_x_value = current_position_set[i].x;

        if (current_x_value > highest_x_value ){
            highest_x_value = current_x_value ;
            // finds highest x value (taking into account block width)
        }
        if (current_x_value < lowest_x_value){
            lowest_x_value = current_x_value ;
            // finds lowest x value
        }
    }

    if (highest_x_value >= config.scene_dims.width){
        return true;
    }

    if (lowest_x_value < 0 ){
        return true;
    }

    return false;
}

// Recall that `this` is a `const Ball*`, and you can create a copy of a ball
// with the copy constructor. So to get a new `Ball` to return, you can write
//
//     Ball result(*this);
//
Ball
Ball::next(double dt)
{
    position_set shape_rot_set = sprite_set[current_shape];
    Ball result(*this);
    last_rotation = current_rotation;

    int add_to_y = velocity.height * dt ;
    int add_to_x = 0;
    if (left_right == 1){
        // if left_right = 1, shift block left 30 px
        add_to_x = -30;
        result.left_right = 0;

    }

    //if left arrow pressed, subtract 30 to the x position of the OVERALL
    // current posiiton
    if (left_right == 2){
        add_to_x = 30;
        result.left_right = 0;

    }

    // adds the y displacement to current_position.y (overall position)
    result.current_position.y = result.current_position.y + add_to_y;
    result.current_position.x = result.current_position.x + add_to_x;

    // updates which flip position it is

    if (flip_next_bool == true){
        result.current_rotation = (result.current_rotation + 1 ) % 4;
        result.flip_next_bool = false;
    }

    // CURRENT ROTATION --> UPDATED NOW
    // DONT USE UNTIL THE END !!!!

    // flips current rotation
    four_pc_coord current_rot_set = shape_rot_set[result.current_rotation];


    // updates x and y positions of parts of the current_position_set
    for (int i=0; i<4; i++){
        result.current_position_set[i].x = result.current_position.x +
                current_rot_set[i].x;

        result.current_position_set[i].y = result.current_position.y +
                current_rot_set[i].y;
    }


    for (int i =0; i<4; i++){
        if (result.current_position_set[i].x % 30)
            result.current_position_set[i].x = result.current_position_set[i]
                    .x + (30 - result.current_position_set[i].x % 30);

        if (result.current_position_set[i].y % 30)
            result.current_position_set[i].y = result.current_position_set[i]
                    .y + (30 - result.current_position_set[i].y % 30);
    }

    return result;


}


bool
Ball::hits_block() const
{


    return false;
}


// Once you've written `Ball::hits_block`, finding an element of `bricks`
// that collides with this ball isn't hard (use a for-each loop), but
// how to /remove it once you find it? The more obvious solution may be
// to shift all the elements after it to the left, but that's awkward,
// and there's a cleaner way when the order of the elements of the
// vector doesn't matter:
//
//  1. Replace the hit brick with a copy of the last brick (`bricks.last()`)
//     by assignment. If you want to edit a brick in `bricks`, make sure each
//     brick given by the for-each loop is a reference to the existing brick,
//     not a copy.
//
//  2. Now the brick you didn't want is gone, but you have an extra in the back
//     that duplicates the one you just got rid of, so remove the last brick
//     using pop_back().
//
//  3. Don't keep iterating after a pop_back() or you will go out of
//     bounds, because the loop condition won't adjust to the diminished
//     vector.
//

int
Ball::pop_row(std::vector<ge211::Posn<int>>& bricks)
const
{
    bool re_search;
    int drop_count = 0;
    // itterates tthrough the rows 0 --> 25 y values
    for (int row = 0; row < 25; row++) {
        int count = 0;
        re_search = false;

        // itterates through the brick size
        for (int i = 0; i < bricks.size(); i++) {

            // iterates through brick list
            if (bricks[i].y == row * 30) {
                count++;
            }
        }


        if (count == 15) {
            drop_count++;
            re_search = true;

            while (count > 0) {
                for (int j = 0; j < bricks.size(); j++) {
                    // iterates through brick list
                    if (bricks[j].y == row * 30) {
                        bricks[j] = bricks.back();
                        bricks.pop_back();

                        count = count - 1;

                    }

                }
            }

            for (int j = 0; j < bricks.size(); j++) {
                if (bricks[j].y < row * 30) {
                    bricks[j].y = bricks[j].y + 30;
                }
            }
        }


    }

    while (re_search) {

        for (int row = 0; row < 26; row++) {
            int count = 0;
            re_search = false;

            // itterates through the brick size
            for (int i = 0; i < bricks.size(); i++) {

                // iterates through brick list
                if (bricks[i].y == row * 30) {
                    count++;
                }
            }


            if (count == 15) {
                drop_count++;
                re_search = true;

                while (count > 0) {
                    for (int j = 0; j < bricks.size(); j++) {
                        // iterates through brick list
                        if (bricks[j].y == row * 30) {
                            bricks[j] = bricks.back();
                            bricks.pop_back();

                            count = count - 1;

                        }

                    }
                }

                for (int j = 0; j < bricks.size(); j++) {
                    if (bricks[j].y < row * 30) {
                        bricks[j].y = bricks[j].y +  30;

                    }

                }

            }

        }

    }
    return drop_count;

}






bool
Ball::kill_brick(std::vector<ge211::Posn<int>>& bricks) const
{
    for (int i = 0; i<4; i++){
        bricks.push_back(current_position_set[i]);
    }
    return false;
}


bool
operator==(Ball const& a, Ball const& b)
{
    // TODO: replace this with your code:
    return false;
}

bool
operator!=(Ball const& a, Ball const& b)
{
    return !(a == b);
}

std::ostream&
operator<<(std::ostream& o, Ball const& ball)
{
    // You may have seen this message when running your tests. It
    // would be more helpful if it showed the contents of each ball,
    // right? So you can make that happen by making this print the
    // contents of the ball (however you like).
    o << "Ball{";
    o << "TODO: see the bottom of ball.cxx for more info";
    return o << "}";
}
