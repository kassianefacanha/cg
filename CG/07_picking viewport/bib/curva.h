#ifndef CURVA_H
#define CURVA_H
#include <lampada.h>
#include <Vetor3D.h>
#include <vector>
#include<buda.h>

using namespace std;



class Curva
{


public:
   Camera *camPro = new CameraDistante();
   Buda *buda = new Buda();
    int ic = 0;
    double u = 0;
    vector<vector<double>> Interpoladora = {
            {-4.5, 13.5, -13.5, 4.5},
            {9, -22.5, 18, -4.5},
            {-5.5, 9, -4.5, 1},
            {1, 0, 0, 0}
        };

        vector<vector<double>> Bezier = {
            {2, -2, 1, 1},
            {-3, 3, -2, -1},
            {0, 0, 1, 0},
            {1, 0, 0, 0}
        };

        vector<vector<double>> Hermite = {
            {-1, 3, -3, 1},
            {3, -6, 3, 0},
            {-3, 3, 0, 0},
            {1, 0, 0, 0}
        };
        vector<vector<double>> CatmullRom = {
            {-1/2.0, 3/2.0, -3/2.0, 1/2.0},
            {2/2.0, -5/2.0, 4/2.0, -1/2.0},
            {-1/2.0, 0.0, 1/2.0, 0.0},
            {0.0, 2/2.0, 0.0, 0.0}
        };
        vector<vector<double>> Bspline = {
            {-1/6.0, 3/6.0, -3/6.0, 1/6.0},
            {3/6.0, -6/6.0, 3/6.0, 0},
            {-3/6.0, 0, 3/6.0, 0},
            {1/6.0, 4/6.0, 1/6.0, 0}
        };


    Lampada *lamp = new Lampada();

    Curva();
    vector<vector<double>> Matriz = Interpoladora;
    Vetor3D PT(vector<Vetor3D> pontos, double u, int opc);
    void DesCurva(vector<Vetor3D> pontos, double u);
    void desenhaO(vector<Vetor3D> pontos, double delta_u, CameraDistante *camera);
};

#endif // CURVA_H
