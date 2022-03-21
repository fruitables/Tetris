// IT MIGHT BE OKAY TO MODIFY THIS FILE, BUT YOU PROBABLY DON'T
// WANT TO.
//
// Defines the structure and resources of the user interface.
//

#pragma once

#include <ge211.hxx>

// Forward declaration of our model struct. This lets us use references
// to Model in this file even though the definition isn’t visible. (Just
// like in C.)
struct Model;

struct View
{
    //
    // CONSTRUCTOR
    //

    /// Constructs a `View` given a const reference to the model that
    /// stores the actual state of the game. This lets the view observe
    /// the model’s state but not modify it.
    ///
    /// The word `explicit` means that this constructor doesn't define
    /// an implicit conversion whereby you could pass a `Model` to a
    /// function that expects a `View` and have it work.
    explicit View(Model const&);

    //
    // MEMBER FUNCTIONS
    //

    /// Returns the size of the window as given by `config.scene_dims`.
    ge211::Dims<int> initial_window_dimensions() const;

    /// Renders all the game entities to the screen. In particular,
    /// `ball_sprite` is placed at the ball's bounding box's top-left,
    /// `paddle_sprite` is placed where the model says the paddle is,
    /// and `brick_sprite` is placed for each brick in `model.bricks`.
    void draw(ge211::Sprite_set&,
              int score,
              int level);


    //


    //
    // MEMBER VARIABLES
    //

    /// This is a reference to the model. It means that the view doesn't
    /// own the model but has access to it. Thus, the client of the view
    /// (controller.cxx) must have or create a `Model` first and then
    /// pass that by reference to the `View` constructor.
    Model const& model;

    // These three definitions hold the sprites that we need to
    // display the circle, the paddle, and the bricks to the screen.
    // They’re initialized in View’s constructor (in view.cxx, see
    // View::View(Model const&))
    ge211::Rectangle_sprite const bit_sprite;
    ge211::Rectangle_sprite const gameover_sprite;
    ge211::Rectangle_sprite const won_sprite;
    ge211::Rectangle_sprite const paddle_sprite;
    ge211::Rectangle_sprite const brick_sprite;
    ge211::Rectangle_sprite const top_margin_sprite;

    ge211::Rectangle_sprite title_sprite {ge211::geometry::Dims<int>(120,120),
                                          (ge211::Color::from_rgba(255,99,71,1))};

    ge211::Font sans72 {"sans.ttf", 72},
            sans40 {"sans.ttf", 40},
            sans20 {"sans.ttf", 20};

    ge211::Text_sprite score_label {"Score: ", sans20};
    ge211::Text_sprite level_label {"Level: ", sans20};

    ge211::Text_sprite won_level_words {"Final Level: 5", sans20};

    ge211::Text_sprite final_score_words {"Final Score: ", sans20};
    ge211::Text_sprite final_level_words {"Final Level: ", sans20};
    ge211:: Text_sprite press_q_to_quit {"Press 'q' to quit", sans20};
    ge211:: Text_sprite press_r_to_restart {"Press 'r' to restart", sans20};


    ge211::Text_sprite score_words {"Score: ", sans20};
    ge211::Text_sprite level_words {"Level: ", sans20};



    ge211::Text_sprite game_over_label {"GAME OVER", sans40};
    ge211::Text_sprite won_label {"YOU WON!", sans40};

    ge211::Text_sprite paused1_sprite {"Paused! Press 'p' to unpause", sans20};
    ge211::Text_sprite paused2_sprite {"'q' to quit", sans20};
    ge211::Text_sprite paused3_sprite {"or 'r' to restart", sans20};









};
