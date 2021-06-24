#include <iostream>
#include <vector>
#include <math.h>
#include <set>
using namespace std;

// library code from https://vlecomte.github.io/cp-geo.pdf
// page 56
typedef double T;

struct pt {
    T x, y;
    pt operator+(pt p) {return {x+p.x, y+p.y};}
    pt operator-(pt p) {return {x-p.x, y-p.y};}
    pt operator*(T d) {return {x*d, y*d};}
    pt operator/(T d) {return {x/d, y/d};} // only for floatingpoint
};

bool operator==(pt a, pt b) {return a.x == b.x && a.y == b.y;}
bool operator!=(pt a, pt b) {return !(a == b);}
T sq(pt p) {return p.x*p.x + p.y*p.y;}
double abs(pt p) {return sqrt(sq(p));}
T cross(pt v, pt w) {return v.x*w.y - v.y*w.x;}
T dot(pt v, pt w) {return v.x*w.x + v.y*w.y;}
T orient(pt a, pt b, pt c) {return cross(b-a,c-a);}

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

bool properInter(pt a, pt b, pt c, pt d, pt &out) {
    double oa = orient(c,d,a),
            ob = orient(c,d,b),
            oc = orient(a,b,c),
            od = orient(a,b,d);

    // Proper intersection exists iff opposite signs
    if (oa*ob < 0 && oc*od < 0) {
        out = (a*ob - b*oa) / (ob-oa);
        return true;
    }
    return false;
}

// slope of a line
double slope(line l) { return (l.q.y - l.p.y) / (l.q.x - l.p.x); }

int main() {
    int n;
    cin >> n;
    while (n) {
        double x1, y1, x2, y2;
        int triangles = 0;

        // edge case: only 1 or 2 lines, obviously theres no triangles
        if (n == 1) {
            cin >> x1 >> y1 >> x2 >> y2;
            cout << "0\n";
            continue;
        }
        if (n == 2) {
            cin >> x1 >> y1 >> x2 >> y2;
            cin >> x1 >> y1 >> x2 >> y2;
            cout << "0\n";
            continue;
        }

        vector<line> lines;
        for (int i=0;i<n;i++) {
            cin >> x1 >> y1 >> x2 >> y2;
            pt p; p.x = x1; p.y = y1;
            pt q; q.x = x2; q.y = y2;
            line l(p, q);
            lines.push_back(l);
        }

        // loop through each line, then loop through all the lines it intersects with, 
        // and all the lines THOSE intersect with, and see if this 3rd line intersects with the first
        int l1, l2, l3;
        set<line> traversed;
        pt inter;
        for (l1 = 0; l1 < n; l1++) {
            pt A = lines[l1].p;
            pt B = lines[l1].q;
            for (l2 = l1+1; l2 < n; l2++) {
                pt C = lines[l2].p;
                pt D = lines[l2].q;
                if (properInter(A, B, C, D, inter)) {
                    for (l3 = l2+1; l3 < n; l3++) {
                        pt E = lines[l3].p;
                        pt F = lines[l3].q;
                        if (properInter(C, D, E, F, inter)) {
                            // do A B and E F cross? then we have a triangle
                            if (properInter(A, B, E, F, inter)) {
                                triangles++;
                            }
                        }
                    }
                }
            } 
        }

        cout << triangles << "\n";
        cin >> n;
    }
}