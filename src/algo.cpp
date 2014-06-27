#include "algo.h"

#include "groupe.h"
#include "entite.h"
#include "gene.h"
#include "combinaison.h"

using namespace std;

Algo::Algo ( Instance* instance ) :_instance ( instance ),_parcours ( vector<int>() ),_e1 ( 0 ),_e2 ( 0 ),_poidCourant ( 0 ),_nbComparaisons ( 0 ),_debut ( true ),_nbComparaisonsMax ( 0 ),_startTime ( 0 ),_endTime ( 0 ),_cumulTime ( 0 )
{

}


int Algo::calculNbComparaisonsMax()
{
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
                    ++_nbComparaisonsMax;
                }//Fin parcours entiteIt2
            }//Fin parcours itGroupe2
        }//Fin parcours entiteIt
    }//Fin parcours itGroupe

    return _nbComparaisonsMax;
}


bool Algo::entiteIdentiqueSurIndicesGenes ( const Entite* const & e1, const Entite*const & e2, const vector< int > &indices )
{
    _nbComparaisons++;
    assert ( e1 );
    assert ( e2 );
    _poidCourant=0;
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
            else _poidCourant++;
        }//Fin parcours indices
        if ( identique ) return identique;
    }
    return identique;
}


//OUI
bool Algo::estCaracterisePar ( const vector< int > &indices )
{
    bool identique=true;//Vrai si deux entités sont identiques,faux sinon

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
//         cout<<"Cette combinaison de taille "<< indices.size() <<" permet de caractériser l'instance"<<endl;
//         cout<<"Nb comparaisons: "<<_nbComparaisons<<endl;
//         afficheVecteur ( indices );
//         cout<<endl;

        cout<<indices.size() <<" "<<_nbComparaisons;	//DATA
        return true;
    }
    return false;
}


// bool Algo::estCaracteriseParFullVersion ( const vector< int >& indices )
// {
//     _fitness=0;
//     bool identique=false;//Vrai si deux entités sont identiques,faux sinon
//
//     //Parcours des groupes
//     for ( vector<Groupe*>::const_iterator itGroupe=_instance->_groupes.begin(); itGroupe!=_instance->_groupes.end(); itGroupe++ )
//     {
//         //Parcours des entités du groupes
//         for ( vector<Entite*>::const_iterator entiteIt= ( *itGroupe )->_entites.begin(); entiteIt!= ( *itGroupe )->_entites.end(); entiteIt++ )
//         {
//             //Nouveau parcours des groupes
//             for ( vector<Groupe*>::const_iterator itGroupe2=itGroupe+1; itGroupe2!=_instance->_groupes.end(); itGroupe2++ )
//             {
//                 //Nouveau parcours des entite
//                 for ( vector<Entite*>::const_iterator entiteIt2= ( *itGroupe2 )->_entites.begin(); entiteIt2!= ( *itGroupe2 )->_entites.end(); entiteIt2++ )
//                 {
//                     if ( ( entiteIdentiqueSurIndicesGenes ( *entiteIt,*entiteIt2,indices ) ) )
//                     {
//                         if ( !identique ) identique=true;
//                         ++_fitness;
// // 												break;
//                     }
// //                     else ++_fitness;
//                 }//Fin parcours entiteIt2
// //                 if ( identique ) break;
//             }//Fin parcours itGroupe2
// //             if ( identique ) break;
//         }//Fin parcours entiteIt
// //         if ( identique ) break;
//     }//Fin parcours itGroupe
//     if ( ! identique )
//     {
// //         cout<<"Cette combinaison de taille "<< indices.size() <<" permet de caractériser l'instance"<<endl;
// //         cout<<"Nb comparaisons: "<<_nbComparaisons<<endl;
// //         afficheVecteur ( indices );
// //         cout<<endl;
//
//         cout<<indices.size() <<" "<<_nbComparaisons<<endl;	//DATA
//
//         return true;
//     }
//     return false;
// }


