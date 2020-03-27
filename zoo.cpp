/**
 * Implements a Zoo namespace with methods for constructing Grid objects containing various creatures in the Game of Life.
 *      - Creatures like gliders, light weight spaceships, and r-pentominos can be spawned.
 *          - These creatures are drawn on a Grid the size of their bounding box.
 *
 *      - Grids can be loaded from and saved to an ascii file format.
 *          - Ascii files are composed of:
 *              - A header line containing an integer width and height separated by a space.
 *              - followed by (height) number of lines, each containing (width) number of characters,
 *                terminated by a newline character.
 *              - (space) ' ' is Cell::DEAD, (hash) '#' is Cell::ALIVE.
 *
 *      - Grids can be loaded from and saved to an binary file format.
 *          - Binary files are composed of:
 *              - a 4 byte int representing the grid width
 *              - a 4 byte int representing the grid height
 *              - followed by (width * height) number of individual bits in C-style row/column format,
 *                padded with zero or more 0 bits.
 *              - a 0 bit should be considered Cell::DEAD, a 1 bit should be considered Cell::ALIVE.
 *
 * @author 962940
 * @date March, 2020
 */
#include <fstream>
#include <sstream>
#include "zoo.h"

// Include the minimal number of headers needed to support your implementation.
// #include ...

/**
 * Zoo::glider()
 *
 * Construct a 3x3 grid containing a glider.
 * https://www.conwaylife.com/wiki/Glider
 *
 * @example
 *
 *      // Print a glider in a Grid the size of its bounding box.
 *      std::cout << Zoo::glider() << std::endl;
 *
 *      +---+
 *      | # |
 *      |  #|
 *      |###|
 *      +---+
 *
 * @return
 *      Returns a Grid containing a glider.
 */
Grid Zoo::glider() {
    Grid grid(3);
    grid.set(1, 0, ALIVE);
    grid.set(2, 1, ALIVE);
    grid.set(3, 0, ALIVE);
    grid.set(3, 1, ALIVE);
    grid.set(3, 2, ALIVE);

    return grid;
}

/**
 * Zoo::r_pentomino()
 *
 * Construct a 3x3 grid containing an r-pentomino.
 * https://www.conwaylife.com/wiki/R-pentomino
 *
 * @example
 *
 *      // Print an r-pentomino in a Grid the size of its bounding box.
 *      std::cout << Zoo::r_pentomino() << std::endl;
 *
 *      +---+
 *      | ##|
 *      |## |
 *      | # |
 *      +---+
 *
 * @return
 *      Returns a Grid containing a r-pentomino.
 */
Grid Zoo::r_pentomino() {
    Grid grid(3);
    grid.set(1, 0, ALIVE);
    grid.set(2, 0, ALIVE);
    grid.set(0, 1, ALIVE);
    grid.set(1, 1, ALIVE);
    grid.set(1, 2, ALIVE);

    return grid;
}

/**
 * Zoo::light_weight_spaceship()
 *
 * Construct a 5x4 grid containing a light weight spaceship.
 * https://www.conwaylife.com/wiki/Lightweight_spaceship
 *
 * @example
 *
 *      // Print a light weight spaceship in a Grid the size of its bounding box.
 *      std::cout << Zoo::light_weight_spaceship() << std::endl;
 *
 *      +-----+
 *      | #  #|
 *      |#    |
 *      |#   #|
 *      |#### |
 *      +-----+
 *
 * @return
 *      Returns a grid containing a light weight spaceship.
 */
Grid Zoo::light_weight_spaceship() {
    Grid grid(5, 4);
    grid.set(1, 0, ALIVE);
    grid.set(4, 0, ALIVE);
    grid.set(0, 1, ALIVE);
    grid.set(0, 2, ALIVE);
    grid.set(4, 2, ALIVE);
    grid.set(3, 0, ALIVE);
    grid.set(3, 1, ALIVE);
    grid.set(3, 2, ALIVE);
    grid.set(3, 3, ALIVE);

    return grid;
}

