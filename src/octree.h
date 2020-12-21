#ifndef QUADTREE_QUADTREE_H
#define QUADTREE_QUADTREE_H
#include "plano.h"
#include "point.h"
#include "functions.h"

using namespace cimg_library;


class Octree {
    pixel_des root;
    string filename;
    ifstream file;
public:

    Octree(string _filename) : filename(_filename) {
        file.open(filename);
        file.seekg(0, ios::end);
        int amount = file.tellg() / sizeof(pixel_des);
        file.seekg((amount - 1) * sizeof(pixel_des));
        file.read((char *) &root, sizeof(pixel_des));
    }

    void fill(CImg<unsigned char> &ans, vector <point> points, int reflect) {

        int distXmin, distZmin, distYmin;
        distXmin = distZmin = distYmin = 1000;
        int distXmax = 0, distYmax = 0, distZmax = 0;

        for (auto it:points) {
            distXmin = min(distXmin, int(it.coor[0]));
            distYmin = min(distYmin, int(it.coor[1]));
            distZmin = min(distZmin, int(it.coor[2]));
            distXmax = max(distXmax, int(it.coor[0]));
            distYmax = max(distYmax, int(it.coor[1]));
            distZmax = max(distZmax, int(it.coor[2]));
        }
        int distX = (abs(distXmax - distXmin));
        int distY = (abs(distYmax - distYmin));
        int distZ = (abs(distZmax - distZmin));

        switch (reflect) {
            case 0:  /* Proyeccion en plano XY */
                for (int i = 0; i < distX; i++) {
                    for (int j = 0; j < distY; j++) {
                        ans(distXmin + i, distYmin + j) = 255;
                    }
                }
                break;
            case 1:  /* Proyeccion en plano YZ */
                for (int i = 0; i < distY; i++) {
                    for (int j = 0; j < min(distZ, 39 - distZmin); j++) {
                        ans(distYmin + i, distZmin + j) = 255;
                    }
                }
                break;
            case 2:  /* Proyeccion en plano XZ */
                for (int i = 0; i < distX; i++) {
                    for (int j = 0; j < min(distZ, 39 - distZmin); j++) {
                        ans(distXmin + i, distZmin + j) = 255;
                    }
                }
                break;
        }

    }

    void get_cut(plano &input, uint64_t pos, CImg<unsigned char> &ans, int &reflect) {
        pixel_des temp;
        file.seekg(pos);
        file.read((char *) &temp, sizeof(pixel_des));
        if (intersect(input, temp)) {
            if (temp.isLeaf) {
                auto pts = getPoints({temp.pi, temp.pf}, input);
                if (pts.size() == 6) {
                    pts.erase(pts.begin() + 2);
                    pts.erase(pts.begin() + 2);
                }
                fill(ans, pts, reflect);
            } else {
                for (int i = 0; i < 8; i++) {
                    if (temp.children[i] != -1) {
                        get_cut(input, temp.children[i], ans, reflect);
                    }
                }
            }
        }
    }

    CImg<unsigned char> Get_Cut(double w, double h, double d, double angle1, double angle2) {
        /* obtenemos los puntos y el plano que intersectan con el poliedro */
        point p1 = {w / 2, h / 2, d / 2};
        point p2 = {w / 2 + cos(PI + angle1), h / 2, d / 2 + sin(PI + angle1)};
        point p3 = {w / 2, h / 2 + cos(PI + angle2), d / 2 + sin(PI + angle2)};
        plano pl = getPlano(p1, p2, p3);

        auto pts = getPoints({{0, 0, 0},
                              {h, w, d}}, pl);
        /* se obtiene el plano por el cual vamos a hacer la reflexion. */

        double umbral = d / w * PI / 4;
        int reflect = 1;
        if (angle1 <= umbral && angle2 <= umbral)
            reflect = 0;
        else if (angle1 > umbral && angle2 < umbral)
            reflect = 1;
        else if (angle1 < umbral && angle2 > umbral)
            reflect = 2;
        else if (angle1 > angle2)
            reflect = 1;
        else
            reflect = 2;

        int wf = 1000, df = 1000, wfmax = 0, dfmax = 0;
        /* Se crea la imagen con respecto a la reflexion */
        auto points = getPoints({{0, 0, 0},
                                 {h, w, d}}, pl);

        int distXmin, distZmin, distYmin;
        distXmin = distZmin = distYmin = 1000;
        int distXmax = 0, distYmax = 0, distZmax = 0;

        for (auto it:points) {
            distXmin = min(distXmin, int(it.coor[0]));
            distYmin = min(distYmin, int(it.coor[1]));
            distZmin = min(distZmin, int(it.coor[2]));
            distXmax = max(distXmax, int(it.coor[0]));
            distYmax = max(distYmax, int(it.coor[1]));
            distZmax = max(distZmax, int(it.coor[2]));
        }
        int distX = (abs(distXmax - distXmin));
        int distY = (abs(distYmax - distYmin));
        int distZ = (abs(distZmax - distZmin));
        /* Se obtienen las dimensiones */
        switch (reflect) {
            case 0: {
                wf = distX;
                df = distY;
                break;
            };
            case 1: {
                wf = distY;
                df = distZ;
                break;
            };
            case 2: {

                wf = distX;
                df = distZ;
                break;
            }
        }
        CImg<unsigned char> ans(wf, df, 1, 1, 0);
        /* Se llama a la funcion que realiza todo el pintado de la nueva imagen */
        file.seekg(0, ios::end);
        int pos = int(file.tellg()) - int(sizeof(pixel_des));
        get_cut(pl, pos, ans, reflect);

        return ans;
    }