//NON
bool Algo::estCaracterisePar_version1 ( const vector< int >& indices )
{
    bool identique=true;//Vrai si deux entités sont identiques,faux sinon

    //Petite heuristique
    if ( _e1!=_e2 && entiteIdentiqueSurIndicesGenes ( _e1,_e2,indices ) )
    {
        return false;
    }

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
//         cout<<"Cette combinaison de taille "<< indices.size() <<" permet de caractériser l'instance"<<endl;
//         cout<<"Nb comparaisons: "<<_nbComparaisons<<endl;
// 				cout<<indices.size()<<" "<<_nbComparaisons<<endl; //DATA

        _e1=0;
        _e2=0;
//         afficheVecteur ( indices );
//         cout<<endl;
        return true;
    }
    return false;
}

//A REVOIR MAIS A PRIORI NON
bool Algo::estCaracterisePar_version2 ( const vector< int >& indices )
{
    int k=indices.size();
    //CAS INITIAL
    if ( _debut ) //Si debut: parcours total des entités sans coupure dans l'arbre afin d'initialiser les map de _poids dans Entite
    {
//         cout<<"CAS INITIAL"<<endl;
        bool identique=false;

        //Parcours des entités de reference
        for ( vector<Entite*>::const_iterator itRef=_instance->_entites.begin(); itRef!=_instance->_entites.end(); itRef++ )
        {
            //Parcours des entités de comparaison
            for ( vector<Entite*>::const_iterator itComp=itRef+1; itComp!=_instance->_entites.end(); itComp++ )
            {
                //On ne doit pas comparer 2 entités appartenant au même groupe
                //Et une entite ne peut pas etre une entite de comparaison
                if ( ( *itRef )->_idGroupe == ( *itComp )->_idGroupe ) continue;
                else //Sinon comparaison des 2 entités
                {
                    if ( entiteIdentiqueSurIndicesGenes ( *itRef,*itComp,indices ) )
                    {
                        if ( !identique ) identique=true;
//                     ( *itComp )->_poid=_poidCourant;	<--Pas de coupure (voir tout premier commentaire de la méthode)
//                     _e1=*itRef;											<--Pas de coupure (voir tout premier commentaire de la méthode)
//                     _e2=*itComp;											<--Pas de coupure (voir tout premier commentaire de la méthode)
// 										return false;											<--Pas de coupure (voir tout premier commentaire de la méthode)
                    }
                    //Dans tout les cas
                    if ( _poidCourant>=k-1 )
                        ( *itRef )->_poidsCritique[*itComp]=_poidCourant;				// <-- Insertion
                    else ( *itRef )->_poidsNonCritique[*itComp]=_poidCourant;		// <-- Insertion
                }
            }
        }
        _debut=false;
        if ( identique ) return false;
    }
    //CAS GENERAL
    else
    {
//         cout<<"CAS GENERAL"<<endl;
//         //Petite heuristique
//         if ( _e1!=_e2 && entiteIdentiqueSurIndicesGenes ( _e1,_e2,indices ) )
//         {
//             _nbCutPetiteHeuristique++;
//             return false;
//         }
//
        //Heuristique: on compare toute les entités qui ont un poids >= k-1 (_poidCritique)
        for ( vector<Entite*>::const_iterator itRef=_instance->_entites.begin(); itRef!=_instance->_entites.end(); itRef++ )
        {
// 						cout<<(*itRef)->_poidsCritique.size()<<endl;

            vector<pair<Entite*,int> > aBasculerVersPoidsNonCritique;
            aBasculerVersPoidsNonCritique.reserve ( _instance->_entites.size() );

            for ( map<Entite*,int>::iterator itComp= ( *itRef )->_poidsCritique.begin(); itComp!= ( *itRef )->_poidsCritique.end(); itComp++ )
            {
                if ( itComp->second < k-1 )
                {
                    cout<<"non"<<endl;
                    continue;
                }
                if ( entiteIdentiqueSurIndicesGenes ( *itRef,itComp->first,indices ) )
                {
// 									cout<<"\t test"<<endl;
                    assert ( _poidCourant>=k-1 );
                    itComp->second=_poidCourant;

                    //MAJ de la map _poidsCritique de l'iterateur
                    for ( vector<pair<Entite*,int> >::const_iterator it=aBasculerVersPoidsNonCritique.begin(); it!=aBasculerVersPoidsNonCritique.end(); it++ )
                        ( *itRef )->basculerVersPoidsNonCritique ( it->first,it->second );

                    return false; //CUT
                }
                else if ( _poidCourant < k-1 )
                    aBasculerVersPoidsNonCritique.push_back ( *itComp );
            }

            //MAJ de la map _poidsCritique de l'iterateur
            for ( vector<pair<Entite*,int> >::const_iterator it=aBasculerVersPoidsNonCritique.begin(); it!=aBasculerVersPoidsNonCritique.end(); it++ )
                ( *itRef )->basculerVersPoidsNonCritique ( it->first,it->second );
        }
    }

    //Dans tout les cas, si il y eu une caractérisation
    _debut=true;
    for ( vector<Entite*>::const_iterator it=_instance->_entites.begin(); it!=_instance->_entites.end(); it++ )
    {
        ( *it )->_poidsCritique.clear();
        ( *it )->_poidsNonCritique.clear();
    }

    cout<<"Cette combinaison de taille "<< indices.size() <<" permet de caractériser l'instance"<<endl;
    cout<<_nbComparaisons<<endl;
    _e1=0;
    _e2=0;
    afficheVecteur<int>( indices );
    cout<<endl;
    return true;
}


















