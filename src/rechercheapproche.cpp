#include "rechercheapproche.h"

#include "groupe.h"
#include "entite.h"
#include "gene.h"
#include "combinaison.h"

using namespace std;

RechercheApproche::RechercheApproche ( const Instance* instance ) :Algo ( instance )
{

}

void RechercheApproche::rechercheLocaleAleatoire ( unsigned int k, unsigned int nbIterations )
{
    assert ( _instance->_borneMin>0 );
    do
    {
        do
        {
            parcoursAleatoire ( k );
        }
        while ( ! estCaracterisePar ( _parcours ) && --nbIterations>0 );
    }
    while ( --k>_instance->_borneMin && nbIterations>0 );
}

void RechercheApproche::parcoursAleatoire ( unsigned int k )
{
    _parcours.resize ( k );
    //Creation des combinaisons aleatoire
    set<int> ens;
    do
    {
        int alea=rand() %_instance->_genes.size() +1;
        ens.insert ( alea );
    }
    while ( ens.size() != k );

    copy ( ens.begin(),ens.end(),_parcours.begin() );
}
