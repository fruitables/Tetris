/*******************************************/
/*** DO NOT CHANGE ANYTHING IN THIS FILE ***/
/*******************************************/

// The model tracks the logical state of the game, independent of the
// presentation and control. In particular, it keeps track of:
//
//  - the game configuration (the sizes of things such as bricks, the paddle,
//    and the screen),
//
//  - the locations and sizes of all the bricks,
//
//  - the location and size of the paddle (the thing at the bottom that you
//    control), and
//
//  - the state of the ball, including its location and velocity (grouped in
//    the `Ball` struct).
//
// It also provides three member functions to help the UI in updating it.
//

#pragma once

#include "ball.hxx"
#include "game_config.hxx"
#include <vector>


// The logical state of the game.
struct Model
{
    ///
    /// CONSTRUCTOR
    ///

    // Constructs a model from a game configuration.
    //
    // The `= Game_config()` syntax makes the argument optional, in which case
    // it defaults to the default `Game_config`. That is, you can explicitly
    // create a `Game_config` to pass the `Model` constructor like so:
    //
    //     Game_config config;
    //     config.ball_radius = 2;
    //     Model model(config);
    //
    // Or you can omit the constructor argument, in which case you get
    // the default `Game_config` (as defined in game_config.cpp):
    //
    //     Model model;
    //
    // The word `explicit` means that this constructor doesn't define an
    // implicit conversion whereby C++ would automatically convert
    // `Game_config`s into `Model`s if needed. You don't want that.
    explicit Model(Game_config const& config = Game_config());

    ///
    /// MEMBER FUNCTIONS
    ///

    void launch();
    void gameover_sequence();
    void wingame_sequence();
    void flip();
    void left();
    void right();
    void on_frame(double dt);
    void pause();
    void unpause();

    ///
    /// MEMBER VARIABLES
    ///


    Game_config const config;

    // All of the bricks, in no particular order. `Block` is a type
    // alias for `ge211::Rect<float>`, which means it gives both the
    // position of the top-left corner of each brick and the dimensions.
    std::vector<ge211::Posn<int>> bricks;

    position_set current_piece_position;

    // The position and dimensions of the paddle.
    Block paddle;

    // The state of the ball. Much of the model's business actually
    // happens in there, so see ball.hxx for that.
    Ball ball;

    // A source of random “boost” values.
    ge211::Random_source<float> random_boost_source;

    bool gameover;
    int level;

    int score_keeper;
    int score_actual;
    bool wingame;
    bool paused;
    int saved_velocity;
};

