// YOU DEFINITELY NEED TO MODIFY THIS FILE.

#include "model.hxx"
#include <algorithm>


Model::Model(Game_config const& config)
        : config(config),
          paddle(Block::from_top_left(config.paddle_top_left_0(),
                                      config.paddle_dims)),
          ball(paddle, config),
          random_boost_source(-config.max_boost, config.max_boost),
          gameover(false),
          level(0),
          score_keeper(0),
          score_actual(0),
          wingame(false),
          paused(false),
          saved_velocity(0)
{

}


void
Model:: gameover_sequence(){
    // if the block hits the top
    // clears bricks
    bricks.clear();





}

void
Model:: wingame_sequence(){

    bricks.clear();

}

void
Model:: pause(){
    paused = true;
    saved_velocity = ball.velocity.height;
    ball.velocity.height = 0;
}

void
Model:: unpause(){
    paused = false;
    ball.velocity.height = saved_velocity;
    saved_velocity = 0;
}

void
Model::flip()
{
    ball.flip_next_bool = true;
}

void
Model :: left()
{
    ball.left_right = 1;
}

void
Model :: right()
{
    ball.left_right = 2;


}



// Freebie.
void
Model::launch()
{
    bricks.clear();
    paused=false;
    ball.live = true;
    gameover=false;
    wingame = false;
    level = 0;
    score_keeper = 0;
    score_actual = 0;
    ball.velocity = {0,200};
    ball.current_shape = 0;
    ball.current_rotation = 0;
    ball.last_rotation = 4;
    ball.flip_next_bool = false;
    ball.left_right = 0;
    ball.convert_to_bricks = false;
    ball.current_position_set ={{210,0},{210,30},{210,60},{180,60}};
    ball.current_position = {210,0};



}





void
Model::on_frame(double dt)
{
    if (gameover == false) {
    // if current ball is live...
    if (ball.live) {
        Ball next_b = ball.next(dt);

        if (next_b.hits_side(config) ||
            next_b.hits_side_of_block(bricks)) {


            ball.left_right = 0;
            ball.flip_next_bool = false;


        }



        if (next_b.hits_bottom(config)) {

            for (int i = 0; i < bricks.size(); i++) {
                if (bricks[i].x % 30)
                    bricks[i].x = bricks[i].x + (30 - bricks[i].x % 30);

                if (bricks[i].y % 30)
                    bricks[i].y =
                            bricks[i].y + (30 - (bricks[i].y + 10));

            }

            ball.kill_brick(bricks);
            int temp_score = ball.pop_row(bricks);

            score_actual = score_actual + (temp_score * 10);
            score_keeper = score_keeper + (temp_score * 10);

            if (score_keeper >= 40) {
                level++;
                if (level >= 6){
                    wingame = true;
                    wingame_sequence();
                    return;
                }
                score_keeper = score_keeper - 40;
                ball.velocity.height = ball.velocity.height +
                        30;


            }

            // adds current sprite coords to the bricks vector
            // resets coords of next block
            ball.current_position.x = 210;
            ball.current_position.y = 0;
            ball.current_rotation = 0;
            ball.current_shape = (ball.current_shape + rand() % 4 + 1) % 4;

        }

        if (next_b.hits_top_of_block(bricks) && ball.flip_next_bool ==
                                                false ) {

            std::cout<<ball.flip_next_bool;

            for (int i = 0; i < bricks.size(); i++) {
                if (bricks[i].x % 30)
                    bricks[i].x = bricks[i].x + (30 - bricks[i].x % 30);

                if (bricks[i].y % 30)
                    bricks[i].y =
                            bricks[i].y + (30 - (bricks[i].y + 10));

            }
            ball.kill_brick(bricks);

            int temp_score = ball.pop_row(bricks);
            score_actual = score_actual + (temp_score * 10);
            score_keeper = score_keeper + (temp_score * 10);


            if (score_keeper >= 40) {
                level++;

                if (level >= 6){
                    wingame = true;
                    wingame_sequence();
                    return;
                    }
                score_keeper = score_keeper - 40;
                ball.velocity.height = ball.velocity.height +
                                       30;
            }

            // adds current sprite coords to the bricks vector
            // resets coords of next block
            ball.current_position.x = 210;
            ball.current_position.y = 0;
            ball.current_rotation = 0;
            ball.current_shape = (ball.current_shape + rand() % 4 + 1) % 4;

        }

        ball = ball.next(dt);

        if (bricks.size() != 0) {
            if (ball.hits_top(config, bricks) == true) {
                gameover = true;
                ball.live = false;
                gameover_sequence();
                return;
            }
        }
    }
}
}






