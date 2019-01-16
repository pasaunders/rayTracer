#include <png.h>

class Sphere
{
private:
    int centerX, centerY;
    int radius;
    //define color here
public:
    Sphere(int, int, int /*color variable here*/);
    ~Sphere();
};

Sphere::Sphere(int xCoordinate, int yCoordinate, int rad /*color variable here*/)
{
    centerX = xCoordinate;
    centerY = yCoordinate;
    radius = rad;
}

Sphere::~Sphere()
{
}