//OUI
bool Algo::estCaracterisePar_version3 ( const vector< int >& indices )
{
    //TODO:Peut-etre mieux vaut il choisir une pile pour _entitesCritique ???
    //FAIT: NON

    int k=indices.size();
    bool identique=true;//Vrai si deux entités sont identiques,faux sinon

    //Heuristique TODO:peut etre garder en memoire ceux qui ont été parcouru afin d'éviter de les parcourir une seconde fois
    //FAIT: Non trop couteux

    for ( vector<Entite*>::const_iterator itRef=_instance->_entites.begin(); itRef!=_instance->_entites.end(); itRef++ )
    {
        if ( ( *itRef )->_entitesCritique.size() >0 )
        {
// 					if (k<30) cout<<"TAILLE \t"<<( *itRef )->_entitesCritique.size()<<endl;
            for ( set<Entite*>::const_iterator itComp= ( *itRef )->_entitesCritique.begin(); itComp!= ( *itRef )->_entitesCritique.end(); itComp++ )
            {
                if ( entiteIdentiqueSurIndicesGenes ( *itRef,*itComp,indices ) )
                {
//                     if ( _poidCourant < k-1 )
//                         ( *itRef )->_entitesCritique.erase ( *itComp );
                    return false;
                }
//                 else if ( _poidCourant < k-1 )
//                     ( *itRef )->_entitesCritique.erase ( *itComp );
            }
        }
    }

    //Parcours des groupes
    for ( vector<Groupe*>::const_iterator itGroupe=_instance->_groupes.begin(); itGroupe!=_instance->_groupes.end(); itGroupe++ )
    {
        //Parcours des entités du groupes
        for ( vector<Entite*>::const_iterator itRef= ( *itGroupe )->_entites.begin(); itRef!= ( *itGroupe )->_entites.end(); itRef++ )
        {
            //Nouveau parcours des groupes
            for ( vector<Groupe*>::const_iterator itGroupe2=itGroupe+1; itGroupe2!=_instance->_groupes.end(); itGroupe2++ )
            {
                //Nouveau parcours des entite
                for ( vector<Entite*>::const_iterator itComp= ( *itGroupe2 )->_entites.begin(); itComp!= ( *itGroupe2 )->_entites.end(); itComp++ )
                {
                    if ( ( identique=entiteIdentiqueSurIndicesGenes ( *itRef,*itComp,indices ) ) )
                    {
                        /*Si les deux entités sont identiques, on les garde en memoire afin de les tester en premier
                        					  lors de la prochaine combinaison afin de couper des brancges dans l'arbre de recherche*/
                        ( *itRef )->_entitesCritique.insert ( *itComp );
                        break;
                    }
                    if ( _poidCourant == k-1 )
                        ( *itRef )->_entitesCritique.insert ( *itComp );
                }//Fin parcours itComp
                if ( identique ) break;
            }//Fin parcours itGroupe2
            if ( identique ) break;
        }//Fin parcours itRef
        if ( identique ) break;
    }//Fin parcours itGroupe
    if ( ! identique )
    {
//         cout<<"Cette combinaison de taille "<< indices.size() <<" permet de caractériser l'instance"<<endl;
//         cout<<"Nb comparaisons: "<<_nbComparaisons<<endl;
//         afficheVecteur ( indices );
//         cout<<endl;

        cout<<indices.size() <<" "<<_nbComparaisons<<endl;	//DATA

//         for ( vector<Entite*>::const_iterator itRef=_instance->_entites.begin(); itRef!=_instance->_entites.end(); itRef++ )
//         {
//             ( *itRef )->_entitesCritique.clear();
//
//         }

        return true;
    }
    return false;
}


