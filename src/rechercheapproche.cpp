#include "rechercheapproche.h"

#include "groupe.h"
#include "entite.h"
#include "gene.h"
#include "combinaison.h"

using namespace std;

RechercheApproche::RechercheApproche ( Instance* instance ) :Algo ( instance )
{
    _proba.resize ( _instance->_genes.size(),0 );
    _utiliteRelative.resize ( _instance->_genes.size(),0 );
    _variationFitness.resize ( _instance->_genes.size(),0 );
    _utilisationGene.resize ( _instance->_genes.size(),0 );

    _nbComparaisonsMax=calculNbComparaisonsMax();

}

//TODO: faire une recherche par roulette adaptative.Probabilité initialisé par le taux de similarité globale

void RechercheApproche::initialisationProba ()
{
    float sommeTauxInverse=0;
    for ( unsigned int i=0; i<_instance->_tauxDeSimilariteGlobale.size(); i++ )
        sommeTauxInverse+=1-_instance->_tauxDeSimilariteGlobale[i];

    for ( unsigned int i=0; i<_instance->_tauxDeSimilariteGlobale.size(); i++ )
    {
// 			cout<<1-_instance->_tauxDeSimilariteGlobale[i]<<endl;
        _proba[i]= ( 1-_instance->_tauxDeSimilariteGlobale[i] ) /sommeTauxInverse;
    }
//     sleep(5);

    //Ajustement des proba sur une echelle de 0 à 1
    for ( unsigned int i=1; i<_proba.size(); i++ )
    {
        _proba[i]+=_proba[i-1];
//         cout<<_proba[i]<<endl;
    }
}

void RechercheApproche::roulette ()
{
    initialisationProba ();

    //Lancement de la recherche
    unsigned int k=_instance->_genes.size()-1;

    while ( k>_instance->_borneMin )
    {
        //Création de la combinaison
        set<int> combinaison;
        do
        {
            double alea = ( double ) rand() /RAND_MAX;
            //Recherche du gene que l'on selectionne d'après le tirage aleatoire
            for ( unsigned int i=0; i<_proba.size(); i++ )
            {
//                 cout<<_proba[i]<<"\t"<<alea<<endl;
                if ( _proba[i]>=alea )
                {
                    combinaison.insert ( i );
                    break;
                }
            }
        }
        while ( combinaison.size() < k );

        //Transformation en tableau d'indice
        vector<int> indices;
        indices.resize ( combinaison.size() );
        copy ( combinaison.begin(),combinaison.end(),indices.begin() );

        if ( estCaracterisePar_version4 ( indices ) )
        {
            cout<<"L'instance admet une caracterisation de taille " <<k<<endl;
            --k;
            _individus.clear();
        }
//         else //Si solution proche, travail sur la solution partielle
//         {
//             double rapport= ( double ) _fitness/_nbComparaisonsMax;
//             if ( k<=15 )
//                 if ( rapport>=0.85 )
//                 {
//                     if ( _individus.size() <10 )
//                     {
//                         _individus.push_back ( indices );
//                     }
//                     else //Croisement
//                     {
//                         cout<<"CROISEMENT"<<endl;
//                         vector<vector<int> > enfants;
//                         for ( vector<vector<int> >::iterator itPere=_individus.begin(); itPere!=_individus.end()-1; itPere++ )
//                             for ( vector<vector<int> >::iterator itMere=itPere+1; itMere!=_individus.end(); itMere++ )
//                             {
//                                 vector<int> enfant=croisementParPlusFaibleSimilariteEntreLesIndices ( *itPere,*itMere );
//                                 if ( estCaracterisePar_version4 ( indices ) )
//                                 {
//                                     cout<<"OBTENU PAR CROISEMENT L'instance admet une caracterisation de taille " <<k<<endl;
//                                     --k;
//                                 }
//                                 rapport= ( double ) _fitness/_nbComparaisonsMax;
//                                 if ( rapport>=0.87 )
//                                 {
//                                     afficheVecteur ( *itPere );
//                                     afficheVecteur ( *itMere );
//                                     afficheVecteur ( enfant );
//                                     cout<< ( double ) _fitness/_nbComparaisonsMax<<endl;
//                                 }
//                             }
//                         _individus.clear();
//                         cout<<"FIN CROISEMENT"<<endl;
//                     }
//                 }
//         }

    }
}

