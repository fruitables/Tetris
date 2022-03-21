// YOU DEFINITELY NEED TO MODIFY THIS FILE.

#include "view.hxx"
#include "model.hxx"

///
/// VIEW CONSTANTS
///

// Colors are red-green-blue(-alpha), each component
// from 0 to 255.
static ge211::Color const bit_color {255, 127, 127};
static ge211::Color const paddle_color {255, 255, 127};
static ge211::Color const brick_color {100, 100, 100};
static ge211::Color const green_color {0,100,50};



///
/// VIEW CONSTRUCTOR
///

// Data members that are references cannot be initialized by assignment
// in the constructor body and must be initialized in a member
// initializer list.
View::View(Model const& m)
        : model(m),
          bit_sprite(m.config.bit_block_dims, bit_color),
          gameover_sprite({450,750},bit_color),
          won_sprite({450,750,},green_color),
          paddle_sprite(m.config.paddle_dims, paddle_color),
          brick_sprite(m.config.brick_dims(), brick_color),
          top_margin_sprite({450,30}, paddle_color)
{ }




///
/// VIEW FUNCTIONS
///

// Use `Sprite_set::add_sprite(Sprite&, Position)` to add each sprite
// to `sprites`.


void
View::draw(ge211::Sprite_set& sprites,
           int score,
           int level)
{

    // adds sprites for the current active sprite
    for(int i = 0; i<4; i++) {

        sprites.add_sprite(bit_sprite, model.ball.current_position_set[i]);
    }

if(model.paused == true){
    sprites.add_sprite(paused1_sprite, {100,300}, 5);
    sprites.add_sprite(paused2_sprite, {100,350}, 5);
    sprites.add_sprite(paused3_sprite, {100,400}, 5);



}

if(model.wingame == true){
    sprites.add_sprite(won_sprite,{0,0},5);
    sprites.add_sprite(won_label, ge211::geometry::Posn<int>( 100, 100),
                       6);




    ge211::Text_sprite::Builder level_builder(sans20);
    level_builder.color(ge211::Color::black()) << level;
    level_label.reconfigure(level_builder);
    ge211::Text_sprite::Builder score_builder(sans20);

    score_builder.color(ge211::Color::black()) << score;
    score_label.reconfigure(score_builder);

    sprites.add_sprite(final_score_words,{10,1},8);
    sprites.add_sprite(won_level_words,{10,29},8);

    sprites.add_sprite(score_label, {130, 1},38);

    sprites.add_sprite(press_q_to_quit, {100, 300},6);
    sprites.add_sprite(press_r_to_restart, {100, 360},6);


}


if (model.gameover == true){
    sprites.add_sprite(gameover_sprite,{0,0},5);
    sprites.add_sprite(game_over_label, ge211::geometry::Posn<int>( 100, 100),
            6);

    ge211::Text_sprite::Builder level_builder(sans20);
    level_builder.color(ge211::Color::black()) << level;
    level_label.reconfigure(level_builder);
    ge211::Text_sprite::Builder score_builder(sans20);

    score_builder.color(ge211::Color::black()) << score;
    score_label.reconfigure(score_builder);

    sprites.add_sprite(final_score_words,{10,1},8);
    sprites.add_sprite(final_level_words,{10,29},8);

    sprites.add_sprite(score_label, {130, 1},38);
    sprites.add_sprite(level_label, ge211::geometry::Posn<int>( 130, 29), 8);

    sprites.add_sprite(press_q_to_quit, {100, 300},6);
    sprites.add_sprite(press_r_to_restart, {100, 360},6);
}


    for(int i=0; i < model.bricks.size(); i++) {


        sprites.add_sprite(bit_sprite,model.bricks[i]);
    }
    sprites.add_sprite(score_words,{10,1},3);
    sprites.add_sprite(level_words,{10,29},3);


    sprites.add_sprite(top_margin_sprite,{0,0},0);

    ge211::Text_sprite::Builder level_builder(sans20);
    level_builder.color(ge211::Color::white()) << level;
    level_label.reconfigure(level_builder);


    ge211::Text_sprite::Builder score_builder(sans20);
    score_builder.color(ge211::Color::white()) << score;
    score_label.reconfigure(score_builder);


    sprites.add_sprite(score_label, {80, 1},3);
    sprites.add_sprite(level_label, ge211::geometry::Posn<int>( 80, 29), 3);
    sprites.add_sprite(title_sprite, {1,1},1);


    // sprites.add_sprite(score_label, ge211::geometry::Posn<int>( 1, 1),2);
    //sprites.add_sprite(level_label, ge211::geometry::Posn<int>( 1, 29),2);

}


ge211::Dims<int>
View::initial_window_dimensions() const
{
    return model.config.scene_dims;
}