bool trieGroupeParTauLocal ( Groupe const * const g1,Groupe const * const g2 )
{
    return g1->_moyenneTauxDeSimilariteLocal<g2->_moyenneTauxDeSimilariteLocal;
}

//OUI
bool Algo::estCaracterisePar_version4 ( const vector< int >& indices )
{
    _fitness=0;
    int k=indices.size();
    bool caracterise=true;//Vrai si deux entités sont identiques,faux sinon

    //Heuristique
    //NOTE:peut etre garder en memoire ceux qui ont été parcouru afin d'éviter de les parcourir une seconde fois
    //FAIT: est trop couteux en temp de calcul par rapport à un parcours multiple

    //PMDA
    for ( vector<Entite*>::const_iterator itRef=_instance->_entites.begin(); itRef!=_instance->_entites.end(); itRef++ )
    {
        if ( ( *itRef )->_entitesCritique.size() >0 )
        {
            for ( set<Entite*>::const_iterator itComp= ( *itRef )->_entitesCritique.begin(); itComp!= ( *itRef )->_entitesCritique.end(); itComp++ )
            {
                if ( entiteIdentiqueSurIndicesGenes ( *itRef,*itComp,indices ) )
                {
                    return false;
                }
//                 else if ( _poidCourant < k-1 )											//TODO:regarder de plus pres			<--En commentaire car meilleur si l'on garde en memoire
//                     ( *itRef )->_entitesCritique.erase ( *itComp );
            }
        }
    }


//     //AJOUT ALGO DYNAMIQUE TRIE PAR PETIT TAU SUR INDICE DES COMBINAISONS <-- NE FONCTIONNE PAS BIEN
//     //Heuristique sur les taux de similarite locale (petit tau)
//     //Parcours exhaustif des groupe
//     for ( vector<Groupe*>::const_iterator itRef=_instance->_groupes.begin(); itRef!=_instance->_groupes.end(); itRef++ )
//     {
//         //Initialisation _moyenneTauxDeSimilariteLocal
//         ( *itRef )->_moyenneTauxDeSimilariteLocal=0;
//         for ( vector<Groupe*>::iterator itComp=_instance->_groupes.begin(); itComp!=_instance->_groupes.end(); itComp++ )
//         {
//             if ( *itRef==*itComp ) continue;
//             ( *itRef )->_moyenneTauxDeSimilariteLocal+=calculTauxDeSimilariteEntreLesDeuxGroupes ( **itRef,**itComp );
//         }
//         ( *itRef )->_moyenneTauxDeSimilariteLocal/=_instance->_groupes.size()-1;
//     }
//
//     //Trie des groupes par petit tau
//     sort ( _instance->_groupes.begin(),_instance->_groupes.end(),trieGroupeParTauLocal );

// 		for ( vector<Groupe*>::const_iterator itRef=_instance->_groupes.begin(); itRef!=_instance->_groupes.end(); itRef++ )
// 			cout<<(*itRef)->_moyenneTauxDeSimilariteLocal<<endl;
// 		cout<<endl;
    //FIN (petit tau)

    //FIN AJOUT ALGO DYNAMIQUE TRIE PAR PETIT TAU SUR INDICE DES COMBINAISONS

    //NOUVEAU PARCOURS DYNAMIQUE SUR INDICE DES COMBINAISONS <-- FONCTIONNE MOINS BIEN EN DYNAMIQUE QUE EN STATIQUE
// 		_instance->majParcoursGroupePourCombinaison(indices);

    //NOUVEAU PARCOURS DE GROUPE
    for ( multimap<float,pair<const Groupe * const,const Groupe * const> >::const_reverse_iterator it=_instance->_parcoursGroupe.rbegin(); it!=_instance->_parcoursGroupe.rend(); it++ )
    {
        const Groupe * const itGroupe=it->second.first;
        const Groupe * const itGroupe2=it->second.second;


//*     //Parcours des groupes
//*     for ( vector<Groupe*>::const_iterator itGroupe=_instance->_groupes.begin(); itGroupe!=_instance->_groupes.end(); itGroupe++ )
//*     {
//*         //Nouveau parcours des groupes
//**         for ( vector<Groupe*>::const_iterator itGroupe2=itGroupe+1; itGroupe2!=_instance->_groupes.end(); itGroupe2++ )
//**         {

        bool tabou=false;
//DEBUT TABOU
        map<Groupe*,set<int> >::const_iterator elementIt= itGroupe->_tabous.find ( const_cast<Groupe*>(itGroupe2) );
        //Si j'ai une liste d'indice tabous pour ce groupe de comparaison
        if ( ( elementIt != itGroupe->_tabous.end() ) )
        {
//                         cout<< ( *itGroupe )->_id<<" / "<< ( *itGroupe2 )->_id<<endl;
            //Je cherche si un des indices d'indices fait partie de cette liste
            for ( unsigned int i=0; i<indices.size(); i++ )
            {
//                             cout<<i<<endl;
                if ( elementIt->second.find ( indices[i] ) !=elementIt->second.end() )
                {
                    tabou=true;
                    break;
                }
            }
//                         cout<<endl;
            if ( tabou )
            {
                ++_fitness;
                continue;//On change de groupe de comparaisons car on est sur d'avoir une caractérisation entre les deux groupes courants
            }
        }

        //         if ( !tabou ) //Parcours standard
        //         {
        // // 							cout<<"Parcours standard"<<endl;
        //             if ( ( caracterise=caracteriseDeuxGroupe ( *itGroupe,*itGroupe2,indices ) ) )
        //             {
        //                 _fitness+= ( *itGroupe )->_entites.size() * ( *itGroupe2 )->_entites.size();
        //                 continue;
        //             }
        //             else break;
        //         }
//FIN TABOU


        //POUR NOUVEAU PARCOURS GROUPE
        if ( !tabou ) //Parcours standard
        {
// 							cout<<"Parcours standard"<<endl;
            if ( ( caracterise=caracteriseDeuxGroupe ( itGroupe,itGroupe2,indices ) ) )
            {
                _fitness+=  itGroupe->_entites.size() * itGroupe2->_entites.size();
                continue;
            }
            else break;
        }


//**         }
//         cout<<"\t"<<caracterise<<endl;
        if ( !caracterise ) break;
//*     }
    }
    if ( caracterise )
    {
//         cout<<"Cette combinaison de taille "<< indices.size() <<" permet de caractériser l'instance"<<endl;
//         cout<<"Nb comparaisons: "<<_nbComparaisons<<endl;
//         afficheVecteur ( indices );
//         cout<<endl;

        cout<<indices.size() <<"\t"<<_nbComparaisons;	//DATA
    }
//     cout<<caracterise<<endl;
    return caracterise;
}


