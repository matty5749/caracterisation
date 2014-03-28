#ifndef SOLVEUR_H
#define SOLVEUR_H

#include "algo.h"

class Solveur : public Algo
{
    //ATTRIBUTS
private:

public:



    //METHODES
    Solveur ( const Instance* instance );

    /*!
    * \param k borne supérieur
    * \param allSolution si vrai, cherchera toute les formules de taille k caractérisant l'instance
    */
    void rechercheExacteEnProfondeurAPartirde ( unsigned int k , bool allSolution=false ) ;

    /*!
    * \param k borne inférieur
    * \param allSolution si vrai, cherchera toute les formules de taille k caractérisant l'instance
    */
    void rechercheExacteEnLargeurAPartirde ( unsigned int k , bool allSolution=false ) ;

///\brief Instancie le vecteur _parcours d'entier de 1 à _genes.size() dans l'ordre croissant
    void parcoursSansHeuristique();








};

#endif //SOLVEUR_H
