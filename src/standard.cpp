#include "standard.h"

void afficheVecteur ( std::vector< int > vecteur )
{
    for ( unsigned int i=0; i<vecteur.size(); i++ )
    {
        std::cout<<vecteur[i]<<" ";
    }
    std::cout<<std::endl;
}
