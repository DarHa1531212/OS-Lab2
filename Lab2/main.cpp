#include <iostream>
using namespace std;

int ressourcesTotal[5] = {12, 20, 14, 8, 16};
int C[5][5];

void CalculerC() {

     



}



void GenererA() {

	int ressourcesDispo[5] = { 30, 20, 20, 60, 40 };
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

	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			cout << matriceA[y][x] << " ";
			if (x == 4)
				cout << endl;
		}

	}

}



void CalculerCMoinsA() {





}




int main() {


    GenererA();
    return 0;
}