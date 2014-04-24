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
    bool solution;
    do
    {
        solution=false;
        _startTime=clock();
        _nbComparaisons=0;
//         int nbSol=0;
        //Parcours des combinaisons de taille k
        Combinaison combinaison ( _parcours );
//         cout<<endl<<"\t\t****** Parcours des combinaisons de taille "<< k <<" ******"<<endl;
        while ( combinaison.next ( k ).size() >0 )
        {
            if ( estCaracterisePar ( combinaison._combinaisonCourante ) )
            {
                _endTime=clock();
//                 cout<<"Résolu en "<< ( double ) ( _endTime-_startTime ) /CLOCKS_PER_SEC<< " secondes"<<endl;
// 								cout<<k<<" "<<( double ) ( _endTime-_startTime ) /CLOCKS_PER_SEC<<endl; //DATA
//                 nbSol++;
                if ( solution==false ) solution=true;
                if ( !allSolution ) break; //On passe à k-1
            }
            //Sinon on cherche avec une autre combinaison
        }
//         cout<<"** Il y a "<<nbSol<<" solutions"<<endl;
    }
    while ( --k>=_instance->_borneMin && solution );
    if ( !solution ) cout<<"Pas de solution en "<<k+1<<endl<<endl;
    cout<<"*** La borne minimale a été atteinte et est de "<<k+2<<" ***"<<endl<<endl;
}


void Solveur::rechercheExacteEnProfondeurAPartirde_heuristique1 ( unsigned int k, bool allSolution )
{
// 				parcoursSansHeuristique();
    assert ( _instance->_borneMin>0 );
    assert ( _parcours.size() >0 );
    //On part de kMax vers kMin
    bool solution;
    do
    {
        solution=false;
        _startTime=clock();
        _nbComparaisons=0;
        //Parcours des combinaisons de taille k
        Combinaison combinaison ( _parcours );
//         cout<<endl<<"\t\t****** Parcours des combinaisons de taille "<< k <<" ******"<<endl;
        while ( combinaison.next ( k ).size() >0 )
        {
            if ( estCaracterisePar_version1 ( combinaison._combinaisonCourante ) )
            {
                _endTime=clock();
                cout<<k<<" "<< ( double ) ( _endTime-_startTime ) /CLOCKS_PER_SEC<<endl; //DATA
//                 cout<<"Résolu en "<< ( double ) ( _endTime-_startTime ) /CLOCKS_PER_SEC<< " secondes"<<endl;
                if ( solution==false ) solution=true;
                if ( !allSolution ) break; //On passe à k-1
            }
            //Sinon on cherche avec une autre combinaison
        }
    }
    while ( --k>=_instance->_borneMin && solution );
    if ( !solution ) cout<<"Pas de solution en "<<k+1<<endl<<endl;
    cout<<"*** La borne minimale a été atteinte et est de "<<k+2<<" ***"<<endl<<endl;
}


















void Solveur::rechercheExacteEnProfondeurAPartirde_heuristique2 ( unsigned int k, bool allSolution )
{
    assert ( _parcours.size() > 0 );
    assert ( _instance->_borneMin>0 );
    //On part de kMax vers kMin
    bool solution;
    do
    {
        solution=false;
        _startTime=clock();
        _nbComparaisons=0;
        //Parcours des combinaisons de taille k
        Combinaison combinaison ( _parcours );
        cout<<endl<<"\t\t****** Parcours des combinaisons de taille "<< k <<" ******"<<endl;
        while ( combinaison.next ( k ).size() >0 )
        {

            //MAJ des poids en cas de décalage dans combinaison
            if ( combinaison._decalage>0 )
            {
//                 if (combinaison._decalage>2) cout<<"DECALAGE : " <<combinaison._decalage <<endl;
                for ( vector<Entite*>::const_iterator it=_instance->_entites.begin(); it!=_instance->_entites.end(); it++ )
                {
                    vector<pair<Entite*,int> > aBasculerVersPoidsCritique;
                    aBasculerVersPoidsCritique.reserve ( ( *it )->_poidsNonCritique.size() );

                    for ( map<Entite*,int>::iterator itMap= ( *it )->_poidsNonCritique.begin(); itMap != ( *it )->_poidsNonCritique.end(); itMap++ )
                    {
                        itMap->second+=combinaison._decalage;
                        if ( itMap->second >= ( int ) k-1 )
                            aBasculerVersPoidsCritique.push_back ( *itMap );
                    }
                    //MAJ de la map _poidsNonCritique de l'iterateur
                    for ( vector<pair<Entite*,int> >::const_iterator itBascule=aBasculerVersPoidsCritique.begin(); itBascule!=aBasculerVersPoidsCritique.end(); itBascule++ )
                        ( *it )->basculerVersPoidsCritique ( itBascule->first,itBascule->second );
                }

                //Trie de _entites dans _instance par _poidsCritique.size()
                if ( combinaison._decalage>0 ) _instance->trieDesEntitesParPoidCritique();
            }
            //TODO: Eventuellement faire la MAJ sur les poids critiques, mais pas nécéssaire (il faut y trouver un intéret) ...
            //Fin MAJ des poids



            if ( estCaracterisePar_version2 ( combinaison._combinaisonCourante ) )
            {
                _endTime=clock();
                cout<<"Résolu en "<< ( double ) ( _endTime-_startTime ) /CLOCKS_PER_SEC<< " secondes"<<endl;
                if ( solution==false ) solution=true;
                if ( !allSolution ) break; //On passe à k-1
            }
            //Sinon on cherche avec une autre combinaison
        }
    }
    while ( --k>=_instance->_borneMin && solution );
    if ( !solution ) cout<<"Pas de solution en "<<k+1<<endl<<endl;
    cout<<"*** La borne minimale a été atteinte et est de "<<k+2<<" ***"<<endl<<endl;
}
























