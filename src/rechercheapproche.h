#ifndef RECHERCHE_APPROCHE_H
#define RECHERCHE_APPROCHE_H

#include "algo.h"

class RechercheApproche : public Algo
{
public:
    //ATTRIBUTS

    //METHODES
    RechercheApproche ( Instance* instance );

    void rechercheLocaleAleatoire ( unsigned int k , unsigned int nbIterations );

    ///\brief Instancie le vecteur _parcours d'entier de 1 à _genes.size() de façon aléatoire
    void parcoursAleatoire ( unsigned int k );
};

#endif //RECHERCHE_APPROCHE_H
