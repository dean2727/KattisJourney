#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
using namespace std;

// we can just find the minimum of the distances from each vertex of both polygons
// to their nearest lines (naive loop)

// library code from https://vlecomte.github.io/cp-geo.pdf
typedef double T;

struct pt {
    T x, y;
    pt operator+(pt p) {return {x+p.x, y+p.y};}
    pt operator-(pt p) {return {x-p.x, y-p.y};}
    pt operator*(T d) {return {x*d, y*d};}
    pt operator/(T d) {return {x/d, y/d};} // only for floating point
};

bool operator==(pt a, pt b) {return a.x == b.x && a.y == b.y;}
bool operator!=(pt a, pt b) {return !(a == b);}
T sq(pt p) {return p.x*p.x + p.y*p.y;}
double abs(pt p) {return sqrt(sq(p));}
T cross(pt v, pt w) {return v.x*w.y - v.y*w.x;}
T dot(pt v, pt w) {return v.x*w.x + v.y*w.y;}

ostream& operator<<(ostream& os, pt p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

// point to point representation
struct line {
    pt p;
    pt q;
    pt v;
    T c;
    line(pt p, pt q) : p(p), q(q), v(q-p), c(cross(v,p)) {}
};

T side(pt p, line l) {return cross(l.v,p)-l.c;}

bool cmpProj(pt p, pt q, pt v) {
    return dot(v,p) < dot(v,q);
}

double dist(pt p, line l) {return abs(side(p, l)) / abs(l.v);}

double segPoint(pt a, pt b, pt p) {
    if (a != b) {
        line l(a, b);
        if (cmpProj(a, p, l.v) && cmpProj(p, b, l.v)) // if closest to projection
            return dist(p, l); // output distance to line
    }
    return min(abs(p-a), abs(p-b)); // otherwise distance to A or B
}


int main() {
    int t, no, ni, x, y, i, j;
    T ans;
    cin >> t;
    while (t--) {
        vector<pt> innerPoints;
        vector<pt> outterPoints;

        cin >> ni;
        for (i=0;i<ni;i++) {
            cin >> x >> y;
            pt c;
            c.x = x;
            c.y = y;
            innerPoints.push_back(c);
        }

        cin >> no;
        for (i=0;i<no;i++) {
            cin >> x >> y;
            pt c;
            c.x = x;
            c.y = y;
            outterPoints.push_back(c);
        }

        // create lines from the points of the polygons
        vector<line> innerLines;
        vector<line> outterLines;
        for (i=0;i<ni-1;i++) {
            line l(innerPoints[i], innerPoints[i+1]);
            innerLines.push_back(l);
        }
        line l(innerPoints[ni-1], innerPoints[0]);
        innerLines.push_back(l);

        for (i=0;i<no-1;i++) {
            line l2(outterPoints[i], outterPoints[i+1]);
            outterLines.push_back(l2);
        }
        line l2(outterPoints[no-1], outterPoints[0]);
        outterLines.push_back(l2);

        // min radius is half of the smallest distance between a polygon vertex and its closest line
        T maxRad = 0.0;
        T totalMinDist = 1000000.0;
        T minDist, thisDist;
        // first loop through inner poly vertices
        for (i=0;i<innerPoints.size();i++) {
            pt c = innerPoints[i];
            // loop through outter poly lines
            minDist = 1000000.0;
            for (j=0;j<outterLines.size();j++) {
                thisDist = segPoint(outterLines[j].p, outterLines[j].q, c);
                if (thisDist < minDist) minDist = thisDist;
            }
            if (minDist < totalMinDist) totalMinDist = minDist;
        }
        // now loop through outter poly vertices
        for (i=0;i<outterPoints.size();i++) {
            pt c = outterPoints[i];
            // loop through inner poly lines
            minDist = 1000000.0;
            for (j=0;j<innerLines.size();j++) {
                thisDist = segPoint(innerLines[j].p, innerLines[j].q, c);
                if (thisDist < minDist) minDist = thisDist;
            }
            if (minDist < totalMinDist) totalMinDist = minDist;
        }

        cout << fixed << setprecision(8) << totalMinDist / 2 << "\n";
    }
}