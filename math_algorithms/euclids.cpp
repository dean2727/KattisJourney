// Euclids algorithm for finding the GDC of a and b
// Assumption: a > b
int GCD(int a, int b) {
    if (b == 0) return a;
    return GCD(b, a % b);
}
