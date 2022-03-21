/*******************************************/
/*** DO NOT CHANGE ANYTHING IN THIS FILE ***/
/*******************************************/

// Defines a struct for modeling the ball.

#pragma once

#include "game_config.hxx"

#include <ge211.hxx>

#include <iostream>


/// We will represent positions as GE211 `Posn<float>`s, which we alias
/// with the type name `Position`. This is a struct that could be
/// defined like so:
///
///   struct Position
///   {
///       float x;   // pixel distance from left edge of window
///       float y;   // pixel distance from top edge of window
///   };
using Position = ge211::Posn<float>;


/// We will represent velocities as GE211 `Dims<float>`s, which we alias
/// with the type name `Velocity`. This is a struct that could be
/// defined like so:
///
///   struct Velocity
///   {
///       float width;   // horizontal rate of change (px/s)
///       float height;  // vertical rate of change (px/s)
///   };
using Velocity = ge211::Dims<float>;

/// We will represent blocks (the bricks and the paddle) as GE211
/// `Rect<int>`s, which we alias with the type name `Block`. This is a
/// struct that could be defined like so:
///
///   struct Block
///   {
///       int x;       // x coordinate of left side of rectangle
///       int y;       // y coordinate of top side of rectangle
///       int width;
///       int height;
///   };
using Block = ge211::Rect<int>;

using four_pc_coord = std::vector<ge211::Posn<int>>;
using position_set = std::vector<four_pc_coord>;
using shape_set = std::vector<position_set>;


//vector of blocks

struct Ball
{
    ///
    Ball(Block const& paddle, Game_config const&);

    Ball next(double dt) ;
    bool hits_top(Game_config const&,std::vector<ge211::Posn<int>>& bricks) const;

    four_pc_coord find_ball_bottom() const;

    four_pc_coord find_ball_top() const;

    four_pc_coord find_ball_right() const;

    four_pc_coord find_ball_left() const;



    four_pc_coord find_brick_top(std::vector<ge211::Posn<int>>& bricks) const;

    four_pc_coord find_brick_right(std::vector<ge211::Posn<int>>& bricks) const;

    bool left_ball_hits_right_bricks(std::vector<ge211::Posn<int>>& bricks)
    const;

    bool right_ball_hits_left_bricks(std::vector<ge211::Posn<int>>&
    bricks) const;

    four_pc_coord find_brick_left(std::vector<ge211::Posn<int>>& bricks) const;





    bool hits_top_of_block(std::vector<ge211::Posn<int>>& bricks) const;

    bool hits_side_of_block(std::vector<ge211::Posn<int>>& bricks) const;

    bool hits_bottom(Game_config const&) const;

    bool hits_side(Game_config const&) const;

    bool hits_block() const;

    int pop_row(std::vector<ge211::Posn<int>>& bricks) const;

    bool kill_brick(std::vector<ge211::Posn<int>>& bricks) const;



    ge211::Dims<int> dimensions;

    Position center;

    Velocity velocity;

    int current_shape;

    int current_rotation;

    int last_rotation;

    shape_set sprite_set;

    position_set shape_rot_set;

    ge211::geometry::Posn<int> current_position;

    four_pc_coord current_position_set;

    bool flip_next_bool;

    int left_right;

    bool convert_to_bricks;

    bool sprite_transition;

    bool live;
};


/// Compares two `Ball`s for equality. This may be useful for testing.
///
/// Two `Ball`s are equal if all their member variables are pairwise
/// equal.
bool
operator==(Ball const&, Ball const&);

/// Inequality for `Ball`s.
bool
operator!=(Ball const&, Ball const&);

/// Stream insertion (printing) for `Ball`. This can make your test
/// results easier to read.
std::ostream&
operator<<(std::ostream&, Ball const&);
