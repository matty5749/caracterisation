#include "combinaison.h"

using namespace std;

Combinaison::Combinaison ( const std::vector< int >& elements ) :_n ( elements.size() ),_k ( 0 ),_elements ( elements ),_decalage ( 0 ),_nbCombEffectue ( 0 ),_nbCombTotal ( 0 )
{
    _iterElements.resize ( _n );
}

// void Instance::test() const
// {
//     int n=5;
//     int k=3;
// std::size_t comb_size = k;
//     vector<int> enumeration ( n );
//     int ind=10;
//     for ( int i=0; i<n; i++ )
//         enumeration[i]=ind--;
//
// 		vector<vector<int>::const_iterator> enumerationIterateur(n);
// 		int i=0;
// 		for ( vector<int>::iterator it=enumeration.begin(); it!=enumeration.end(); it++,i++ )
// 		{
// 			enumerationIterateur[i]=it;
// // 			cout<<(long int)&*it<<endl;
// 		}
//
//
//     //Génération et parcours des combinaisons de taille k
//     cout<<endl<<"\t\t****** Parcours des combinaisons de taille "<< k <<" ******"<<endl;
//     do
//     {
//         //Combinaison à traiter
//         vector<int> indices ( k );
//         int i=0;
//         for ( vector<vector<int>::const_iterator>::iterator it=enumerationIterateur.begin(); it!=enumerationIterateur.begin() +comb_size; it++ )
//         {
// //             indices[i++]=*it;
//             cout<<**it<<" ";
//         }
//         cout<<endl;
//     }
//     while ( next_combination ( enumerationIterateur.begin(),enumerationIterateur.begin() + comb_size,enumerationIterateur.end() ) );
// }

const std::vector< int >& Combinaison::next ( unsigned int k )
{
    _nbCombEffectue++;

    if ( k!=_k ) //Changement de k, on entame un nouveau cycle
    {
        _nbCombEffectue=0;
        _k=k;

        //Calcul de nbCompTotal
        unsigned int i,j;
        for ( i=_n,j=1, _nbCombTotal=1; i>_n-_k; i--,j++ ) // calcul de Cnp
        {
            _nbCombTotal *= i;
            _nbCombTotal /= j;
        }
        //Fin calcul

        //Initialisation de _iterElements
        i=0;
        for ( vector<int>::const_iterator it=_elements.begin(); it!=_elements.end(); it++,i++ )
            _iterElements[i]=it;

        //Premiere combinaison
        _combinaisonCourante.resize ( k );
        for ( i=0; i<_k; i++ )
            _combinaisonCourante[i]=_elements[i];
    }
    else
    {
        std::size_t comb_size = k;

        bool enCoursDeCycle=next_combination ( _iterElements.begin(),_iterElements.begin() +comb_size,_iterElements.end() );
        if ( enCoursDeCycle ) //Si on est en cours de cycle, on calcul et on renvoie la combinaison courante
        {
            int i=0;
            for ( vector<vector<int>::const_iterator>::iterator it=_iterElements.begin(); it!=_iterElements.begin() + comb_size; it++,i++ )
                _combinaisonCourante[i]=**it;
// 						afficheVecteur(_combinaisonCourante);
        }
        else _combinaisonCourante.clear();
    }

    //Dans tout les cas
//     cout<<_decalage<<"\t";
//     afficheVecteur(_combinaisonCourante);
    return _combinaisonCourante;
}


template <typename Iterator>
bool Combinaison::next_combination ( const Iterator first, Iterator k, const Iterator last )
{
    _decalage=0;
    /* Credits: Mark Nelson http://marknelson.us */
    if ( ( first == last ) || ( first == k ) || ( last == k ) )
        return false;
    Iterator i1 = first;
    Iterator i2 = last;
    ++i1;
    if ( last == i1 )
        return false;
//     i1 = last;
//     --i1;
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
        else _decalage++;
    }
    std::rotate ( first,k,last );
    return false;
}

double Combinaison::getPourcentage() const
{
 return (double) _nbCombEffectue*100/_nbCombTotal;
}
