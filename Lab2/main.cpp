#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

/*
 * ressources totales disponibles dans le système
 */
int ressourcesTotales[5] = {30, 20, 20, 60, 40};

/**
 * @brief  la cantité d'objets de chaque type créé. Le programme s'arrête lorsque au moins 20 objets de chaque type est créé
 */
int objetsCrees[5] = {0, 0, 0, 0, 0};


/*
 * ce que tu veux allouer pour chaque thread
*/
int allocation[5][5];

int ressourcesNonAlloueesDiponible[5];

/*
 * les demandes maximales que tu peux faire pour chaque thread
 * matrice C dans les notes de cours
 */
int demandeMaximal[5][5] = {{24, 11, 0,  0,  0},
                            {0,  16, 16, 0,  0,},
                            {0,  0,  14, 8,  0},
                            {0,  0,  0,  36, 36},
                            {26, 0,  0,  0,  11}};

/*
 * Le nombre de ressources nécessaires pour la création de chaque objet
 */
int compositionObjets[5][5] = {{2, 1, 0, 0, 0},
                               {0, 1, 1, 0, 0},
                               {0, 0, 3, 2, 0},
                               {0, 0, 0, 4, 4},
                               {2, 0, 0, 0, 1}};


/**
 * @brief Vérifie si une demande de création d'objets peut dépasser les ressources maximales dans le système
 *
 * @param demandeCreation le nombre d'objets de chaque type devant être créé
 * @return true: la demande ne dépasse pas les ressources du système
 * @return false: la demande dépasse les ressources du système
 */
bool VerifierDepassementRessources(vector<int> demandeCreation) {
    // les ressources sont dans l'ordre, le chaîne, le bois, le fer, l'or et le cuivre
    int demandeRessourcesTotale[5] = {0, 0, 0, 0, 0};

    //les ressources utilisées pour créer un baton, soit 2 chaîne et un bois
    demandeRessourcesTotale[0] += 2 * demandeCreation[0];
    demandeRessourcesTotale[1] += demandeCreation[0];

    //les ressources utilisées pour créer une flèche, soit 1 bois et un fer
    demandeRessourcesTotale[1] += demandeCreation[1];
    demandeRessourcesTotale[2] += demandeCreation[1];

    //les ressources utilisées pour créer une épé, soit 3 fer et 2 or
    demandeRessourcesTotale[2] += 3 * demandeCreation[2];
    demandeRessourcesTotale[3] += 2 * demandeCreation[2];

    //les ressources utilisées pour créer une couronne, soit 4 or et 4 cuivre
    demandeRessourcesTotale[3] += 4 * demandeCreation[3];
    demandeRessourcesTotale[4] += 4 * demandeCreation[3];

    //les ressources utilisées pour créer un bracelet, soit 1 cuivre et 2 chaîne
    demandeRessourcesTotale[4] += demandeCreation[4];
    demandeRessourcesTotale[0] += 2 * demandeCreation[4];

    for (int i = 0; i < 5; i++) {
        if (demandeRessourcesTotale[i] > ressourcesTotales[i])
            return false;
    }

    return true;
}

