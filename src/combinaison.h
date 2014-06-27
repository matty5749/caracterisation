#ifndef COMBINAISON_H
#define COMBINAISON_H

#include "standard.h"

class Combinaison
{
    //ATTRIBUTS
private:
    unsigned int _n;
    unsigned int _k;
    std::vector<int> _elements;	/*!<Les éléments qui vont être combiné via iterElements*/
    std::vector<std::vector<int>::const_iterator> _iterElements;	/*!<Les itérateurs vers les éléments qui sont combinés,cela afin de pouvoir traiter
		un vecteur d'éléments non triés (ex: [3,4,5,2,3,1]), les combinaisons se feront sur les itérateurs qui eux sont triés par ordre croissant*/
		unsigned long long int _nbCombEffectue;
		unsigned long long int _nbCombTotal;
public:
    std::vector<int> _combinaisonCourante;
		unsigned int _decalage;/*!<Nb de décalage lors de la combinaison suivante généré par next: 3 parmi 5 : 125 --> 234 = décalage de 2*/

public:
    //METHODES
    Combinaison ( const std::vector<int> &elements );

    /*!
     * \param k parmi n
     * \return La prochaine combinaison de taille k , vecteur vide si toute les combinaisons ont été effectuées
     * \warning Si le k change d'un appel à l'autre, c'est toute les combinaisons qui sont reprises depuis le début.
     */
    const std::vector<int>& next ( unsigned int k );
		
		///!\return le pourcentage de combinaisons ayant déjà été analysé
		double getPourcentage () const;


private:
    /*!
    * \author Mark Nelson http://marknelson.us
    * \warning Cette méthode ne peut effectuer les combinaisons que sur
    * des conteneur triés par ordre croissant
    */
    template <typename Iterator>
    bool next_combination ( const Iterator first, Iterator k, const Iterator last );


};

#endif //COMBINAISON_H

// /*Ma méthode récursive pour calculer des combinaisons,
// mais il faut lui préférer la méthode itérative next_combination*/
// void combinaisons ( std::vector<int> res, const std::vector<int> &enumeration, const unsigned int k, const unsigned int indice )
// {
// //     if ( k>enumeration.size() )
// //     {
// //         cout<<"k est supérieur à n!"<<endl;
// // //         exit ( EXIT_FAILURE );
// //     }
//     if ( k==0 )
//     {
// // 				cout<<"\t\t";
// //        afficheVecteur ( res );
//         return;
//     }
//     else
//     {
//         for ( unsigned int i=0; i<enumeration.size(); i++ )
//         {
//             std::vector<int> enumeration2 ( enumeration.size()-i-1 );
//             std::copy ( enumeration.begin() +i+1,enumeration.end(),enumeration2.begin() );
//             res[indice]=enumeration[i];
//             combinaisons ( res,enumeration2,k-1,indice+1 );
//         }
//     }
// }
