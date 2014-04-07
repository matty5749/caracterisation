#include "algo.h"

#include "groupe.h"
#include "entite.h"
#include "gene.h"
#include "combinaison.h"

using namespace std;

Algo::Algo ( const Instance* instance ) :_instance ( instance ),_parcours ( vector<int>() ),_e1 ( 0 ),_e2 ( 0 ),_poidCourant ( 0 ),_nbComparaisons ( 0 ),_debut ( true )
{

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
        cout<<"Cette combinaison de taille "<< indices.size() <<" permet de caractériser l'instance"<<endl;
        cout<<"Nb comparaisons: "<<_nbComparaisons<<endl;
        afficheVecteur ( indices );
        cout<<endl;
        return true;
    }
    return false;
}

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
        cout<<"Cette combinaison de taille "<< indices.size() <<" permet de caractériser l'instance"<<endl;
        cout<<"Nb comparaisons: "<<_nbComparaisons<<endl;
        _e1=0;
        _e2=0;
        afficheVecteur ( indices );
        cout<<endl;
        return true;
    }
    return false;
}


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
    afficheVecteur ( indices );
    cout<<endl;
    return true;
}



















bool Algo::estCaracterisePar_version3 ( const vector< int >& indices )
{
    //TODO:Peut-etre mieux vaut il choisir une pile pour _entitesCritique ???

    int k=indices.size();
    bool identique=true;//Vrai si deux entités sont identiques,faux sinon

    //Heuristique TODO:peut etre garder en memoire ceux qui ont été parcouru afin d'éviter de les parcourir une seconde fois
    for ( vector<Entite*>::const_iterator itRef=_instance->_entites.begin(); itRef!=_instance->_entites.end(); itRef++ )
    {
        if ( ( *itRef )->_entitesCritique.size() >0 )
        {
// 					if (k<30) cout<<"TAILLE \t"<<( *itRef )->_entitesCritique.size()<<endl;
            for ( set<Entite*>::const_iterator itComp= ( *itRef )->_entitesCritique.begin(); itComp!= ( *itRef )->_entitesCritique.end(); itComp++ )
            {
                if ( entiteIdentiqueSurIndicesGenes ( *itRef,*itComp,indices ) )
                {
                    if ( _poidCourant < k-1 )
                        ( *itRef )->_entitesCritique.erase ( *itComp );
                    return false;
                }
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
        cout<<"Cette combinaison de taille "<< indices.size() <<" permet de caractériser l'instance"<<endl;
        cout<<"Nb comparaisons: "<<_nbComparaisons<<endl;
        afficheVecteur ( indices );
        cout<<endl;

//         for ( vector<Entite*>::const_iterator itRef=_instance->_entites.begin(); itRef!=_instance->_entites.end(); itRef++ )
//         {
//             ( *itRef )->_entitesCritique.clear();
//
//         }

        return true;
    }
    return false;
}


bool Algo::estCaracterisePar_version4 ( const vector< int >& indices )
{
    int k=indices.size();
    bool caracterise=true;//Vrai si deux entités sont identiques,faux sinon

    //Heuristique 
    //NOTE:peut etre garder en memoire ceux qui ont été parcouru afin d'éviter de les parcourir une seconde fois
    //FAIT: est trop couteux en temp de calcul par rapport à un parcours multiple
    
    for ( vector<Entite*>::const_iterator itRef=_instance->_entites.begin(); itRef!=_instance->_entites.end(); itRef++ )
    {
        if ( ( *itRef )->_entitesCritique.size() >0 )
        {
// 					if (k<30 && ( *itRef )->_entitesCritique.size()>6) cout<<"TAILLE \t"<<( *itRef )->_entitesCritique.size()<<endl;
            for ( set<Entite*>::const_iterator itComp= ( *itRef )->_entitesCritique.begin(); itComp!= ( *itRef )->_entitesCritique.end(); itComp++ )
            {
                if ( entiteIdentiqueSurIndicesGenes ( *itRef,*itComp,indices ) )
                {
                    if ( _poidCourant < k-1 )
                        ( *itRef )->_entitesCritique.erase ( *itComp );
                    return false;
                }
            }
        }
    }

    //Parcours des groupes
    for ( vector<Groupe*>::const_iterator itGroupe=_instance->_groupes.begin(); itGroupe!=_instance->_groupes.end(); itGroupe++ )
    {
        //Nouveau parcours des groupes
        for ( vector<Groupe*>::const_iterator itGroupe2=itGroupe+1; itGroupe2!=_instance->_groupes.end(); itGroupe2++ )
        {
            bool tabou=false;
            map<Groupe*,set<int> >::const_iterator elementIt= ( *itGroupe )->_tabous.find ( *itGroupe2 );
            //Si j'ai une liste d'indice tabous pour ce groupe de comparaison
            if ( ( elementIt != ( *itGroupe )->_tabous.end() ) )
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
                if ( tabou ) continue;//On change de groupe de comparaisons car on est sur d'avoir une caractérisation entre les deux groupes courants
            }
            
            if (!tabou)//Parcours standard
						{
// 							cout<<"Parcours standard"<<endl;
							if ((caracterise=caracteriseDeuxGroupe(*itGroupe,*itGroupe2,indices))) continue;
							else break;
						}
        }
//         cout<<"\t"<<caracterise<<endl;
        if (!caracterise) break;
    }
    if (caracterise)
		{
			cout<<"Cette combinaison de taille "<< indices.size() <<" permet de caractériser l'instance"<<endl;
        cout<<"Nb comparaisons: "<<_nbComparaisons<<endl;
        afficheVecteur ( indices );
        cout<<endl;
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





