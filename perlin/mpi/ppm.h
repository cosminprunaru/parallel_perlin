/**
 * Process a binary PPM file
 */
#include <vector>
#include <string>

#ifndef PPM_H
#define PPM_H

class ppm {
    void init();
    
    /**
     * info about the PPM file (height and width)
     */
    unsigned int nr_lines;
    unsigned int nr_columns;

public:
    /**
     * arrays for storing the R,G,B values
     */
    std::vector<unsigned char> r;
    std::vector<unsigned char> g;
    std::vector<unsigned char> b;
    
    unsigned int height;
    unsigned int width;
    unsigned int max_col_val;
    
    /**
     * total number of elements (pixels)
     */
    unsigned int size;

    ppm();
    
    /**
     * create an "epmty" PPM image with a given width and height;the R,G,B arrays are filled with zeros
     */
    ppm(const unsigned int _width, const unsigned int _height);
    
    /**
     * write the PPM image in fname
     */
    void write(const std::string &fname);
};

#endif
