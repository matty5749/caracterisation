#ifndef ALGO_H
#define ALGO_H

#include "instance.h"
#include "standard.h"

class Algo
{
    //ATTRIBUTS
protected:
    Instance* _instance;
    std::vector<int> _parcours;/*!<L'ordre dans lequel sera parcouru l'espace de recherche, initialiser par les méthodes de type parcoursSansHeuristique , parcours.............*/
    Entite* _e1;
    Entite* _e2;
		unsigned short int _poidCourant;
		unsigned int _fitness;
		unsigned int _nbComparaisons;
		bool _debut;
		int _nbComparaisonsMax;/*<!Le nombre de comparaisons max est le nombre de comparaisons qu'il faut effectuer pour caractériser une instance*/
public:


    //METHODES
    Algo ( Instance* instance );





protected:
		///!\brief Le nombre de comparaisons max est le nombre de comparaisons qu'il faut effectuer pour caractériser une instance
		int calculNbComparaisonsMax();
	
    /*!
    * \brief Renvoie vrai si l'instance est caractérisable par les gènes présent aux positions d'indices dans _genes
    * \param indices est composé des positions des gènes dont on veut savoir si ils caractérisent l'instance
    */
    bool estCaracterisePar ( const std::vector<int> &indices ) ;
		
// 		/*!
// 		 * \brief Concu pour la roulette adaptative, permet de déterminer un fitness pour la combinaison indices
// 		 * \return le fitness de la combinaison
// 		 */
// 		bool estCaracteriseParFullVersion ( const std::vector<int> &indices ) ;

		/*!
    * \brief Renvoie vrai si l'instance est caractérisable par les gènes présent aux positions d'indices dans _genes
    * \param indices est composé des positions des gènes dont on veut savoir si ils caractérisent l'instance
    */
		bool estCaracterisePar_version1 ( const std::vector<int> &indices ) ;
		
		    /*!
    * \brief Renvoie vrai si l'instance est caractérisable par les gènes présent aux positions d'indices dans _genes
    * \param indices est composé des positions des gènes dont on veut savoir si ils caractérisent l'instance
		* \details Dans cette version, on ne parcoure plus les groupes mais directement les entites, permet de coller à l'heuristique 2 
    */
    bool estCaracterisePar_version2 ( const std::vector<int> &indices ) ;

				    /*!
    * \brief Renvoie vrai si l'instance est caractérisable par les gènes présent aux positions d'indices dans _genes
    * \param indices est composé des positions des gènes dont on veut savoir si ils caractérisent l'instance
		* \details Dans cette version, on ne parcoure plus les groupes mais directement les entites, permet de coller à l'heuristique 3 
    */
    bool estCaracterisePar_version3 ( const std::vector<int> &indices ) ;
		
		bool estCaracterisePar_version4 ( const std::vector<int> &indices ) ;
		
		bool caracteriseDeuxGroupe ( const Groupe* const &g1, const Groupe* const &g2, const std::vector<int> &indices) ;
		
    bool entiteIdentiqueSurIndicesGenes ( const Entite* const&e1 , const Entite*const &e2 , const std::vector<int> &indices );
};

#endif //ALGO_H
