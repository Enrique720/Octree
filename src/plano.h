#ifndef PLANO_H
#define PLANO_H

#include "point.h"

struct plano {
    double a, b, c, d;
};

double getX(plano input, point point) {
    if (input.a == 0) return INF;
    return -(input.b * point.coor[1] + input.c * point.coor[2] + input.d) / input.a;
}

double getY(plano input, point point) {
    if (input.b == 0) return INF;
    return -(input.a * point.coor[0] + input.c * point.coor[2] + input.d) / input.b;
}

double getZ(plano input, point point) {
    if (input.c == 0) return INF;
    return -(input.b * point.coor[1] + input.a * point.coor[0] + input.d) / input.c;
}

bool intersect(plano input, pixel_des quad) {
    point initial = {quad.pi.coor[0], quad.pi.coor[1], quad.pi.coor[2]};
    point end = {quad.pf.coor[0], quad.pf.coor[1], quad.pf.coor[2]};
    if ((input.c == 0 || (getZ(input, initial) >= quad.pi.coor[2]) && (getZ(input, end) <= quad.pf.coor[2]) ||
         (getZ(input, initial) <= quad.pf.coor[2]) && (getZ(input, end) >= quad.pi.coor[2])) &&
        (input.b == 0 || (getY(input, initial) >= quad.pi.coor[1]) && (getY(input, end) <= quad.pf.coor[1]) ||
         (getY(input, initial) <= quad.pf.coor[1]) && (getY(input, end) >= quad.pi.coor[1])) &&
        (input.a == 0 || (getX(input, initial) >= quad.pi.coor[0]) && (getX(input, end) <= quad.pf.coor[0]) ||
         (getX(input, initial) <= quad.pf.coor[0]) && (getX(input, end) >= quad.pi.coor[0]))) {
        return true;
    }
    return false;
}

plano getPlano(point p1, point p2, point p3) {
    plano pl;

    point v1 = p2 - p1;
    point v2 = p3 - p1;
    point cross = v1 * v2;
    point norm = cross.norm();

    pl.a = norm.coor[0];
    pl.b = norm.coor[1];
    pl.c = norm.coor[2];
    pl.d = -(norm.coor[0] * p1.coor[0] + norm.coor[1] * p1.coor[1] + norm.coor[2] * p1.coor[2]);

    return pl;
}

vector <point> getPoints(pixel_des pd, plano pl) {
    vector <point> pts;

    double nx, ny, nz;
    /* Aristas en X*/
    if (getX(pl, {0, pd.pi.coor[1], pd.pi.coor[2]}) != INF) {
        nx = getX(pl, {0, pd.pi.coor[1], pd.pi.coor[2]});
        if (nx >= pd.pi.coor[0] && nx <= pd.pf.coor[0]) pts.push_back({nx, pd.pi.coor[1], pd.pi.coor[2]});
    }
    if (getX(pl, {0, pd.pi.coor[1], pd.pf.coor[2]}) != INF) {
        nx = getX(pl, {0, pd.pi.coor[1], pd.pf.coor[2]});
        if (nx >= pd.pi.coor[0] && nx <= pd.pf.coor[0]) pts.push_back({nx, pd.pi.coor[1], pd.pf.coor[2]});
    }
    if (getX(pl, {0, pd.pf.coor[1], pd.pi.coor[2]}) != INF) {
        nx = getX(pl, {0, pd.pf.coor[1], pd.pi.coor[2]});
        if (nx >= pd.pi.coor[0] && nx <= pd.pf.coor[0]) pts.push_back({nx, pd.pf.coor[1], pd.pi.coor[2]});
    }
    if (getX(pl, {0, pd.pf.coor[1], pd.pf.coor[2]}) != INF) {
        nx = getX(pl, {0, pd.pf.coor[1], pd.pf.coor[2]});
        if (nx >= pd.pi.coor[0] && nx <= pd.pf.coor[0]) pts.push_back({nx, pd.pf.coor[1], pd.pf.coor[2]});
    }

    /* Aristas en Y */
    if (getY(pl, {pd.pi.coor[0], 0, pd.pi.coor[2]}) != INF) {
        ny = getY(pl, {pd.pi.coor[0], 0, pd.pi.coor[2]});
        if (ny >= pd.pi.coor[1] && ny <= pd.pf.coor[1]) pts.push_back({pd.pi.coor[0], ny, pd.pi.coor[2]});
    }
    if (getY(pl, {pd.pi.coor[0], 0, pd.pf.coor[2]}) != INF) {
        ny = getY(pl, {pd.pi.coor[0], 0, pd.pf.coor[2]});
        if (ny >= pd.pi.coor[1] && ny <= pd.pf.coor[1]) pts.push_back({pd.pi.coor[0], ny, pd.pf.coor[2]});
    }
    if (getY(pl, {pd.pf.coor[0], 0, pd.pi.coor[2]}) != INF) {
        ny = getY(pl, {pd.pf.coor[0], 0, pd.pi.coor[2]});
        if (ny >= pd.pi.coor[1] && ny <= pd.pf.coor[1]) pts.push_back({pd.pf.coor[0], ny, pd.pi.coor[2]});
    }
    if (getY(pl, {pd.pf.coor[0], 0, pd.pf.coor[2]}) != INF) {
        ny = getY(pl, {pd.pf.coor[0], 0, pd.pf.coor[2]});
        if (ny >= pd.pi.coor[1] && ny <= pd.pf.coor[1]) pts.push_back({pd.pf.coor[0], ny, pd.pf.coor[2]});
    }

    /* Aristas en Z */
    if (getZ(pl, {pd.pi.coor[0], pd.pi.coor[1], 0}) != INF) {
        nz = getZ(pl, {pd.pi.coor[0], pd.pi.coor[1], 0});
        if (nz >= pd.pi.coor[2] && nz <= pd.pf.coor[2]) pts.push_back({pd.pi.coor[0], pd.pi.coor[1], nz});
    }
    if (getZ(pl, {pd.pi.coor[0], pd.pf.coor[1], 0}) != INF) {
        nz = getZ(pl, {pd.pi.coor[0], pd.pf.coor[1], 0});
        if (nz >= pd.pi.coor[2] && nz <= pd.pf.coor[2]) pts.push_back({pd.pi.coor[0], pd.pf.coor[1], nz});
    }
    if (getZ(pl, {pd.pf.coor[0], pd.pi.coor[1], 0}) != INF) {
        nz = getZ(pl, {pd.pf.coor[0], pd.pi.coor[1], 0});
        if (nz >= pd.pi.coor[2] && nz <= pd.pf.coor[2]) pts.push_back({pd.pf.coor[0], pd.pi.coor[1], nz});
    }
    if (getZ(pl, {pd.pf.coor[0], pd.pf.coor[1], 0}) != INF) {
        nz = getZ(pl, {pd.pf.coor[0], pd.pf.coor[1], 0});
        if (nz >= pd.pi.coor[2] && nz <= pd.pf.coor[2]) pts.push_back({pd.pf.coor[0], pd.pf.coor[1], nz});
    }

    return pts;
}

#endif