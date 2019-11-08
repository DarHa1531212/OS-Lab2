#include <iostream>
using namespace std;

int ressourcesTotal[5] = {12, 20, 14, 8, 16};
int demandeMaximal[5][5];
int compositionObjets[5][5] = {{2, 1, 0, 0, 0},
                               {0, 1, 1, 0, 0},
                               {0, 0, 3, 2, 0},
                               {0, 0, 0, 4, 4},
                               {2, 0, 0, 0, 1}};

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
        } else 
        {
            objetsMaxTemp = (ressourcesTotal[i]/compositionObjets[noObjet][i]);
        }
        
        if (maxObjets > objetsMaxTemp)
        {
            maxObjets = objetsMaxTemp;
        }
    }
    if(maxObjets == 9999)
    {
        maxObjets = 0;
    }
    return maxObjets;
}

/**
* @brief  Ajoute le nombre de ressource necessaire pour creer le maximum d'objet d'un seul type dans
la matrice demandeMaximal
* @param  maxObjet: maximum d'objet d'un seul type que l'on peut creer avec les ressources totales
* @param  noObjet: Le numero de l'objet a creer dans la matrice, sa position.
* @param  nbrRessources: Le nombre de type de ressources disponibles dans le systeme
*/
void AjouterDemandeMaxUnObjet(int maxObjet, int noObjet, int nbrRessources) 
{
    for (int i = 0; i < nbrRessources; i++)
    {
        demandeMaximal[noObjet][i] = maxObjet * compositionObjets[noObjet][i];
    }
}

/**
* @brief  Calcul la demande maximal en ressources de chaque objets selon les ressources totales
* @note   matrice C dans les exemples du professeur
* @param  nbrObjets: Le nombre de type d'objets dans le systeme
* @param  nbrRessources: Le nombre de type de ressources dans le systeme(pas la quantite)
*/
void CalculerDemandeMaximal(int nbrObjets, int nbrRessources) 
{
    for (int j = 0; j < nbrObjets; j++)
    {
        int maxObjetsJ = CalculerMaxObjetsPossiblePour1Thread(j, nbrRessources);
        AjouterDemandeMaxUnObjet(maxObjetsJ, j, nbrRessources);
    }
}



void GenererA() {





}



void CalculerCMoinsA() {





}




int main() {




    return 0;
}