    int bfs(int pos,int height){
        priority_queue<pair<int,int>> q;
        q.push({0,pos});
        while(!q.empty()){
            auto temp = q.top();
            q.pop();
            file.seekg(temp.second,ios::beg);
            file.read((char*)&root,sizeof(pixel_des));
            for(int i=0;i<8;i++){
                if(root.children[i]!=-1)
                    q.push({temp.first-1,root.children[i]});
                    if(-(temp.first-1)>height)height= -(temp.first-1);
            }
        }
        return height;
    }

    int getRam(){
        int height=0;
        file.seekg(0, ios::end);
        int pos = int(file.tellg()) - int(sizeof(pixel_des));
        return bfs(pos,height);
    }



};

CImg<unsigned char>
Get_Cut(double w, double h, double d, double angle1, double angle2, CImg<unsigned char> &InitImage) {
    point p1 = {w / 2, h / 2, d / 2};
    point p2 = {w / 2 + cos(PI + angle1), h / 2, d / 2 + sin(PI + angle1)};
    point p3 = {w / 2, h / 2 + cos(PI + angle2), d / 2 + sin(PI + angle2)};
    plano pl = getPlano(p1, p2, p3);

    auto pts = getPoints({{0, 0, 0},
                          {h, w, d}}, pl);
    /* Se obtiene el plano por el cual vamos a hacer la reflexion. */
    double umbral = d / w * PI / 4;
    int reflect = 1;
    if (angle1 <= umbral && angle2 <= umbral) {
        reflect = 0;
    } else if (angle1 > umbral && angle2 < umbral) {
        reflect = 1;
    } else if (angle1 < umbral && angle2 > umbral) {
        reflect = 2;
    } else if (angle1 > angle2) {
        reflect = 1;
    } else {
        reflect = 2;
    }
    int wf = 1000, df = 1000, wfmax = 0, dfmax = 0;
    /* Se crea la imagen con respecto a la reflexion */
    auto points = getPoints({{0, 0, 0},
                             {h, w, d}}, pl);
    int distXmin, distZmin, distYmin;
    distXmin = distZmin = distYmin = 1000;
    int distXmax = 0, distYmax = 0, distZmax = 0;
    for (auto it:points) {
        distXmin = min(distXmin, int(ceil(it.coor[0])));
        distYmin = min(distYmin, int(ceil(it.coor[1])));
        distZmin = min(distZmin, int(ceil(it.coor[2])));
        distXmax = max(distXmax, int(ceil(it.coor[0])));
        distYmax = max(distYmax, int(ceil(it.coor[1])));
        distZmax = max(distZmax, int(ceil(it.coor[2])));
    }
    int distX = (abs(distXmax - distXmin));
    int distY = (abs(distYmax - distYmin));
    int distZ = (abs(distZmax - distZmin));

    switch (reflect) {
        case 0: {
            wf = distX;
            df = distY;
            break;
        };
        case 1: {
            wf = distY;
            df = distZ;
            break;
        };
        case 2: {

            wf = distX;
            df = distZ;
            break;
        }
    }

    CImg<unsigned char> ans(wf, df, 1, 1, 0);  /* Imagen Final */

    switch (reflect) {
        case 0: {  
            for (int i = 0; i < distX; i++) {
                for (int j = 0; j < distY; j++) {
                    InitImage(distXmin + i, distYmin + j, ceil(getZ(pl, {distXmin + i, distYmin + j, 0})));
                    ans(distXmin + i, distYmin + j) = InitImage(distXmin + i, distYmin + j,
                                                                ceil(getZ(pl, {distXmin + i, distYmin + j, 0})));
                }
            }
            break;
        };
        case 1: { 
            for (int i = 0; i < distY; i++) {
                for (int j = 0; j < min(distZ, 39 - distZmin); j++) {
                    ans(distYmin + i, distZmin + j) = InitImage(ceil(getX(pl, {0, distYmin + i, distZmin + j})),
                                                                distYmin + i, distZmin + j);
                }
            }
            break;
        };
        case 2: { 
            for (int i = 0; i < distX; i++) {
                for (int j = 0; j < min(distZ, 39 - distZmin); j++) {
                    int y = max(0, int(ceil(getY(pl, {distXmin + i, 0, distZmin + j}))));
                    ans(distXmin + i, distZmin + j) = InitImage(distXmin + i, y, distZmin + j);

                }
            }
            break;
        }
    }
    return ans;


}

