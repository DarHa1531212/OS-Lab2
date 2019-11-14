#include <iostream>
using namespace std;

int ressourcesTotal[5] = {12, 20, 14, 8, 16};
int demandeMaximale[5][5];
int allocation[5][5];

void CalculerC() {





}



void GenererA() {





}



void CalculerCmoinsA(int matriceTemporairePourCmoinsA[5][5])
{

    for (int x = 0; x < 5; x++)
    {

        for (int y = 0; y < 5; y++)
        {

            matriceTemporairePourCmoinsA[x][y] = (demandeMaximale[x][y] - allocation[x][y]);

        }

    }

}


void CalculerV(int matriceTemporairePourV[5])
{


    for (int x = 0; x < 5; x++)
    {

        int sommeColonneMatriceAllocation=0;

        for (int y = 0; y < 5; y++)
        {

            sommeColonneMatriceAllocation+=allocation[y][x];

        }

        matriceTemporairePourV[x]=ressourcesTotal[x]-sommeColonneMatriceAllocation;


    }


}




int main() {

 




    return 0;
}