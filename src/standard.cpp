#include "standard.h"

using namespace std;

void afficheVecteur ( std::vector< int > vecteur )
{
    for ( unsigned int i=0; i<vecteur.size(); i++ )
    {
        std::cout<<vecteur[i]<<" ";
    }
    std::cout<<std::endl;
}


int toInt ( std::string str )
{
    istringstream iss ( str );
    int val;
    iss>>val;
		return val;
}
