#include <iostream>
using namespace std;

int ressourcesTotal[5] = {30, 20, 20, 60, 40};

int demandeMaximal[5][5];
int compositionObjets[5][5] = {{2, 1, 0, 0, 0},
							   {0, 1, 1, 0, 0},
							   {0, 0, 3, 2, 0},
							   {0, 0, 0, 4, 4},
							   {2, 0, 0, 0, 1}};


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

/**
* @brief  Calcul le maximum d'objet d'un seul type que l'on peut creer avec les ressources
* dans le systeme
* @param  noObjet: Le numero de l'objet a creer dans la matrice, sa position.
* @param  nbrRessources: Le nombre de type de ressources disponibles dans le systeme
* @retval retourne le maximum d'objet du type du noObjet que l'on peut creer
*/
int CalculerMaxObjetsPossiblePour1Thread(int noObjet, int nbrRessources)
{
	int maxObjets = 9999;

	for (int i = 0; i < nbrRessources; i++)
	{
		int objetsMaxTemp;
		if (compositionObjets[noObjet][i] == 0)
		{
			continue;
		}
		else
		{
			objetsMaxTemp = (ressourcesTotal[i] / compositionObjets[noObjet][i]);
		}

		if (maxObjets > objetsMaxTemp)
		{
			maxObjets = objetsMaxTemp;
		}
	}
	if (maxObjets == 9999)
	{
		maxObjets = 0;
	}
	return maxObjets;
}

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