void Solveur::rechercheExacteEnProfondeurAPartirde_heuristique3 ( unsigned int k, bool allSolution )
{
// 				parcoursSansHeuristique();
    assert ( _instance->_borneMin>0 );
    assert ( _parcours.size() >0 );
    //On part de kMax vers kMin
    bool solution;
    do
    {
        solution=false;
        _startTime=clock();
        _nbComparaisons=0;
        //Parcours des combinaisons de taille k
        Combinaison combinaison ( _parcours );
//         cout<<endl<<"\t\t****** Parcours des combinaisons de taille "<< k <<" ******"<<endl;
        while ( combinaison.next ( k ).size() >0 )
        {
// 					if (combinaison._decalage>=5)
// 					{
// 						for ( vector<Entite*>::const_iterator itRef=_instance->_entites.begin(); itRef!=_instance->_entites.end(); itRef++ )
//                     ( *itRef )->_entitesCritique.clear();
// 					}

            if ( estCaracterisePar_version3 ( combinaison._combinaisonCourante ) )
            {
                _endTime=clock();
//                 cout<<k<<" "<< ( double ) ( _endTime-_startTime ) /CLOCKS_PER_SEC<<endl; //DATA
//                 cout<<"Résolu en "<< ( double ) ( _endTime-_startTime ) /CLOCKS_PER_SEC<< " secondes"<<endl;
                if ( solution==false )
                    solution=true;
                if ( !allSolution ) break; //On passe à k-1
            }
            //Sinon on cherche avec une autre combinaison
        }
    }
    while ( --k>=_instance->_borneMin && solution );
    if ( !solution ) cout<<"Pas de solution en "<<k+1<<endl<<endl;
    cout<<"*** La borne minimale a été atteinte et est de "<<k+2<<" ***"<<endl<<endl;
}


void Solveur::rechercheExacteEnProfondeurAPartirde_heuristique4 ( unsigned int k, bool allSolution )
{
// 				parcoursSansHeuristique();
    assert ( _instance->_borneMin>0 );
    assert ( _parcours.size() >0 );
    //On part de kMax vers kMin
    bool solution;
    do
    {
        solution=false;
        _startTime=clock();
        _nbComparaisons=0;
        //Parcours des combinaisons de taille k
        Combinaison combinaison ( _parcours );
//         cout<<endl<<"\t\t****** Parcours des combinaisons de taille "<< k <<" ******"<<endl;
        while ( combinaison.next ( k ).size() >0 )
        {
// 					if (combinaison._decalage>=5)
// 					{
// 						for ( vector<Entite*>::const_iterator itRef=_instance->_entites.begin(); itRef!=_instance->_entites.end(); itRef++ )
//                     ( *itRef )->_entitesCritique.clear();
// 					}

            if ( estCaracterisePar_version4 ( combinaison._combinaisonCourante ) )
            {
                _endTime=clock();
//                 cout<<k<<" "<< ( double ) ( _endTime-_startTime ) /CLOCKS_PER_SEC<<endl; //DATA
//                 cout<<"Résolu en "<< ( double ) ( _endTime-_startTime ) /CLOCKS_PER_SEC<< " secondes"<<endl;
                if ( solution==false ) solution=true;
                if ( !allSolution ) break; //On passe à k-1
            }
            //Sinon on cherche avec une autre combinaison
        }
    }
    while ( --k>=_instance->_borneMin && solution );
    if ( !solution ) cout<<"Pas de solution en "<<k+1<<endl<<endl;
    cout<<"*** La borne minimale a été atteinte et est de "<<k+2<<" ***"<<endl<<endl;
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

void Solveur::parcoursStandard()
{
    _parcours.resize ( _instance->_genes.size() );
    for ( unsigned int i=0; i<_instance->_genes.size(); i++ )
        _parcours[i]=i;
}