int64_t insert(point pi, point pf, CImg<unsigned char> &image, ofstream &output_file) {
    int color = image(pi.coor[1], pi.coor[0], pi.coor[2]);
    bool unique = isColorUnique(pi, pf, color, image);
    pixel_des pd = {pi, pf, false};
    if (unique) {
        if (color == 255) {
            output_file.seekp(0, ios::end);
            int64_t size = output_file.tellp();
            pd.isLeaf = true;
            output_file.write((char *) &pd, sizeof(pixel_des));
            return size;
        }
    } else {
        int xi = pi.coor[0];
        int yi = pi.coor[1];
        int zi = pi.coor[2];
        int xf = pf.coor[0];
        int yf = pf.coor[1];
        int zf = pf.coor[2];
        int mx = (xf + xi) / 2;
        int my = (yf + yi) / 2;
        int mz = (zf + zi) / 2;
        if (xi != mx && yi != my && zi != mz) pd.children[0] = insert({xi, yi, zi}, {mx, my, mz}, image, output_file);
        if (xi != mx && yi != my && mz != zf) pd.children[1] = insert({xi, yi, mz}, {mx, my, zf}, image, output_file);
        if (xi != mx && my != yf && zi != mz) pd.children[2] = insert({xi, my, zi}, {mx, yf, mz}, image, output_file);
        if (xi != mx && my != yf && mz != zf) pd.children[3] = insert({xi, my, mz}, {mx, yf, zf}, image, output_file);
        if (mx != xf && yi != my && zi != mz) pd.children[4] = insert({mx, yi, zi}, {xf, my, mz}, image, output_file);
        if (mx != xf && yi != my && mz != zf) pd.children[5] = insert({mx, yi, mz}, {xf, my, zf}, image, output_file);
        if (mx != xf && my != yf && zi != mz) pd.children[6] = insert({mx, my, zi}, {xf, yf, mz}, image, output_file);
        if (mx != xf && my != yf && mz != zf) pd.children[7] = insert({mx, my, mz}, {xf, yf, zf}, image, output_file);
        output_file.seekp(0, ios::end);
        int64_t size = output_file.tellp();
        output_file.write((char *) &pd, sizeof(pixel_des));
        return size;
    }
    return -1;
}

void insert(CImg<unsigned char> &image, string filename) {
    int w = image.width();
    int h = image.height();
    int d = image.depth();
    ofstream output_file(filename, ios::binary | ios::trunc);
    insert({0, 0, 0}, {h, w, d}, image, output_file);
}

CImg<unsigned char> reconstruir(int w, int h, int d, string filename) {
    ifstream input_file(filename, ios::binary);
    pixel_des pd;
    CImg<unsigned char> R(w, h, d, 1, 0);
    while (input_file.read((char *) &pd, sizeof(pixel_des))) {
        for (int i = pd.pi.coor[0]; i < pd.pf.coor[0]; i++) {
            for (int j = pd.pi.coor[1]; j < pd.pf.coor[1]; j++) {
                for (int k = pd.pi.coor[2]; k < pd.pf.coor[2]; k++) {
                    R(j, i, k) = 255;
                }
            }
        }
    }
    return R;
}


#endif //QUADTREE_QUADTREE_H