/**
 * Zoo::load_ascii(path)
 *
 * Load an ascii file and parse it as a grid of cells.
 * Should be implemented using std::ifstream.
 *
 * @example
 *
 *      // Load an ascii file from a directory
 *      Grid grid = Zoo::load_ascii("path/to/file.gol");
 *
 * @param path
 *      The std::string path to the file to read in.
 *
 * @return
 *      Returns the parsed grid.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if:
 *          - The file cannot be opened.
 *          - The parsed width or height is not a positive integer.
 *          - Newline characters are not found when expected during parsing.
 *          - The character for a cell is not the ALIVE or DEAD character.
 */
Grid Zoo::load_ascii(std::string filePath) {
    std::ifstream file;
    file.open(filePath);
    Grid newGrid;

    if (!file) {
        throw std::runtime_error("File failed to open");
    }

    if (file.is_open()) {
        std::string line;
        int width = 0, height = 0;
        int lineIndex = 0;
        while ((getline(file, line))) {
            int characterIndex = 0;
            if (lineIndex == 0) {
                std::string temp;
                std::stringstream ss(line);
                while (getline(ss, temp, ' ')) {
                    if (characterIndex == 0)
                        width = std::stoi(temp);
                    else
                        height = std::stoi(temp);

                    characterIndex++;
                }

                if (width < 0 || height < 0) {
                    throw std::runtime_error("Width or Height is a negative number");
                }
                newGrid = Grid(width, height);
                std::cout << "Width: " << width << " Height: " << height;
            } else {
                for (int i = 0; i < line.length(); i++) {
                    if (i >= width)
                        throw std::runtime_error(&"There is a missing new line character on line: "[lineIndex]);

                    std::cout << line[i] << std::endl;
                    if (line[i] == '#')
                        newGrid.set(i, lineIndex - 1, ALIVE);
                    else if (line[i] != ' ') {
                        throw std::runtime_error("File contains invalid string");
                    }
                }
            }
            lineIndex++;
        }

        if (lineIndex - 1 < height) {
            throw std::runtime_error("File ends unexpectedly");
        }

        file.close();
    }

    return newGrid;
}

/**
 * Zoo::save_ascii(path, grid)
 *
 * Save a grid as an ascii .gol file according to the specified file format.
 * Should be implemented using std::ofstream.
 *
 * @example
 *
 *      // Make an 8x8 grid
 *      Grid grid(8);
 *
 *      // Save a grid to an ascii file in a directory
 *      try {
 *          Zoo::save_ascii("path/to/file.gol", grid);
 *      }
 *      catch (const std::exception &ex) {
 *          std::cerr << ex.what() << std::endl;
 *      }
 *
 * @param path
 *      The std::string path to the file to write to.
 *
 * @param grid
 *      The grid to be written out to file.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if the file cannot be opened.
 */
void Zoo::save_ascii(std::string filePath, Grid grid) {
    std::ofstream saveFile(filePath);

    saveFile << grid.get_width() << " " << grid.get_height() << std::endl;
    saveFile << grid.to_string();

    saveFile.close();
}

/**
 * Zoo::load_binary(path)
 *
 * Load a binary file and parse it as a grid of cells.
 * Should be implemented using std::ifstream.
 *
 * @example
 *
 *      // Load an binary file from a directory
 *      Grid grid = Zoo::load_binary("path/to/file.bgol");
 *
 * @param path
 *      The std::string path to the file to read in.
 *
 * @return
 *      Returns the parsed grid.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if:
 *          - The file cannot be opened.
 *          - The file ends unexpectedly.
 */


/**
 * Zoo::save_binary(path, grid)
 *
 * Save a grid as an binary .bgol file according to the specified file format.
 * Should be implemented using std::ofstream.
 *
 * @example
 *
 *      // Make an 8x8 grid
 *      Grid grid(8);
 *
 *      // Save a grid to an binary file in a directory
 *      try {
 *          Zoo::save_binary("path/to/file.bgol", grid);
 *      }
 *      catch (const std::exception &ex) {
 *          std::cerr << ex.what() << std::endl;
 *      }
 *
 * @param path
 *      The std::string path to the file to write to.
 *
 * @param grid
 *      The grid to be written out to file.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if the file cannot be opened.
 */

