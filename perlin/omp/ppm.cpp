#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>

#include "ppm.h"

/**
 * init with default values
 */
void ppm::init() {
    width = 0;
    height = 0;
    max_col_val = 255;
}

/**
 * create a PPM object
 */
ppm::ppm() {
    init();
}

/**
 * create an "epmty" PPM image with a given width and height;the R,G,B arrays are filled with zeros
 */
ppm::ppm(const unsigned int _width, const unsigned int _height) {
    init();
    width = _width;
    height = _height;
    nr_lines = height;
    nr_columns = width;
    size = width*height;

    /**
     * fill r, g and b with 0
     */
    r.resize(size);
    g.resize(size);
    b.resize(size);
}

/**
 * write the PPM image in fname
 */
void ppm::write(const std::string &fname) {
    std::ofstream inp(fname.c_str(), std::ios::out | std::ios::binary);
    if (inp.is_open()) {

        inp << "P6\n";
        inp << width;
        inp << " ";
        inp << height << "\n";
        inp << max_col_val << "\n";

        char aux;
        for (unsigned int i = 0; i < size; ++i) {
            aux = (char) r[i];
            inp.write(&aux, 1);
            aux = (char) g[i];
            inp.write(&aux, 1);
            aux = (char) b[i];
            inp.write(&aux, 1);
        }
    } else {
        std::cout << "Error. Unable to open " << fname << std::endl;
    }
    inp.close();
}