//Génère le vecteur aléatoire de demande de créatio des objes et le retourne
vector<int> GenererVecteurDemandeCreationObjet() {

    vector<int> DemandeCreationObjet(5);

    //loop pour remplir le vecteur
    for (int x = 0; x < 5; x++) {
        int y = rand() % 6;
        DemandeCreationObjet.at(x) = y;


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
int CalculerMaxObjetsPossiblePour1Thread(int noObjet, int nbrRessources) {
    int maxObjets = 9999;

    for (int i = 0; i < nbrRessources; i++) {
        int objetsMaxTemp;
        if (compositionObjets[noObjet][i] == 0) {
            continue;
        } else {
            objetsMaxTemp = (ressourcesTotales[i] / compositionObjets[noObjet][i]);
        }

        if (maxObjets > objetsMaxTemp) {
            maxObjets = objetsMaxTemp;
        }
    }
    if (maxObjets == 9999) {
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
void AjouterDemandeMaxUnObjet(int maxObjet, int noObjet, int nbrRessources) {
    for (int i = 0; i < nbrRessources; i++) {
        demandeMaximal[noObjet][i] = maxObjet * compositionObjets[noObjet][i];
    }
}

/**
* @brief  Calcul la demande maximal en ressources de chaque objets selon les ressources totales
* @note   matrice C dans les exemples du professeur
* @param  nbrObjets: Le nombre de type d'objets dans le systeme
* @param  nbrRessources: Le nombre de type de ressources dans le systeme(pas la quantite)
*/
void CalculerDemandeMaximal(int nbrObjets, int nbrRessources) {
    for (int j = 0; j < nbrObjets; j++) {
        int maxObjetsJ = CalculerMaxObjetsPossiblePour1Thread(j, nbrRessources);
        AjouterDemandeMaxUnObjet(maxObjetsJ, j, nbrRessources);
    }
}

/**
 * @brief Génère l'état initial de la matrice A pour le début d'execution du programme
 *
 */
void GenererA() {

    int ressourcesDispo[5] = {30, 20, 20, 60, 40};

    int sommeRessourcesDemandees;
    bool capaciteRespectee;

    //itère pour chaque ressource
    for (int j = 0; j < 5; j++) {
        capaciteRespectee = false;

        while (!capaciteRespectee) {
            sommeRessourcesDemandees = 0;
            // cette boucle itère au travers des différents threads et assigne une ressource "claim" pour le début du programme
            for (int i = 0; i < 5; i++) {
                int v1 = rand() % (demandeMaximal[i][j] + 1);
                allocation[i][j] = v1;
                sommeRessourcesDemandees += v1;
            }

            if (sommeRessourcesDemandees <= ressourcesDispo[j])
                capaciteRespectee = true;
        }

    }
}


//Calcule case par case la différence entre demandeMaximal et allocation
void CalculerCmoinsA(int matriceTemporairePourCmoinsA[5][5]) {

    for (int x = 0; x < 5; x++) {

        for (int y = 0; y < 5; y++) {

            matriceTemporairePourCmoinsA[x][y] = (demandeMaximal[x][y] - allocation[x][y]);
        }
    }
}

//La somme de chaque colonne de la matrice allocation
void CalculerV(int matriceTemporairePourV[5]) {

    for (int x = 0; x < 5; x++) {

        int sommeColonneMatriceAllocation = 0;

        for (int y = 0; y < 5; y++) {

            sommeColonneMatriceAllocation += allocation[y][x];
        }

        matriceTemporairePourV[x] = ressourcesTotales[x] - sommeColonneMatriceAllocation;
    }
}


/*
* @brief  Copie la matrice originale dans une seconde matrice [5][5]
 * note pas sur que c'est nécessaire
* @param  matriceOrigniale: La matrice à copier
* @param  copieMatrice: la copie de la matrice originale (variable passée par référence)
*/
void CopierMatrice5x5(int matriceOriginale[5][5], int copieMatrice[5][5]) {
    for (int x = 0; x < 5; x++) {

        for (int y = 0; y < 5; y++) {

            copieMatrice[x][y] = matriceOriginale[x][y];

        }

    }
}

void CopierMatrice5x1(int matriceOriginale[5], int copieMatrice[5]) {
    for (int x = 0; x < 5; x++) {

        copieMatrice[x] = matriceOriginale[x];

    }
}

/*
* @brief  Calcul la demande maximal en ressources de chaque objets selon les ressources totales
* @note   matrice C dans les exemples du professeur
* @param  nbrObjets: Le nombre de type d'objets dans le systeme
* @param  nbrRessources: Le nombre de type de ressources dans le systeme(pas la quantite)
*/
/*bool AlgorithmeDuBanquier(int matriceCmoinsA[5][5], queue<int> &ordreFabrication)
{

    int copieMatriceCmoinsA[5][5];
    int copieMatriceRessourcesNonAlloueesDisponible[5];

    int nombreLignesMarquees=0;
    int nombreLignesMarqueesLoop=0;


    queue<int> lignesMarqueesNonLiberees;*/






/*
 * True si sécuritaire et false si ce n'est pas sécuritaire.
 * Peut varié entre true et false durant l'exécution de la boucle mais
 * c'est le résultat à la sortie de la double boucle qui donne le verdict.
 */
/* bool verifierSiSecuritaire=true;
 bool finAlgo=false;


 //on travaille avec une copie mais je suis pas sûr que c'est nécessaire
 CopierMatrice5x5(matriceCmoinsA,copieMatriceCmoinsA);
 CopierMatrice5x1(ressourcesNonAlloueesDiponible,copieMatriceRessourcesNonAlloueesDisponible);

 //Tant que la pile contient quelque chose on boucle
 do
 {
     for(int x=0;x<5;x++)
     {

         for(int y=0; y<5;y++)
         {
             //Si la ligne n'est pas marquée
             if(copieMatriceCmoinsA[x][y]!=-999)
             {
                 if (copieMatriceCmoinsA[x][y] > copieMatriceRessourcesNonAlloueesDisponible[y]) {
                     verifierSiSecuritaire = false;*/

/*
 * La ligne n'est pas sécuritaire, donc on sort de la loop pour trouver si une autre ligne est correcte
 */
/*break;
}
}
else
{
break;//on saute la ligne si elle est marquée
}


}

//Si la ligne de C-A est <= V, on la met dans la fille,
//on incrémente les compteurs et on marque la ligne
if(verifierSiSecuritaire==true and copieMatriceCmoinsA[x][0]!=-999)
{
nombreLignesMarquees++;
nombreLignesMarqueesLoop++;
lignesMarqueesNonLiberees.push(x);

//une ligne contenant que des -999 est une ligne marquée
for(int y=0;y<5;y++)
{
copieMatriceCmoinsA[x][y]=-999;
}

}


}

//si on a marqué des lignes durant l'itération du double for
if (nombreLignesMarqueesLoop!=0)
{

//si on ne trouve pas d'autre ligne à marquer, on libère les ressources de la première ligne marquée
// qui est dans la file.
if(!lignesMarqueesNonLiberees.empty())
{
ordreFabrication.push(lignesMarqueesNonLiberees.front());
verifierSiSecuritaire=true;//pas sure si nécessaire

lignesMarqueesNonLiberees.pop();

for(int x=0; x<5;x++)
{
copieMatriceRessourcesNonAlloueesDisponible[x]+=matriceCmoinsA[ordreFabrication.back()][x];
}


}
else
{
verifierSiSecuritaire=false;
finAlgo=true;
}


}
else
{
//Pour la première itération, on libère le première processus et on le met dans V
if(ordreFabrication.empty())
{
ordreFabrication.push(lignesMarqueesNonLiberees.front());
verifierSiSecuritaire=true;// on remet true avant de réitérer réitérer
lignesMarqueesNonLiberees.pop();

//boucle pour ajouter les ressources de la ligne marquée qui est sur le dessus
//de la pile, dans V

for(int x=0; x<5;x++)
{
copieMatriceRessourcesNonAlloueesDisponible[x]+=matriceCmoinsA[ordreFabrication.front()][x];
}
}
nombreLignesMarqueesLoop=0;
}

if(nombreLignesMarquees==5)
{
finAlgo=true;
verifierSiSecuritaire=true;

//on vérifie s'il reste des lignes qui n'on pas été ajouté à l'ordre.
while(!lignesMarqueesNonLiberees.empty())
{
ordreFabrication.push(lignesMarqueesNonLiberees.front());
lignesMarqueesNonLiberees.pop();// supression du premier éléments
}

}



}while(finAlgo==false);


return verifierSiSecuritaire;

}
*/



bool AlgorithmeDuBanquier(int matriceCmoinsA[5][5], queue<int> &ordreFabrication)
{
    int copieMatriceCmoinsA[5][5];
    int copieMatriceRessourcesNonAlloueesDisponible[5];

    int nombreLignesMarqueesLoop = 0;

    bool verifierSiSecuritaire = true;

    CopierMatrice5x5(matriceCmoinsA, copieMatriceCmoinsA);
    CopierMatrice5x1(ressourcesNonAlloueesDiponible, copieMatriceRessourcesNonAlloueesDisponible);

    do
    {
        nombreLignesMarqueesLoop = 0;
        for (int x = 0; x < 5; x++)

        {
            verifierSiSecuritaire = true;

            for (int y = 0; y < 5; y++)
            {
                //Si la ligne n'est pas marquée
                if (copieMatriceCmoinsA[x][y] != -999) {
                    if (copieMatriceCmoinsA[x][y] > copieMatriceRessourcesNonAlloueesDisponible[y])
                    {
                        verifierSiSecuritaire = false;

                        /*
                         * La ligne n'est pas sécuritaire, donc on sort de la loop pour trouver si une autre ligne est correcte
                         */
                        break;

                    }

                }
                else
                {
                    break;//on saute la ligne si elle est marquée
                }


            }

//Si la ligne de C-A est <= V, on la met dans la fille,
//on incrémente les compteurs et on marque la ligne
            if (verifierSiSecuritaire == true and copieMatriceCmoinsA[x][0] != -999) {

                nombreLignesMarqueesLoop++;
                ordreFabrication.push(x);

                //libère les ressources allouées pour cette ligne
                for (int y = 0; y < 5; y++) {
                    copieMatriceRessourcesNonAlloueesDisponible[y] += allocation[x][y];


                }


                //une ligne contenant que des -999 est une ligne marquée
                for (int y = 0; y < 5; y++) {
                    copieMatriceCmoinsA[x][y] = -999;
                }

            }


        }

    } while (nombreLignesMarqueesLoop != 0);

    bool retournerSiSecuritaire = false;

    for (int x = 0; x < 5; x++) {
        if (copieMatriceCmoinsA[x][0] == -999) {
            retournerSiSecuritaire = true;
        } else {
            retournerSiSecuritaire = false;
            if (ordreFabrication.empty() != true) {
                while (!ordreFabrication.empty()) {
                    ordreFabrication.pop();
                }
            }
            break;
        }
    }

    return retournerSiSecuritaire;
}

void imprimerOrdreFabrication(queue<int> &ordreFabrication) {

    cout << "Ordre de fabrication: " << "\n";

    //Affichage puis supression de l'élément dans la file
    while (!ordreFabrication.empty()) {
        cout << ordreFabrication.front() << "\t";
        ordreFabrication.pop();
    }
    cout << endl;

}


void AjouterObjetCree(vector<int> vecteurDemandeCreationObjet) {

    for (int x = 0; x < 5; x++) {

        objetsCrees[x] += vecteurDemandeCreationObjet[x];


    }


}


void AfficherVecteurDemandeCreationObjet(vector<int> vecteurDemandeCreationObjet) {

    for (int x = 0; x < vecteurDemandeCreationObjet.size(); x++) {

        cout << vecteurDemandeCreationObjet[x] << "\t";

    }

}

int main() {
    bool etatsecuritaire;
    queue<int> ordreFabricationObjets;
    int matriceDemandeMaxMoinsAlloue[5][5];
    vector<int> vecteurDemandeCreationObjet;

// le programme jusqu'à ce que au moins 20 objets de chaque type aient été créés.
    while (objetsCrees[0] < 20 || objetsCrees[1] < 20 || objetsCrees[2] < 20 || objetsCrees[3] < 20 ||
           objetsCrees[4] < 20) {
        bool ressourcesRespectees = false;
        GenererA();

        while (!ressourcesRespectees) {
            vecteurDemandeCreationObjet = GenererVecteurDemandeCreationObjet();
            ressourcesRespectees = VerifierDepassementRessources(vecteurDemandeCreationObjet);

            //Si false on va reboucler, donc affichage que la demande est rejeté, car excède les ressources
            if (ressourcesRespectees == false) {
                cout << "Demande ";
                AfficherVecteurDemandeCreationObjet((vecteurDemandeCreationObjet));
                cout << "rejetee, car excede les ressources." << "\n";
            }
        }
        CalculerCmoinsA(matriceDemandeMaxMoinsAlloue);
        CalculerV(ressourcesNonAlloueesDiponible);

// les ressources ne sont pas dépassées, appeler l'algorithme du banquier
        etatsecuritaire = AlgorithmeDuBanquier(matriceDemandeMaxMoinsAlloue, ordreFabricationObjets);
        if (etatsecuritaire) {
            imprimerOrdreFabrication(ordreFabricationObjets);
            AjouterObjetCree(vecteurDemandeCreationObjet);
        }


    }
    return 0;
}