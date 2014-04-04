#include "groupe.h"

using namespace std;

Instance* Groupe::_static_instance=0;

Groupe::Groupe ( unsigned int id , Instance* instance ) :_id ( id )
{
    if ( ! _static_instance ) _static_instance=instance;
    _masque.resize ( _static_instance->_genes.size(),0 );
}

void Groupe::calculMasque()
{
    _masque.clear();
    _masque.resize ( _static_instance->_genes.size(),0 );

    for ( vector<Entite*>::const_iterator it=_entites.begin(); it!=_entites.end(); it++ )
    {
        int i=0;
        for ( vector<pair<Gene*,bool> >::const_iterator itGene= ( *it )->_genes.begin(); itGene!= ( *it )->_genes.end(); itGene++,i++ )
            if ( itGene->second ) _masque[i]+=1;
    }

    //Moyenne
    for ( vector<float>::iterator it=_masque.begin(); it!=_masque.end(); it++ )
        *it=*it/_entites.size();
}

void Groupe::afficheMasque() const
{
    for ( vector<float>::const_iterator it=_masque.begin(); it!=_masque.end(); it++ )
        if ( *it == 1 || *it==0 ) cout<<*it<<" ";
        else cout<<"  ";
    cout<<endl;
}
