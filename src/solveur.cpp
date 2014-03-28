#include "solveur.h"

#include "groupe.h"
#include "entite.h"
#include "gene.h"
#include "combinaison.h"

using namespace std;

Solveur::Solveur ( const Instance* instance ) :Algo ( instance )
{

}


void Solveur::rechercheExacteEnProfondeurAPartirde ( unsigned int k, bool allSolution )
{
// 				parcoursSansHeuristique();
    assert ( _instance->_borneMin>0 );
    assert ( _parcours.size() >0 );
    //On part de kMax vers kMin
    bool solution=false;
    do
    {
        //Parcours des combinaisons de taille k
        Combinaison combinaison ( _parcours );
        cout<<endl<<"\t\t****** Parcours des combinaisons de taille "<< k <<" ******"<<endl;
        while ( combinaison.next ( k ).size() >0 )
        {
            if ( estCaracterisePar ( combinaison._combinaisonCourante ) )
            {
                if ( solution==false ) solution=true;
                if ( !allSolution ) break; //On passe à k-1
            }
            //Sinon on cherche avec une autre combinaison
        }
    }
    while ( --k>=_instance->_borneMin || solution );
    cout<<"La borne minimale a été atteinte et est de "<<++k<<endl;
}

void Solveur::rechercheExacteEnLargeurAPartirde ( unsigned int k, bool allSolution )
{
// 				parcoursSansHeuristique()
    assert ( _instance->_borneMin>0 );;
    assert ( _parcours.size() >0 );
    bool solution=false;
    //On part de kMin vers kMax
    do
    {
        cout<<"La borne minimale est de taille "<< k <<endl;
        //Parcours des combinaisons de taille k
        Combinaison combinaison ( _parcours );
        cout<<endl<<"\t\t****** Parcours des combinaisons de taille "<< k <<" ******"<<endl;
        while ( combinaison.next ( k ).size() >0 )
        {
            if ( estCaracterisePar ( combinaison._combinaisonCourante ) )
                if ( !allSolution )
                {
                    solution=true;
                    break;
                } //On arrete
            //Sinon on cherche avec une autre combinaison
        }
        ++k;
    }
    while ( !solution );
    cout<<"La borne minimale a été atteinte et est de "<<--k<<endl;
}

void Solveur::parcoursSansHeuristique()
{
    _parcours.resize ( _instance->_genes.size() );
    for ( unsigned int i=0; i<_instance->_genes.size(); i++ )
        _parcours[i]=i;
}





