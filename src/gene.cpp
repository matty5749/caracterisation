#include "gene.h"

using namespace std;

Instance* Gene::_static_instance=0;

Gene::Gene ( unsigned int id, unsigned int nbEntites, Instance* instance ) :_nbOne ( -1 ),_id ( id )
{
    if ( ! _static_instance ) _static_instance=instance;
    _entites.resize ( nbEntites );
}

unsigned int Gene::nbOne()
{
    if ( _nbOne>-1 ) return _nbOne; //Le calcul a déja été fait et le résultat se trouve dans l'attribut _nbOne

    //Sinon on calcul _nbOne
    _nbOne=0;
    for ( vector<pair<Entite*,bool> >::iterator it=_entites.begin(); it!=_entites.end(); it++ )
        if ( it->second==true ) ++_nbOne;

    return _nbOne;
}


void Gene::affichage ( ostream& os ) const
{
    for ( vector<pair<Entite*,bool> >::const_iterator it=_entites.begin(); it!=_entites.end(); it++ )
    {
        os<< ( *it ).second<<endl;
    }
}

ostream& operator<< ( ostream& os, const Gene& g )
{
    os<<"AFFICHAGE"<<endl;
    g.affichage ( os );
    return os;
}

bool estSimilaire ( const Gene*const g1, const Gene*const g2 )
{
    if ( g1->_id == g2->_id )
    {
        cout<<"Les deux gènes doivent être différent dans bool estSimilaire ( const Gene*const g1, const Gene*const g2 )"<<endl;
        exit ( EXIT_FAILURE );
    }
    vector<pair<Entite*,bool> >::const_iterator it2=g2->_entites.begin();
    for ( vector<pair<Entite*,bool> >::const_iterator it1=g1->_entites.begin(); it1!=g1->_entites.end(); it1++,it2++ )
        if ( it1->second != it2->second ) return false;
    return true;
}


