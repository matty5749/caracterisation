#ifndef COMB_H
#define COMB_H

#include "standard.h"



/*!
 * \author Mark Nelson http://marknelson.us
 * \warning Cette méthode ne peut effectuer les combinaisons que sur
 * des conteneur triés par ordre croissant
 */
template <typename Iterator>
bool next_combination ( const Iterator first, Iterator k, const Iterator last )
{
    /* Credits: Mark Nelson http://marknelson.us */
    if ( ( first == last ) || ( first == k ) || ( last == k ) )
        return false;
    Iterator i1 = first;
    Iterator i2 = last;
    ++i1;
    if ( last == i1 )
        return false;
    i1 = last;
    --i1;
    i1 = k;
    --i2;
    while ( first != i1 )
    {
        if ( *--i1 < *i2 )
        {
            Iterator j = k;
            while ( ! ( *i1 < *j ) ) ++j;
            std::iter_swap ( i1,j );
            ++i1;
            ++j;
            i2 = k;
            std::rotate ( i1,j,last );
            while ( last != j )
            {
                ++j;
                ++i2;
            }
            std::rotate ( k,i2,last );
            return true;
        }
    }
    std::rotate ( first,k,last );
    return false;
}


/*Ma méthode récursive pour calculer des combinaisons,
mais il faut lui préférer la méthode itérative next_combination*/
void combinaisons ( std::vector<int> res, const std::vector<int> &enumeration, const unsigned int k, const unsigned int indice )
{
//     if ( k>enumeration.size() )
//     {
//         cout<<"k est supérieur à n!"<<endl;
// //         exit ( EXIT_FAILURE );
//     }
    if ( k==0 )
    {
// 				cout<<"\t\t";
//        afficheVecteur ( res );
        return;
    }
    else
    {
        for ( unsigned int i=0; i<enumeration.size(); i++ )
        {
            std::vector<int> enumeration2 ( enumeration.size()-i-1 );
            std::copy ( enumeration.begin() +i+1,enumeration.end(),enumeration2.begin() );
            res[indice]=enumeration[i];
            combinaisons ( res,enumeration2,k-1,indice+1 );
        }
    }
}
#endif
