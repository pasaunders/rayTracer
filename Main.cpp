#include <vector>
#include "View/write.h"

int main(int argc, char const *argv[])
{
    std::vector<unsigned char> rows;
    
    for(size_t i = 0; i < 100; i++)
    {
        rows.push_back(50);
    }
    
    write_png_file("defaultName.png", rows, 10);
    return 0;
}
