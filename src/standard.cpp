#include "standard.h"

using namespace std;

int toInt ( std::string str )
{
    istringstream iss ( str );
    int val;
    iss>>val;
    return val;
}


float ecartType ( const vector< float >& donnees )
{
    double diff[donnees.size()]; //tableau contenant la différence des données avec la moyenne
    double moy; //moyenne
    double ecart_type; //écart type
    int i;

    moy=0;
    ecart_type=0;

		//calcul de la moyenne
    for ( i=0 ; i<donnees.size(); i++ ) moy += donnees[i];
    moy /= donnees.size();

		//calcul de l'écart type
    for ( i=0 ; i<donnees.size(); i++ )
    {
        diff[i]=pow ( donnees[i]-moy, 2 );
        ecart_type += diff[i];
    }
    ecart_type = sqrt ( ecart_type / donnees.size());
		return ecart_type;
}
