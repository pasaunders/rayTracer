#include <cstdio>
#include <png.h>
#include <string>
#include <iostream>
#include <vector>
#include <cassert>

void write_png_file(std::string file_name, std::vector<unsigned char> const & rows, int numRows)
{
    assert(rows.size() % numRows == 0);
    int individualRowLength = rows.size() / numRows;

    png_byte color_type = PNG_COLOR_TYPE_GRAY;
    png_byte bit_depth = 8;
    std::vector<unsigned char*> row_pointers;
    //png_bytep * row_pointers;

    
    for(size_t i = 0; i < rows.size(); i+=individualRowLength)
    {
        row_pointers.push_back(const_cast<unsigned char *>(&rows[i]));
    }
    
    
    
    
    FILE *fp = fopen (file_name.c_str(), "wb");
    
    //Initialize stuff
    if (!fp) {
        std::cout << "Opening a file went wrong.\n" ;
        abort();
    }

    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    png_infop info_ptr = png_create_info_struct(png_ptr);
    
    if (setjmp(png_jmpbuf(png_ptr))) {
        std::cout << "init io went wrong.\n" ;
        abort();
    }
    
    png_init_io(png_ptr, fp);

    //Write Header
    if (setjmp(png_jmpbuf(png_ptr))) {
    std::cout << "file write went wrong.\n" ;
    abort();
    }
    png_set_IHDR(png_ptr, info_ptr, individualRowLength, numRows,
                bit_depth, color_type, PNG_INTERLACE_NONE,
                PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(png_ptr, info_ptr);
    
    //Write bytes
    if (setjmp(png_jmpbuf(png_ptr))) {
        abort();
    }

    png_write_image(png_ptr, row_pointers.data());
    
    //End write
    if (setjmp(png_jmpbuf(png_ptr))) {
    abort();
    }

    png_write_end(png_ptr, nullptr);
    png_destroy_write_struct(&png_ptr, &info_ptr);
}
