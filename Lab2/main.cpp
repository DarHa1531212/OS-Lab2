#include <iostream>
using namespace std;

int ressourcesTotal[5] = {30, 20, 20, 60, 40};
int allocation[5][5];
int demandeMaximal[5][5];
int compositionObjets[5][5] = {{2, 1, 0, 0, 0},
							   {0, 1, 1, 0, 0},
							   {0, 0, 3, 2, 0},
							   {0, 0, 0, 4, 4},
							   {2, 0, 0, 0, 1}};


//Génère le vecteur aléatoire de demande de créatio des objes et le retourne
vector<int> GenererVecteurDemandeCreationObjet()
{

    vector<int> DemandeCreationObjet vector<int>(5);

    //loop pour remplir le vecteur
    for(int x=0; x<5; x++)
    {
        int y=rand(0,6);
        DemandeCreationObjet.at(x)=y;


    }

    return DemandeCreationObjet;

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

/**
 * @brief Génère l'état initial de la matrice A pour le début d'execution du programme
 * 
 */
void GenererA()
{

	int ressourcesDispo[5] = {30, 20, 20, 60, 40};
	int matriceA[5][5];
	int sommeRessourcesDemandees;
	bool capaciteRespectee = false;

	//itère pour chaque ressource
	for (int j = 0; j < 5; j++)
	{
		capaciteRespectee = false;

		while (!capaciteRespectee)
		{
			sommeRessourcesDemandees = 0;
		}
		// cette boucle itère au travers des différents threads et assigne une ressource "claim" pour le début du programme
		for (int i = 0; i < 5; i++)
		{
			int v1 = rand() % ressourcesDispo[j];
			matriceA[i][j] = v1;
			sommeRessourcesDemandees += v1;
		}

		if (sommeRessourcesDemandees <= ressourcesDispo[j])
			capaciteRespectee = true;
	}
}

//Calcule case par case la différence entre demandeMaximal et allocation
void CalculerCmoinsA(int matriceTemporairePourCmoinsA[5][5])
{

	for (int x = 0; x < 5; x++)
	{

		for (int y = 0; y < 5; y++)
		{

			matriceTemporairePourCmoinsA[x][y] = (demandeMaximal[x][y] - allocation[x][y]);
		}
	}
}

//La somme de chaque colonne de la matrice allocation
void CalculerV(int matriceTemporairePourV[5])
{

	for (int x = 0; x < 5; x++)
	{

		int sommeColonneMatriceAllocation = 0;

		for (int y = 0; y < 5; y++)
		{

			sommeColonneMatriceAllocation += allocation[y][x];
		}

		matriceTemporairePourV[x] = ressourcesTotal[x] - sommeColonneMatriceAllocation;
	}
}

int main()
{

	return 0;
}