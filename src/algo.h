#ifndef ALGO_H
#define ALGO_H

#include "instance.h"
#include "standard.h"

class Algo
{
    //ATTRIBUTS
protected:
    const Instance* _instance;
    std::vector<int> _parcours;/*!<L'ordre dans lequel sera parcouru l'espace de recherche, initialiser par les méthodes de type parcoursSansHeuristique , parcours.............*/
    Entite* _e1;
    Entite* _e2;
public:


    //METHODES
    Algo ( const Instance* instance );





protected:
    /*!
    * \brief Renvoie vrai si l'instance est caractérisable par les gènes présent aux positions d'indices dans _genes
    * \param indices est composé des positions des gènes dont on veut savoir si ils caractérisent l'instance
    */
    bool estCaracterisePar ( const std::vector<int> &indices ) ;


    bool entiteIdentiqueSurIndicesGenes ( const Entite* const&e1 , const Entite*const &e2 , const std::vector<int> &indices ) const;
};

#endif //ALGO_H
