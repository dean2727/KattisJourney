#include <iostream>
#include <cmath>
#include <ostream>
using namespace std;

// can add on to this for different math things
// see https://vlecomte.github.io/cp-geo.pdf for better code

// represents a point/vector
class Coord2D {
public:
    double x = 0.0;
    double y = 0.0;

    double magnitude() {
        return sqrt(x*x + y*y);
    }

    // normalize vector by dividing coordinates by magnitude
    void normalize() {
        double m = magnitude();
        // cant divide by 0
        if (m == 0.0) return;
        x /= m;
        y /= m;
    }
};

double dist(Coord2D a, Coord2D b) {
    return sqrt(pow(a.x-b.x, 2) + pow(a.y-b.y, 2));
}

ostream& operator<<(ostream& os, Coord2D p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

Coord2D operator-(Coord2D a, Coord2D b) {
    Coord2D ret;
    ret.x = a.x - b.x;
    ret.y = a.y - b.y;
    return ret;
}

Coord2D operator+(Coord2D a, Coord2D b) {
    Coord2D ret;
    ret.x = a.x + b.x;
    ret.y = a.y + b.y;
    return ret;
}

Coord2D operator*(Coord2D a, double b) {
    Coord2D ret;
    ret.x = a.x * b;
    ret.y = a.y * b;
    return ret;
}

Coord2D operator/(Coord2D a, double b) {
    Coord2D ret;
    ret.x = a.x / b;
    ret.y = a.y / b;
    return ret;
}

double dot(Coord2D a, Coord2D b) {
    return a.x*b.x + a.y*b.y;
}

// angle = dotproduct / magnitudes
// angle = arccos(a dot b)
double angle(Coord2D a, Coord2D b) {
    a.normalize();
    b.normalize();
    return acos(dot(a, b));
}

// cross product of 2 vectors is positive if turning left,
// negative if turning right, and 0 otherwise
double xprod(Coord2D a, Coord2D b) {
    return a.x*b.y - b.x*a.y;
}

// cross product of 3 points
// as I go from a to b and then to c, is it right or left?
double xprod(Coord2D a, Coord2D b, Coord2D c) {
    Coord2D v1, v2;
    v1 = b-a;
    v2 = c-b;
    return(xprod(v1, v2));
}

// area of parallelogram is cross product of 2 vectors
// divide this by 2 to get area of the triangle
// this is a signed area, so use abs()
double triarea(Coord2D a, Coord2D b, Coord2D c) {
    return abs(xprod(a, b, c) / 2.0);
}

// point and ray representation of a line
class Line {
    // start point
    Coord2D p1;
    // end point
    Coord2D p2;
    // vector to point from p1 to p2
    Coord2D v;

    Line(Coord2D a, Coord2D b) {
        p1 = a;
        p2 = b;
        v = b-a;
    }
};

// intersection routine. if we intersect 2 lines, we get a point
Coord2D intersect(Line L1, Line L2) {
    Coord2D ret;

    // p1 + s * v1 = p2 + t * v2
    // p1x + s * v1x = p2x + t * v2x
    // p1y + s * v1y = p2y + t * v2y
    // now there are 2 unknowns (s and t) with 2 equations
    // s = (p1y * v2x + p2x * v2y - p1x * v2y - p2y * v2x) / (v1x * v2y - v1y * v2x)
    // t = (p1y * v1x + p2x * v1y - p1x * v1y - p2y * v1x) / (v1x * v2y - v1y * v2x)

    // consider if the 2 lines are parallel (denominator for s and t is 0), if so, infinity
    double denominator = L1.v.x * L2.v.y - L1.v.y * L2.v.x;
    if (denominator == 0) {
        ret.x = 100000000.0;
        ret.y = 100000000.0;
        return ret;
    }

    double sNumerator = L1.p1.y * L2.v.x + L2.p1.x * L2.v.y - L1.p1.x * L2.v.y - L2.p1.y * L2.v.x;
    double tNumerator = L1.p1.y * L1.v.x + L2.p1.x * L1.v.y - L1.p1.x * L1.v.y - L2.p1.y * L1.v.x;
    double s = sNumerator / denominator;
    double t = tNumerator / denominator;

    // plug in s and t and return the coordinate
}

// get distance from the point to the line
double dist(Coord2D p, Line L) {
    // Form vector from p1 of L to p – call it w
    Coord2D w = p - L.p1;

    // Compute a unit-length vector in the same direction as v
    Coord2D unitv = L.v;
    unitv.normalize();

    // Compute dot product of w and v’ (the amount of w projected in the direction of v)
    // if L is a line segment, would need to check if 0 <= u <= 1
    double u = dot(w, unitv);
    // The point a = p1+uv’ is the nearest point on the line to the point q
    Coord2D a = L.p1 + unitv * u;
    // So, just compute distance from a to p
    return dist(a, p);
}

// can make a polygon class, and the area would be all the triangle areas summed up

int main() {
    Coord2D a, b, c, d;
    cin >> a.x >> a.y;
    cin >> b.x >> b.y;
    cin >> c.x >> c.y;
    cout << "Point a: " << a << endl;
    cout << "Point b: " << b << endl;
    cout << "Point c: " << c << endl;
    cout << "Distance from a to b = " << dist(a, b) << endl;
    cout << "Distance from b to c = " << dist(b, c) << endl;
    cout << "Distance from a to c = " << dist(a, c) << endl;
    Coord2D v1, v2;
    v1 = b - a;
    v2 = c - b;
    cout << "v1: "<< v1 << endl;
    cout << "v2: "<< v2 << endl;
    // angle in degrees (remember formula for econverting radians to degrees)
    cout << "Angle between v1 and v2 is: " << angle(v1, v2)/3.14159265*180.0 << " degrees" << endl;
    cout << "Cross product a to b to c: " << xprod(a, b, c) << endl;
    cout << "Area of triangle a-b-c: " << triarea(a, b, c) << endl;
    cout << endl << "NORMALIZING!" << endl;
    v1.normalize();
    v2.normalize();
    cout << "v1: "<< v1 << endl;
    cout << "v2: "<< v2 << endl;
}