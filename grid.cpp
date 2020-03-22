/**
 * Implements a class representing a 2d grid of cells.
 *      - New cells are initialized to Cell::DEAD.
 *      - Grids can be resized while retaining their contents in the remaining area.
 *      - Grids can be rotated, cropped, and merged together.
 *      - Grids can return counts of the alive and dead cells.
 *      - Grids can be serialized directly to an ascii std::ostream.
 *
 * You are encouraged to use STL container types as an underlying storage mechanism for the grid cells.
 *
 * @author 962940
 * @date March, 2020
 */
#include "grid.h"

// Include the minimal number of headers needed to support your implementation.
// #include ...

/**
 * Grid::Grid()
 *
 * Construct an empty grid of size 0x0.
 * Can be implemented by calling Grid::Grid(square_size) constructor.
 *
 * @example
 *
 *      // Make a 0x0 empty grid
 *      Grid grid;
 *
 */
Grid::Grid() : Grid(0) {}


/**
 * Grid::Grid(square_size)
 *
 * Construct a grid with the desired size filled with dead cells.
 * Single value constructors should be marked "explicit" to prevent them
 * being used to implicitly cast ints to grids on construction.
 *
 * Can be implemented by calling Grid::Grid(width, height) constructor.
 *
 * @example
 *
 *      // Make a 16x16 grid
 *      Grid x(16);
 *
 *      // Also make a 16x16 grid
 *      Grid y = Grid(16);
 *
 *      // This should be a compiler error! We want to prevent this from being allowed.
 *      Grid z = 16;
 *
 * @param square_size
 *      The edge size to use for the width and height of the grid.
 */
Grid::Grid(int square_size) : Grid(square_size, square_size) {}


/**
 * Grid::Grid(width, height)
 *
 * Construct a grid with the desired size filled with dead cells.
 *
 * @example
 *
 *      // Make a 16x9 grid
 *      Grid grid(16, 9);
 *
 * @param width
 *      The width of the grid.
 *
 * @param height
 *      The height of the grid.
 */
Grid::Grid(int width, int height) {
    // Create a new 2D array of cells [x][y] and populate it with DEAD cells

    _width = width;
    _height = height;

    //cells = new Cell[width * height];
    cells = new Cell[width * height];
    for (int i = 0; i < width * height; i++) {
        cells[i] = DEAD;
    }

    std::cout << "Created a new grid with size width: " << width << " - height: " << height << std::endl;
}

/**
 * Grid::get_width()
 *
 * Gets the current width of the grid.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the width of the grid to the console
 *      std::cout << grid.get_width() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the width of the grid to the console
 *      std::cout << read_only_grid.get_width() << std::endl;
 *
 * @return
 *      The width of the grid.
 */

int Grid::get_width() const {
    return _width;
}

/**
 * Grid::get_height()
 *
 * Gets the current height of the grid.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the height of the grid to the console
 *      std::cout << grid.get_height() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the height of the grid to the console
 *      std::cout << read_only_grid.get_height() << std::endl;
 *
 * @return
 *      The height of the grid.
 */
int Grid::get_height() const {
    return _height;
}

/**
 * Grid::get_total_cells()
 *
 * Gets the total number of cells in the grid.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the total number of cells on the grid to the console
 *      std::cout << grid.get_total_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the total number of cells on the grid to the console
 *      std::cout << read_only_grid.get_total_cells() << std::endl;
 *
 * @return
 *      The number of total cells.
 */
int Grid::get_total_cells() const {
    return _width * _height;
}

/**
 * Grid::get_alive_cells()
 *
 * Counts how many cells in the grid are alive.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the number of alive cells to the console
 *      std::cout << grid.get_alive_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the number of alive cells to the console
 *      std::cout << read_only_grid.get_alive_cells() << std::endl;
 *
 * @return
 *      The number of alive cells.
 */
int Grid::get_alive_cells() const {
    int count = 0;
    for (int i = 0; i < _width * _height; i++) {
        if (cells[i] == ALIVE)
            count++;
    }

    return count;
}

/**
 * Grid::get_dead_cells()
 *
 * Counts how many cells in the grid are dead.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the number of dead cells to the console
 *      std::cout << grid.get_dead_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the number of dead cells to the console
 *      std::cout << read_only_grid.get_dead_cells() << std::endl;
 *
 * @return
 *      The number of dead cells.
 */
int Grid::get_dead_cells() const {
    int count = 0;
    for (int i = 0; i < _width * _height; i++) {
        if (cells[i] == DEAD)
            count++;
    }

    return count;
}

