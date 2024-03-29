/**
 * Declares a class representing a 2d grid of cells.
 * Rich documentation for the api and behaviour the Grid class can be found in grid.cpp.
 *
 * The test suites provide granular BDD style (Behaviour Driven Development) test cases
 * which will help further understand the specification you need to code to.
 *
 * @author 962940
 * @date March, 2020
 */
#pragma once

// Add the minimal number of includes you need in order to declare the class.
// #include ...
#include <vector>
#include <cmath>
#include <iostream>
#include <sstream>

/**
 * A Cell is a char limited to two named values for Cell::DEAD and Cell::ALIVE.
 */
enum Cell : char {
    DEAD = ' ',
    ALIVE = '#'
};

/**
 * Declare the structure of the Grid class for representing a 2d grid of cells.
 */
class Grid {
private:
    std::vector<Cell> cells;
    int _width, _height;

    int get_index(int x, int y) const;

public:
    Grid();

    explicit Grid(int square_size);

    Grid(int width, int height);

    int get_width() const;

    int get_height() const;

    int get_total_cells() const;

    int get_alive_cells() const;

    int get_dead_cells() const;

    void resize(int square_size);

    void resize(int new_width, int new_height);

    Cell get(int x, int y) const;

    void set(int x, int y, Cell value);

    Cell &operator()(int x, int y);

    const Cell &operator()(int x, int y) const;

    Grid crop(int x0, int y0, int x1, int y1) const;

    void merge(const Grid& other, int x0, int y0, bool alive_only = false);

    Grid rotate(int rotation) const;

    friend std::ostream &operator<<(std::ostream &output_stream, const Grid &grid);
    std::string to_string() const;
    // How to draw an owl:
    //      Step 1. Draw a circle.
    //      Step 2. Draw the rest of the owl.

    bool valid_coordinate(int x, int y) const;
};
