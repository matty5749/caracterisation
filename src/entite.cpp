#include "entite.h"


using namespace std;

Instance* Entite::_static_instance=0;

Entite::Entite ( unsigned int id, unsigned int idGroupe, std::string chaine_de_bits, Instance* instance )
    :_id ( id ),_idGroupe ( idGroupe )
{
    if ( ! _static_instance ) _static_instance=instance;

    _genes.resize ( chaine_de_bits.size() );


    //Initialisation de _vVariables
    for ( unsigned int i=0; i<chaine_de_bits.size(); i++ )
    {
        bool presence= ( chaine_de_bits[i]=='1' );
        _genes[i]=make_pair<Gene*,bool> ( _static_instance->_genes[i],presence );
        _static_instance->_genes[i]->_entites[_id-1]=make_pair<Entite*,bool> ( this,presence );
    }
}

void Entite::affichage ( ostream& os ) const
{
    os<<"ID: "<<_id<<" idGroupe: "<<_idGroupe<<" Contenu: \t";
    for ( std::vector<std::pair<Gene*,bool> >::const_iterator it=_genes.begin(); it!=_genes.end(); it++ )
    {
        os<< ( *it ).second;
    }
    os<<std::endl;
}

ostream& operator<< ( ostream& os, const Entite& e )
{
    e.affichage ( os );
    return os;
}

bool estSimilaire ( const Entite*const e1, const Entite*const e2 )
{
	if (e1->_id == e2->_id)
	{
		cout<<"Les deux entités doivent être différentes dans bool estSimilaire ( const Entite*const e1, const Entite*const e2 )"<<endl;
		exit(EXIT_FAILURE);
	}
	vector<pair<Gene*,bool> >::const_iterator it2=e2->_genes.begin();
	for(vector<pair<Gene*,bool> >::const_iterator it1=e1->_genes.begin();it1!=e1->_genes.end();it1++,it2++)
		if (it1->second != it2->second) return false;
	return true;
}