/**
 * Grid::resize(square_size)
 *
 * Resize the current grid to a new width and height that are equal. The content of the grid
 * should be preserved within the kept region and padded with Grid::DEAD if new cells are added.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Resize the grid to be 8x8
 *      grid.resize(8);
 *
 * @param square_size
 *      The new edge size for both the width and height of the grid.
 */

void Grid::resize(int square_size) {
    resize(square_size, square_size);
}

/**
 * Grid::resize(width, height)
 *
 * Resize the current grid to a new width and height. The content of the grid
 * should be preserved within the kept region and padded with Grid::DEAD if new cells are added.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Resize the grid to be 2x8
 *      grid.resize(2, 8);
 *
 * @param new_width
 *      The new width for the grid.
 *
 * @param new_height
 *      The new height for the grid.
 */

void Grid::resize(int new_width, int new_height) {
    Cell *newCells = new Cell[new_width * new_height]; // Create a new Cell array with the new width and height.
    for (int x = 0; x < new_width; x++) { // Loop through the width.
        for (int y = 0; y < new_height; y++) { // Loop through the height.
            if (x < _width && y < _height) // If the coordinate is within the old array, copy it over to the new array.
                newCells[x + new_width * y] = get(x, y);
            else
                newCells[x + new_width * y] = Cell::DEAD;
        }
    }

    // Assign the new variables to the object.
    cells = newCells;
    _width = new_width;
    _height = new_height;
}

/**
 * Grid::get_index(x, y)
 *
 * Private helper function to determine the 1d index of a 2d coordinate.
 * Should not be visible from outside the Grid class.
 * The function should be callable from a constant context.
 *
 * @param x
 *      The x coordinate of the cell.
 *
 * @param y
 *      The y coordinate of the cell.
 *
 * @return
 *      The 1d offset from the start of the data array where the desired cell is located.
 */

int Grid::get_index(int x, int y) const {
    return x + _width * y;
}

/**
 * Grid::get(x, y)
 *
 * Returns the value of the cell at the desired coordinate.
 * Specifically this function should return a cell value, not a reference to a cell.
 * The function should be callable from a constant context.
 * Should be implemented by invoking Grid::operator()(x, y).
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Read the cell at coordinate (1, 2)
 *      Cell cell = grid.get(1, 2);
 *
 * @param x
 *      The x coordinate of the cell to update.
 *
 * @param y
 *      The y coordinate of the cell to update.
 *
 * @return
 *      The value of the desired cell. Should only be Grid::ALIVE or Grid::DEAD.
 *
 * @throws
 *      std::exception or sub-class if x,y is not a valid coordinate within the grid.
 */

Cell Grid::get(int x, int y) const {
    try {
        return operator()(x, y);
    } catch (std::exception &e) {
        std::cerr << "Something went wrong!" << std::endl;
    }

    return DEAD;
}

/**
 * Grid::set(x, y, value)
 *
 * Overwrites the value at the desired coordinate.
 * Should be implemented by invoking Grid::operator()(x, y).
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Assign to a cell at coordinate (1, 2)
 *      grid.set(1, 2, Cell::ALIVE);
 *
 * @param x
 *      The x coordinate of the cell to update.
 *
 * @param y
 *      The y coordinate of the cell to update.
 *
 * @param value
 *      The value to be written to the selected cell.
 *
 * @throws
 *      std::exception or sub-class if x,y is not a valid coordinate within the grid.
 */
void Grid::set(int x, int y, Cell value) {
    try {
        Cell &cell = Grid::operator()(x, y);
        cell = value;
    } catch (std::exception &e) {
        std::cerr << "Grid::set::Something went wrong!" << std::endl;
    }
}

/**
 * Grid::operator()(x, y)
 *
 * Gets a modifiable reference to the value at the desired coordinate.
 * Should be implemented by invoking Grid::get_index(x, y).
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Get access to read a cell at coordinate (1, 2)
 *      Cell cell = grid(1, 2);
 *
 *      // Directly assign to a cell at coordinate (1, 2)
 *      grid(1, 2) = Cell::ALIVE;
 *
 *      // Extract a reference to an individual cell to avoid calculating it's
 *      // 1d index multiple times if you need to access the cell more than once.
 *      Cell &cell_reference = grid(1, 2);
 *      cell_reference = Cell::DEAD;
 *      cell_reference = Cell::ALIVE;
 *
 * @param x
 *      The x coordinate of the cell to access.
 *
 * @param y
 *      The y coordinate of the cell to access.
 *
 * @return
 *      A modifiable reference to the desired cell.
 *
 * @throws
 *      std::runtime_error or sub-class if x,y is not a valid coordinate within the grid.
 */
