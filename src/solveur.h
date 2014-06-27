#ifndef SOLVEUR_H
#define SOLVEUR_H

#include "algo.h"

class Solveur : public Algo
{
    //ATTRIBUTS
public:
    //METHODES
    Solveur ( Instance* instance );

		/*!
    * \param k borne supérieur
    * \param allSolution si vrai, cherchera toute les formules de taille k caractérisant l'instance
    */
    void rechercheExacteEnProfondeurAPartirde ( unsigned int k , bool allSolution=false ) ;
		
    /*!
    * \param k borne supérieur
    * \param allSolution si vrai, cherchera toute les formules de taille k caractérisant l'instance
    */
    void rechercheExacteEnProfondeurAPartirde_heuristique1 ( unsigned int k , bool allSolution=false ) ;

		/*!
    * \param k borne supérieur
    * \param allSolution si vrai, cherchera toute les formules de taille k caractérisant l'instance
		* \details Heuristique: calcul de poids d'identicite et trie par poids
		*/
    void rechercheExacteEnProfondeurAPartirde_heuristique2 ( unsigned int k , bool allSolution=false ) ;
		
		/*!
    * \param k borne supérieur
    * \param allSolution si vrai, cherchera toute les formules de taille k caractérisant l'instance
		* \details Heuristique: calcul des poids d'identicite = k-1 sans trie par poids
		*/
    void rechercheExacteEnProfondeurAPartirde_heuristique3 ( unsigned int k , bool allSolution=false ) ;
		
		
		/*!
    * \param k borne supérieur
    * \param allSolution si vrai, cherchera toute les formules de taille k caractérisant l'instance
		* \details Heuristique: calcul des poids d'identicite = k-1 sans trie par poids + utilisation de _tabous
		*/
    void rechercheExacteEnProfondeurAPartirde_heuristique4 ( unsigned int k , bool allSolution=false ) ;
		
    /*!
    * \param k borne inférieur
    * \param allSolution si vrai, cherchera toute les formules de taille k caractérisant l'instance
    */
    void rechercheExacteEnLargeurAPartirde ( unsigned int k , bool allSolution=false ) ;

    ///\brief Instancie le vecteur _parcours d'entier de 1 à _genes.size() dans l'ordre croissant
    void parcoursStandard();








};

#endif //SOLVEUR_H

