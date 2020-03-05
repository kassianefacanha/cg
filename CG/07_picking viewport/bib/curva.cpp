#include "curva.h"


Curva::Curva()
{

}
Vetor3D Curva::PT(vector<Vetor3D> pontos, double u, int opc){
    double v[4];
    if(opc == 0){
        double v[4]= {u*u*u, u*u, u,1};
    }
    else if(opc ==1){
        double v[4]= {3*u*u, 2*u, 1,0};
    }

    else{
        double v[4]= {6*u, 2, 0,0};
    }
    float M[4];
       M[0] = v[0]*Matriz[0][0] + v[1]*Matriz[1][0] + v[2]*Matriz[2][0] + v[3]*Matriz[3][0];
       M[1] = v[0]*Matriz[0][1] + v[1]*Matriz[1][1] + v[2]*Matriz[2][1] + v[3]*Matriz[3][1];
       M[2] = v[0]*Matriz[0][2] + v[1]*Matriz[1][2] + v[2]*Matriz[2][2] + v[3]*Matriz[3][2];
       M[3] = v[0]*Matriz[0][3] + v[1]*Matriz[1][3] + v[2]*Matriz[2][3] + v[3]*Matriz[3][3];

       Vetor3D P(0,0,0);
       P.x = M[0]*pontos[0].x + M[1]*pontos[1].x + M[2]*pontos[2].x + M[3]*pontos[3].x;
       P.y = M[0]*pontos[0].y + M[1]*pontos[1].y + M[2]*pontos[2].y + M[3]*pontos[3].y;
       P.z = M[0]*pontos[0].z + M[1]*pontos[1].z + M[2]*pontos[2].z + M[3]*pontos[3].z;

      return P;
   }


void Curva::DesCurva(vector<Vetor3D> pontos, double delta_u){
    for(int i = 0; i<pontos.size();i++){
      vector<Vetor3D> p;
      p.push_back(pontos[i%pontos.size()]);
      p.push_back(pontos[(i+1)%pontos.size()]);
      p.push_back(pontos[(i+2)%pontos.size()]);
      p.push_back(pontos[(i+3)%pontos.size()]);
      double distancia = p[i%pontos.size()].getDistance(p[(i+3)%pontos.size()]);
              for(float u=0; u<=1; u+=delta_u){
                  Vetor3D o = PT(p,u,0);
                  Vetor3D k = PT(p,u,1) * (-1);
                  k.normaliza();
                  Vetor3D up = PT(p,u,2);
                  up.normaliza();
                  Vetor3D i = up ^ k;
                  i.normaliza();
                  Vetor3D j = k ^i;
                  j.normaliza();

                  double t[] = {
                      i.x, j.x, k.x, o.x,
                      i.y, j.y, k.y, o.y,
                      i.z, j.z, k.z, o.z,
                      0,   0,   0,   1,
                  };
                  glPushMatrix();
                      glMultTransposeMatrixd(t);
                      glScalef(0.5, 0.03, delta_u * distancia);
                      lamp->desenha();
                  glPopMatrix();
              }
          }
 }

void Curva::desenhaO(vector<Vetor3D> pontos, double delta_u, CameraDistante *camera){
         vector<Vetor3D> p;
        p.push_back(pontos[ic%pontos.size()]);
        p.push_back(pontos[(ic+1)%pontos.size()]);
        p.push_back(pontos[(ic+2)%pontos.size()]);
        p.push_back(pontos[(ic+3)%pontos.size()]);
        double distancia = p[ic%pontos.size()].getDistance(p[(ic+3)%pontos.size()]);

            Vetor3D o = PT(p,u,0);
            Vetor3D k = PT(p,u,1);
            k.normaliza();
            Vetor3D up = PT(p,u,2);
            up.normaliza();
            Vetor3D i = up ^ k;
            i.normaliza();
            Vetor3D j = (k ^i)*(-1);
            j.normaliza();
            camera->u=up*(-1);
            camera->c=o;
            camera->e=(j-k)*5;

            double t[] = {
                i.x, j.x, k.x, o.x,
                i.y, j.y, k.y, o.y,
                i.z, j.z, k.z, o.z,
                0,   0,   0,   1,
            };
            glPushMatrix();
                glMultTransposeMatrixd(t);

                buda->desenha();
            glPopMatrix();

        u+= delta_u;
        if(u>=1){
            u=0;
            ic= (ic+1)%pontos.size();
        }
        camPro->e = o;
        camPro->c= o+k;
        camPro->u = up;
}