Cell &Grid::operator()(int x, int y) {
    if (!valid_coordinate(x, y)) {
        throw std::exception();
    } else {
        return cells[get_index(x, y)];
    }
}

/**
 * Grid::operator()(x, y)
 *
 * Gets a read-only reference to the value at the desired coordinate.
 * The operator should be callable from a constant context.
 * Should be implemented by invoking Grid::get_index(x, y).
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Constant reference to a grid (does not make a copy)
 *      const Grid &read_only_grid = grid;
 *
 *      // Get access to read a cell at coordinate (1, 2)
 *      Cell cell = read_only_grid(1, 2);
 *
 * @param x
 *      The x coordinate of the cell to access.
 *
 * @param y
 *      The y coordinate of the cell to access.
 *
 * @return
 *      A read-only reference to the desired cell.
 *
 * @throws
 *      std::exception or sub-class if x,y is not a valid coordinate within the grid.
 */
Cell &Grid::operator()(int x, int y) const {
    if (!valid_coordinate(x, y)) {
        throw std::exception();
    } else {
        Cell &cell = cells[get_index(x, y)];
        return cell;
    }
}

/**
 * Grid::crop(x0, y0, x1, y1)
 *
 * Extract a sub-grid from a Grid.
 * The cropped grid spans the range [x0, x1) by [y0, y1) in the original grid.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid y(4, 4);
 *
 *      // Crop the centre 2x2 in y, trimming a 1 cell border off all sides
 *      Grid x = y.crop(1, 1, 3, 3);
 *
 * @param x0
 *      Left coordinate of the crop window on x-axis.
 *
 * @param y0
 *      Top coordinate of the crop window on y-axis.
 *
 * @param x1
 *      Right coordinate of the crop window on x-axis (1 greater than the largest index).
 *
 * @param y1
 *      Bottom coordinate of the crop window on y-axis (1 greater than the largest index).
 *
 * @return
 *      A new grid of the cropped size containing the values extracted from the original grid.
 *
 * @throws
 *      std::exception or sub-class if x0,y0 or x1,y1 are not valid coordinates within the grid
 *      or if the crop window has a negative size.
 */
Grid Grid::crop(int x0, int y0, int x1, int y1) const {
    if (x0 < 0 || x1 > _width || y0 < 0 || y1 > _height || x1 - x0 < 0 || y1 - y0 < 0) {
        throw std::exception();
    }

    Grid newGrid = Grid(x1 - x0, y1 - y0);
    for (int y = y0; y < y1; y++) {
        for (int x = x0; x < x1; x++) {
            newGrid.set(x - x0, y - y0, get(x, y));
        }
    }

    return newGrid;
}

/**
 * Grid::merge(other, x0, y0, alive_only = false)
 *
 * Merge two grids together by overlaying the other on the current grid at the desired location.
 * By default merging overwrites all cells within the merge reason to be the value from the other grid.
 *
 * Conditionally if alive_only = true perform the merge such that only alive cells are updated.
 *      - If a cell is originally dead it can be updated to be alive from the merge.
 *      - If a cell is originally alive it cannot be updated to be dead from the merge.
 *
 * @example
 *
 *      // Make two grids
 *      Grid x(2, 2), y(4, 4);
 *
 *      // Overlay x as the upper left 2x2 in y
 *      y.merge(x, 0, 0);
 *
 *      // Overlay x as the bottom right 2x2 in y, reading only alive cells from x
 *      y.merge(x, 2, 2, true);
 *
 * @param other
 *      The other grid to merge into the current grid.
 *
 * @param x0
 *      The x coordinate of where to place the top left corner of the other grid.
 *
 * @param y0
 *      The y coordinate of where to place the top left corner of the other grid.
 *
 * @param alive_only
 *      Optional parameter. If true then merging only sets alive cells to alive but does not explicitly set
 *      dead cells, allowing whatever value was already there to persist. Defaults to false.
 *
 * @throws
 *      std::exception or sub-class if the other grid being placed does not fit within the bounds of the current grid.
 */