bool Algo::caracteriseDeuxGroupe ( const Groupe*const& g1, const Groupe*const& g2, const vector< int >& indices )
{
    int k=indices.size();
    bool identique;//Vrai si deux entités sont identiques,faux sinon

    //Parcours des entités du groupe g1
    for ( vector<Entite*>::const_iterator itRef= g1->_entites.begin(); itRef!= g1->_entites.end(); itRef++ )
    {
        //Parcours des entités du groupe g2
        for ( vector<Entite*>::const_iterator itComp= g2->_entites.begin(); itComp!= g2->_entites.end(); itComp++ )
        {
// 					set<Entite*>::const_iterator itFind=(*itRef)->_entitesCritique.find(*itComp);
// 					if (itFind!=(*itRef)->_entitesCritique.end()) continue; //Si les entités ont déja été comparé, on continue
            if ( ( identique=entiteIdentiqueSurIndicesGenes ( *itRef,*itComp,indices ) ) )
            {
                /*Si les deux entités sont identiques, on les garde en memoire afin de les tester en premier
                					  lors de la prochaine combinaison afin de couper des brancges dans l'arbre de recherche*/
                ( *itRef )->_entitesCritique.insert ( *itComp );
                break;
            }
            if ( _poidCourant == k-1 )
                ( *itRef )->_entitesCritique.insert ( *itComp );
        }//Fin parcours itComp
        if ( identique ) break;
    }
    if ( identique ) return false;
    else return true;
}





