#include "algo.h"

#include "groupe.h"
#include "entite.h"
#include "gene.h"
#include "combinaison.h"

using namespace std;

Algo::Algo ( const Instance* instance ) :_instance ( instance ),_parcours ( vector<int>() ),_e1 ( 0 ),_e2 ( 0 )
{

}


bool Algo::entiteIdentiqueSurIndicesGenes ( const Entite* const & e1, const Entite*const & e2, const vector< int > &indices ) const
{
//     Les k-uplets doivent être différents 2 à 2
    bool identique=true;//Vrai si deux entités sont identiques,faux sinon
    if ( e1!=e2 )
    {
        //Parcours des indices
        bool tempIdentique=true;
        identique=true;
        for ( unsigned int indice=0; indice<indices.size(); indice++ )
        {
//             assert ( ( ( *entiteIt )->_genes[indices[indice]].first )->_id == ( ( *entiteIt2 )->_genes[indices[indice]].first )->_id );
            tempIdentique= e1->_genes[indices[indice]].second== e2->_genes[indices[indice]].second;
            if ( !tempIdentique )
            {
                identique=false;
                break;
            }
        }//Fin parcours indices
        if ( identique ) return identique;
    }
    return identique;
}



bool Algo::estCaracterisePar ( const vector< int > &indices )
{
    bool identique=true;//Vrai si deux entités sont identiques,faux sinon

    //Petite heuristique
    if ( _e1!=_e2 && entiteIdentiqueSurIndicesGenes ( _e1,_e2,indices ) ) return false;

    //Parcours des groupes
    for ( vector<Groupe*>::const_iterator itGroupe=_instance->_groupes.begin(); itGroupe!=_instance->_groupes.end(); itGroupe++ )
    {
        //Parcours des entités du groupes
        for ( vector<Entite*>::const_iterator entiteIt= ( *itGroupe )->_entites.begin(); entiteIt!= ( *itGroupe )->_entites.end(); entiteIt++ )
        {
            //Nouveau parcours des groupes
            for ( vector<Groupe*>::const_iterator itGroupe2=itGroupe+1; itGroupe2!=_instance->_groupes.end(); itGroupe2++ )
            {
                //Nouveau parcours des entite
                for ( vector<Entite*>::const_iterator entiteIt2= ( *itGroupe2 )->_entites.begin(); entiteIt2!= ( *itGroupe2 )->_entites.end(); entiteIt2++ )
                {
                    if ( ( identique=entiteIdentiqueSurIndicesGenes ( *entiteIt,*entiteIt2,indices ) ) )
                    {
                        /*Si les deux entités sont identiques, on les garde en memoire afin de les tester en premier
											  lors de la prochaine combinaison afin de couper des brancges dans l'arbre de recherche*/
                        _e1=*entiteIt;
                        _e2=*entiteIt2;
                        break;
                    }
                }//Fin parcours entiteIt2
                if ( identique ) break;
            }//Fin parcours itGroupe2
            if ( identique ) break;
        }//Fin parcours entiteIt
        if ( identique ) break;
    }//Fin parcours itGroupe
    if ( ! identique )
    {
        cout<<"Cette combinaison de taille "<< indices.size() <<" permet de caractériser l'instance"<<endl;
        _e1=0;
        _e2=0;
        afficheVecteur ( indices );
				cout<<endl;
        return true;
    }
    return false;
}