void Grid::merge(Grid other, int x0, int y0, bool alive_only) {
    // Check if other grid will fit onto current grid, with given coordinates
    if (!valid_coordinate(x0, y0) || !valid_coordinate(x0 + other.get_width(), y0 + other.get_height())) {
        throw std::exception();
    }

    // If we are only merging alive cells, check if other has any alive cells
    if (alive_only && other.get_alive_cells() <= 0) return;

    for (int y = 0, yy = y0; y < other.get_height(); y++, yy++) {
        for (int x = 0, xx = x0; x < other.get_width(); x++, xx++) {
            !alive_only ? set(xx, yy, other.get(x, y)) : other.get(x, y) == ALIVE ? set(xx, yy, other.get(x, y)) : set(
                    xx, yy, get(xx, yy));
        }
    }
}

/**
 * Grid::rotate(rotation)
 *
 * Create a copy of the grid that is rotated by a multiple of 90 degrees.
 * The rotation can be any integer, positive, negative, or 0.
 * The function should take the same amount of time to execute for any valid integer input.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a 1x3 grid
 *      Grid x(1,3);
 *
 *      // y is size 3x1
 *      Grid y = x.rotate(1);
 *
 * @param _rotation
 *      An positive or negative integer to rotate by in 90 intervals.
 *
 * @return
 *      Returns a copy of the grid that has been rotated.
 */
Grid Grid::rotate(int rotation) const {
    int rotationTimes = abs(rotation % 4 + 4) % 4;

    // Create a new grid, with the width and height changed based on the rotation wanted
    Grid newGrid = Grid(rotationTimes % 2 == 0 ? get_width() : get_height(),
                        rotationTimes % 2 == 0 ? get_height() : get_width());
    // Loop through every index in the new grid
    for (int y = 0; y < newGrid.get_height(); y++) {
        for (int x = 0; x < newGrid.get_width(); x++) {
            int newX = x;
            int newY = y;
            // Calculate where it should get its value from
            switch (rotationTimes) {
                case 0:
                    newX = x;
                    newY = y;
                    break;
                case 1:
                    newX = y;
                    newY = get_height() - x - 1;
                    break;
                case 2:
                    newX = get_width() - x - 1;
                    newY = get_height() - y - 1;
                    break;
                case 3:
                    newX = get_width() - y - 1;
                    newY = x;
                    break;
                default:
                    break;
            }
            // Set the new value in the rotated grid
            newGrid.set(x, y, get(newX, newY));
        }
    }

    return newGrid;
}

/**
 * operator<<(output_stream, grid)
 *
 * Serializes a grid to an ascii output stream.
 * The grid is printed wrapped in a border of - (dash), | (pipe), and + (plus) characters.
 * Alive cells are shown as # (hash) characters, dead cells with ' ' (space) characters.
 *
 * The function should be callable on a constant Grid.
 *
 * @example
 *
 *      // Make a 3x3 grid with a single alive cell
 *      Grid grid(3);
 *      grid(1, 1) = Cell::ALIVE;
 *
 *      // Print the grid to the console
 *      std::cout << grid << std::endl;
 *
 *      // The grid is printed with a border of + - and |
 *
 *      +---+
 *      |   |
 *      | # |
 *      |   |
 *      +---+
 *
 * @param os
 *      An ascii mode output stream such as std::cout.
 *
 * @param grid
 *      A grid object containing cells to be printed.
 *
 * @return
 *      Returns a reference to the output stream to enable operator chaining.
 */
std::ostream &operator<<(std::ostream &output_stream, const Grid &grid) {
    for (int y = -1; y <= grid.get_height(); y++) {
        for (int x = -1; x <= grid.get_width(); x++) {
            char character;
            if (x == -1 || x == grid.get_width()) {
                if (y == -1 || y == grid.get_height()) {
                    character = '+';
                } else {
                    character = '|';
                }
            } else if (y == -1 || y == grid.get_height()) {
                character = '-';
            } else {
                character = grid.get(x, y) == ALIVE ? '#' : ' ';
            }
            output_stream << character;
        }
        output_stream << std::endl;
    }

    return output_stream;
}

/**
 * Grid::valid_coordinate(x, y)
 *
 * Helper function to determine if the 2d coordinate is valid in the grid.
 * Should not be visible from outside the Grid class.
 * The function should be callable from a constant context.
 *
 * @param x
 *      The x coordinate of the cell.
 *
 * @param y
 *      The y coordinate of the cell.
 *
 * @return
 *      true if valid, false if not.
 */
bool Grid::valid_coordinate(int x, int y) const {
    return !(x < 0 || y < 0 || x >= _width || y >= _height);
}



