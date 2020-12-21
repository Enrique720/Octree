#ifndef POINT_H
#define POINT_H
#define INF 10000000
#define PI 3.14159265

#include <bits/stdc++.h>

using namespace std;


struct point {
    double coor[3];

    point operator+(const point &pd) {
        point res;
        for (int i = 0; i < 3; i++) {
            res.coor[i] = coor[i] + pd.coor[i];
        }
        return res;
    }

    point operator-(const point &pd) {
        point res;
        for (int i = 0; i < 3; i++) {
            res.coor[i] = coor[i] - pd.coor[i];
        }
        return res;
    }

    point operator*(const point &pd) {
        point res;
        res.coor[0] = coor[1] * pd.coor[2] - coor[2] * pd.coor[1];
        res.coor[1] = coor[2] * pd.coor[0] - coor[0] * pd.coor[2];
        res.coor[2] = coor[0] * pd.coor[1] - coor[1] * pd.coor[0];
        return res;
    }

    bool operator<(const point &pd) {
        return (coor[0] * coor[0] + coor[1] * coor[1] + coor[2] * coor[2]) <
               (pd.coor[0] * pd.coor[0] + pd.coor[1] * pd.coor[1] + pd.coor[2] * pd.coor[2]);
    }

    point norm() {
        point res;
        double sum = 0;
        for (int i = 0; i < 3; i++) {
            sum += coor[i] * coor[i];
        }
        double div = sqrt(sum);
        for (int i = 0; i < 3; i++) {
            res.coor[i] = coor[i] / div;
        }
        return res;
    }

    double dist(point b) {
        double res = 0;
        for (int i = 0; i < 3; i++) {
            res += abs((b.coor[i] - coor[i]) * (b.coor[i] - coor[i]));
        }
        return sqrt(res);
    }

    point operator/(double b) {
        point res;
        for (int i = 0; i < 3; i++) {
            res.coor[i] = coor[i] / b;
        }
        return res;
    }

    point dot(double b) {
        point res;
        for (int i = 0; i < 3; i++) {
            res.coor[i] = coor[i] * b;
        }
        return res;
    }

};

struct pixel_des {
    point pi, pf;
    bool isLeaf;
    int64_t children[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
};
#endif