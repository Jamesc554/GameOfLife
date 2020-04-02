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
    grid.set(0, 2, ALIVE);
    grid.set(1, 2, ALIVE);
    grid.set(2, 2, ALIVE);

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
    grid.set(0, 3, ALIVE);
    grid.set(1, 3, ALIVE);
    grid.set(2, 3, ALIVE);
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
Grid Zoo::load_ascii(const std::string& filePath) {
    // First open the file
    std::ifstream file;
    file.open(filePath);
    Grid newGrid;

    // Then we need to check if the file failed to open
    if (!file) {
        throw std::runtime_error("File failed to open");
    }

    // Once we know the file is open
    if (file.is_open()) {
        int width = 0, height = 0;

        // First thing to do is get the width and height values from the top line
        std::string topLine;
        getline(file, topLine);
        std::stringstream ss(topLine);

        getline(ss, topLine, ' ');
        width = stoi(topLine);

        getline(ss, topLine, ' ');
        height = stoi(topLine);

        // Once we have set the width and height, we need to check to make sure the values are valid. e.g. > 0
        if (width <= 0 || height <= 0) {
            file.close();
            throw std::runtime_error("Width or Height have an invalid value, make sure they are both greater than 0");
        }

        newGrid = Grid(width, height);
        std::string line;
        int lineIndex = 0; // lineIndex is the Y-value for the grid we're reading
        // Next, Loop over each line
        while ((getline(file, line))) {
            // Check if the line is longer than expected
            if ((int)line.length() > width) {
                file.close();
                throw std::runtime_error("The line at " + std::to_string(lineIndex) + " was longer than expected");
            }

            if (line.length() > 0) {
                // Loop over each character in the line
                for (int c = 0; c < (int)line.length(); c++) {
                    char sym = line[c];
                    switch (sym) {
                        case '#':
                            // The Cell is alive
                            newGrid.set(c, lineIndex, ALIVE);
                            break;
                        case ' ':
                            // The Cell is dead
                            newGrid.set(c, lineIndex, DEAD);
                            break;
                        default:
                            // The symbol is an invalid value
                            file.close();
                            throw std::runtime_error("There was an invalid symbol found");
                    }
                }
            }
            lineIndex++;
        }
        if (lineIndex + 1 < height) {
            throw std::runtime_error("File ends unexpectedly");
        }
        file.close();
    } else {
        throw std::runtime_error("File failed to open");
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
void Zoo::save_ascii(const std::string& filePath, const Grid& grid) {
    std::ofstream saveFile(filePath);

    if (!saveFile) {
        throw std::runtime_error("File cannot be opened");
    }

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
Grid Zoo::load_binary(const std::string &filePath) {
    Grid newGrid;
    std::ifstream file(filePath, std::ios::in | std::ios::binary);

    if (!file) {
        throw std::runtime_error("File failed to open");
    }

    int width = 0;
    int height = 0;

    file.read(reinterpret_cast<char *>(&width), sizeof(width));
    file.read(reinterpret_cast<char *>(&height), sizeof(height));

    newGrid = Grid(width, height);

    for (int y = 0; y < height; y++) {
        char line;

        if (file.get(line)) {
            for (int x = 0; x < 8; x++) {
                int cell = ((line >> x) & 1);

                int index = x + 8 * y;

                if (index >= width * height) {
                    y = height;
                    break;
                }

                int xCoord = index % width;
                int yCoord = index / width;

                newGrid.set(xCoord, yCoord, cell == 1 ? ALIVE : DEAD);
            }
        } else {
            file.close();
            throw std::runtime_error("File ends wrong boi");
        }
    }

    file.close();

    return newGrid;
}

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
void Zoo::save_binary(const std::string &filePath, const Grid &grid) {
    std::ofstream saveFile(filePath, std::ios::out | std::ios::binary);

    if (!saveFile)
        throw std::runtime_error("Invalid save directory");

    int width = grid.get_width();
    int height = grid.get_height();

    saveFile.write(reinterpret_cast<const char *>(&width), 4);
    saveFile.write(reinterpret_cast<const char *>(&height), 4);

    unsigned char line = 0;
    int size = grid.get_width() * grid.get_height();
    int x = 0;
    for (int i = 0; i < grid.get_height() * grid.get_width(); i++) {
        if (i < size) {
            int currentBit = grid.get(i % grid.get_width(), i / grid.get_width()) == ALIVE ? 1 : 0;
            if (currentBit) {
                line |= (1 << x);
            }
        }

        x++;
        if (x == 8) {
            x = 0;
            saveFile << (line);
            line = 0;
        }
    }

    if (x != 0) {
        saveFile << (line);
        x = 0;
    }

    saveFile.close();
}