// TODO:Optimisable en utilisant enfant en parametre
vector< int > RechercheApproche::croisementParPlusFaibleSimilariteEntreLesIndices ( const vector< int >& pere, const vector< int >& mere ) const
{
    vector<int> enfant;
    enfant.resize ( pere.size(),0 );
    int i=0;
    vector<int>::const_iterator itMere=mere.begin();
    for ( vector<int>::const_iterator itPere=pere.begin(); itPere!=pere.end(); itPere++,itMere++,i++ )
        if ( *itPere<=*itMere ) enfant[i]=*itPere;
        else enfant[i]=*itMere;

    return enfant;
}


// void RechercheApproche::rouletteAdaptative ( float pMin )
// {
//     initialisationProba ();
//
//     //Lancement de la recherche
//     unsigned int k=_instance->_genes.size()-1;
//
//     long long unsigned int nbIterations=2;
//     unsigned int frequence=100;
//     while ( k>_instance->_borneMin )
//     {
//
//
//         //MAJ
//         if ( nbIterations++%frequence==0 )
//         {
//             //Calcul des utilités relatives
// // 					cout<<"********************************"<<endl;
//             for ( unsigned int i=0; i<_utiliteRelative.size(); i++ )
//             {
//                 if ( _utilisationGene[i]>0 )
// 								{
// 									_utiliteRelative[i]=(double)1/_utilisationGene[i]*_variationFitness[i]/_nbComparaisonsMax;
// 								}
//                 else _utiliteRelative[i]=0;
// // 								cout<<_utiliteRelative[i]<<endl;
//             }
//
//             //MAJ proba
//             float sommeUtiliteRelative=0;
//             for ( unsigned int i=0; i<_utiliteRelative.size(); i++ )
//                 sommeUtiliteRelative+=_utiliteRelative[i];
//
//             for ( unsigned int i=0; i<_instance->_tauxDeSimilariteGlobale.size(); i++ )
//             {
//                 _proba[i]= pMin + ( 1-_instance->_genes.size() *pMin ) *_utiliteRelative[i] /sommeUtiliteRelative;
//             }
//
//             float sommeProba=0;
//             for ( unsigned int i=1; i<_proba.size(); i++ )
//                 sommeProba+=_proba[i];
//
//             //Ajustement des proba sur une echelle de 0 à 1
//             for ( unsigned int i=1; i<_proba.size(); i++ )
//             {
//                 _proba[i]+=_proba[i-1];
//             }
// //             cout<<_proba[_proba.size()-1]<<endl;
// // sleep(5);
// //             //Reinitialisation de _utilisationGene et _variationFitness
// //             for (int i=0;i<_instance->_genes.size();i++)
// // 						{
// // 							_utilisationGene[i]=0;
// // 							_variationFitness[i]=0;
// // 						}
//         }
//
//         //Création de la combinaison
//         set<int> combinaison;
//         do
//         {
//             double alea = ( double ) rand() /RAND_MAX;
//             //Recherche du gene que l'on selectionne d'après le tirage aleatoire
//             for ( unsigned int i=0; i<_proba.size(); i++ )
//             {
//                 if ( _proba[i]>=alea )
//                 {
//                     combinaison.insert ( i );
//                     break;
//                 }
//             }
//         }
//         while ( combinaison.size() <k );
//
// 				//Transformation en tableau d'indice
//         vector<int> indices;
//         indices.resize ( combinaison.size() );
//         copy ( combinaison.begin(),combinaison.end(),indices.begin() );
//
// 				if (k<17) afficheVecteur(indices);
//         if ( estCaracterisePar_version4( indices ) )
//         {
//             cout<<"L'instance admet une caracterisation de taille " <<k<<endl;
//             --k;
//         }
//
//
//         //MAJ _variationFitness et _utilisationGene
//         for ( unsigned int i=0; i<indices.size(); i++ )
//         {
//             _utilisationGene[indices[i]]++;
//             _variationFitness[indices[i]]+=_fitness;
//         }
//     }
// }


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

