#ifndef RECHERCHE_APPROCHE_H
#define RECHERCHE_APPROCHE_H

#include "algo.h"

class RechercheApproche : public Algo
{
protected:
		std::vector<float> _proba;
		std::vector<float> _utiliteRelative;
		std::vector<float> _variationFitness;
		std::vector<unsigned int> _utilisationGene;
		std::vector<std::vector<int> > _individus;
public:
    //ATTRIBUTS

    //METHODES
    RechercheApproche ( Instance* instance );
	
		///!proba fixe en fonction du TAU de chaque gene
		void roulette();
		
		std::vector<int> croisementParPlusFaibleSimilariteEntreLesIndices(const std::vector<int> &pere,const std::vector<int> &mere) const;
		
// 		///!proba adaptative initialisé en fonction du TAU de chaque gene
// 		void rouletteAdaptative(float pMin);
		
		///!Initialisation de _proba a partir des TAU de _instance
		void initialisationProba();
		
    void rechercheLocaleAleatoire ( unsigned int k , unsigned int nbIterations );

    ///\brief Instancie le vecteur _parcours d'entier de 1 à _genes.size() de façon aléatoire
    void parcoursAleatoire ( unsigned int k );
};

#endif //RECHERCHE_APPROCHE_H
