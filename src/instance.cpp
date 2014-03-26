#include "instance.h"

#include "groupe.h"
#include "entite.h"
#include "gene.h"

using namespace std;

// #ifdef INSTANCE_DEBUG
//   if (! id-1<_vGroupes.size() )
// 	{
// 		cout<<"Groupe* Instance::getGroupById ( unsigned int id ) const"<<endl;
// 		cout<<"Le groupe "<<id<<" n'existe pas!"<<endl;
// 	}
// #endif



Instance::Instance() :_nbEntites ( 0 )
{

}

Instance::~Instance()
{
    for ( vector<Entite*>::iterator it=_entites.begin(); it!=_entites.end(); it++ )
        delete *it;

    for ( vector<Gene*>::iterator it=_genes.begin(); it!=_genes.end(); it++ )
        delete *it;

    for ( vector<Groupe*>::iterator it=_groupes.begin(); it!=_groupes.end(); it++ )
        delete *it;
}


void Instance::parseDac ( char* nomFic )
{
    ifstream inputFile ( nomFic );
    if ( !inputFile )
    {
        cout<<"Nom de fichier invalide."<<endl;
        exit ( EXIT_FAILURE );
    }

    string ligne,oldLigne;
    //Parcours pour avoir le nombre d'entite <-- peut être optimiser...
    while ( getline ( inputFile,ligne ) )
    {
        oldLigne=ligne;
    }
    istringstream iss ( oldLigne );//Derniere ligne
    unsigned int nbEntites;
    iss>>nbEntites;
    _entites.reserve ( nbEntites );

    inputFile.close();
    inputFile.open ( nomFic );

    bool debut=true;//Afin d'initialiser _genes
    while ( getline ( inputFile,ligne ) )
    {
        if ( ligne[0]=='#' ) continue;//Commentaire omis
        vector<string> ligne_vecteur;
        // remplir la liste de mots
        istringstream iss ( ligne );
        copy ( istream_iterator<string> ( iss ),istream_iterator<string>(),back_inserter ( ligne_vecteur ) );
        //Vecteur[0] <-- identifiant de l'entité
        istringstream iss2 ( ligne_vecteur[0] );
        int id;
        iss2>>id;
        //Vecteur[1] <-- groupe de l'entité
        istringstream iss3 ( ligne_vecteur[1] );
        int idGroupe;
        iss3>>idGroupe;
        //Reste <-- chaine de bit
        std::string chaine_de_bit="";
        for ( unsigned int i=2; i<ligne_vecteur.size(); i++ )
        {
            chaine_de_bit+=ligne_vecteur[i];
        }

        //Initialisation de _genes si DEBUT
        if ( debut )
        {
            _genes.reserve ( chaine_de_bit.size() );
            for ( unsigned int i=0; i<chaine_de_bit.size(); i++ )
            {
                Gene* gene=new Gene ( i+1,nbEntites ,this ); //nbEntites pour l'allocation de Gene::_entites
                _genes.push_back ( gene );
            }
            debut=false;
        }

        //Création de l'entité
        Entite* entite=new Entite ( id,idGroupe,chaine_de_bit,this );
        _nbEntites++;
        //Récupération ou création de groupe
        Groupe* groupe=getGroupById ( idGroupe );
        if ( groupe==0 )
        {
            groupe=new Groupe ( idGroupe, this );
            _groupes.push_back ( groupe );
        }
        //MAJ du groupe avec l'entité courante
        groupe->_entites.push_back ( entite );
        _entites.push_back ( entite );
    }

    cout<<"Avant traitement:"<<endl;
    cout<<"Nb groupes:\t"<<_groupes.size() <<endl;
    cout<<"Nb entites:\t"<<_entites.size() <<endl;
    cout<<"Nb variables:\t"<<_genes.size() <<endl;

    if ( nbEntites!=_nbEntites )
    {
        cout<<"Probleme dans le nombre d'entite dans void Instance::parseDac ( char* nomFic )"<<endl;
        exit ( EXIT_FAILURE );
    }
}

void Instance::preTraitement()
{
    bool supression;
    do
    {
        supression=false;
        set<Gene*> geneASupprimer;
        set<Entite*> entiteASupprimer;
        //1.Colonne dont toutes les valeurs sont identiques (tout a 1 ou tout a 0)
        for ( vector<Gene*>::iterator it=_genes.begin(); it!=_genes.end(); it++ )
        {
            if ( ( *it )->nbOne() ==0 || ( *it )->nbOne() == _nbEntites )
            {
                geneASupprimer.insert ( *it );
            }
        }

        //2.Chaque colonne doit etre unique
        for ( vector<Gene*>::iterator it1=_genes.begin(); it1!=_genes.end(); it1++ )
            for ( vector<Gene*>::iterator it2=it1+1; it2!=_genes.end(); it2++ )
                if ( estSimilaire ( *it1,*it2 ) ) geneASupprimer.insert ( *it2 );

        //3.Chaque entite doit etre unique
        for ( vector<Entite*>::iterator it1=_entites.begin(); it1!=_entites.end(); it1++ )
            for ( vector<Entite*>::iterator it2=it1+1; it2!=_entites.end(); it2++ )
                if ( estSimilaire ( *it1,*it2 ) ) entiteASupprimer.insert ( *it2 );

        //SUPPRESSION DES GENES REDONDANTS
        for ( set<Gene*>::iterator it=geneASupprimer.begin(); it!=geneASupprimer.end(); it++ )
        {
            //MAJ de _genes
            vector<Gene*>::iterator geneIt=find ( _genes.begin(),_genes.end(),*it );
            if ( geneIt != _genes.end() )
            {
                _genes.erase ( geneIt ); //Redimenssionnement du vecteur
            }
            else cout<<"On ne devrait jamais être dans ce cas (1). (void Instance::preTraitement() --> SUPPRESSION DES GENES REDONDANTS)"<<endl;

            //MAJ de _genes dans Entite
            for ( vector<Entite*>::iterator entiteIt=_entites.begin(); entiteIt!=_entites.end(); entiteIt++ )
            {
                vector<pair<Gene*,bool> >::iterator geneIt2=find_if ( ( *entiteIt )->_genes.begin(), ( *entiteIt )->_genes.end(),bind2nd ( memeGene(),**it ) );
                if ( geneIt2 != ( *entiteIt )->_genes.end() )
                {
                    ( *entiteIt )->_genes.erase ( geneIt2 ); //Redimenssionnement du vecteur
                }
                else cout<<"On ne devrait jamais être dans ce cas (2). (void Instance::preTraitement() --> SUPPRESSION DES GENES REDONDANTS)"<<endl;
            }
            //DESTRUCTION GENE REDONDANT
            delete *it;
            supression=true;
        }

        //SUPPRESSION DES ENTITES REDONDANTES
        for ( set<Entite*>::iterator it=entiteASupprimer.begin(); it!=entiteASupprimer.end(); it++ )
        {
            //MAJ de _entites
            vector<Entite*>::iterator entiteIt=find ( _entites.begin(),_entites.end(),*it );
            if ( entiteIt != _entites.end() )
            {
                _entites.erase ( entiteIt ); //Redimenssionnement du vecteur
            }
            else cout<<"On ne devrait jamais être dans ce cas (3). (void Instance::preTraitement() --> SUPPRESSION DES GENES REDONDANTS)"<<endl;

            //MAJ de _entites dans son groupe
            Groupe* groupe=getGroupById ( ( *it )->_idGroupe );
            if ( groupe != 0 )
            {
                entiteIt=find ( groupe->_entites.begin(),groupe->_entites.end(),*it );
                if ( entiteIt != groupe->_entites.end() )
                {
                    groupe->_entites.erase ( entiteIt ); //Redimenssionnement du vecteur
                }
                else cout<<"On ne devrait jamais être dans ce cas (4). (void Instance::preTraitement() --> SUPPRESSION DES GENES REDONDANTS)"<<endl;
            }
            else cout<<"On ne devrait jamais être dans ce cas (5). (void Instance::preTraitement() --> SUPPRESSION DES GENES REDONDANTS)"<<endl;

            //MAJ de _entites dans Gene
            for ( vector<Gene*>::iterator geneIt=_genes.begin(); geneIt!=_genes.end(); geneIt++ )
            {
                vector<pair<Entite*,bool> >::iterator entiteIt2=find_if ( ( *geneIt )->_entites.begin(), ( *geneIt )->_entites.end(),bind2nd ( memeEntite(),**it ) );
                if ( entiteIt2 != ( *geneIt )->_entites.end() )
                {
                    ( *geneIt )->_entites.erase ( entiteIt2 ); //Redimenssionnement du vecteur
                }
                else cout<<"On ne devrait jamais être dans ce cas (6). (void Instance::preTraitement() --> SUPPRESSION DES GENES REDONDANTS)"<<endl;
            }

            //DESTRUCTION ENTITE REDONDANTE
            delete *it;
            supression=true;
        }
    }
    while ( supression );
    //Si un groupe est vide, l'instance est mal formé
    for ( vector<Groupe*>::iterator it=_groupes.begin(); it!=_groupes.end(); it++ )
        if ( ( *it )->_entites.size() ==0 )
        {
            cout<<"Après réduction, au moins un groupe est vide (groupe id="<< ( *it )->_id<<"), l'instance est donc mal formé!"<<endl;
            exit ( EXIT_FAILURE );
        }
    _nbEntites=_entites.size();
    cout<<"Après traitement:"<<endl;
    cout<<"Nb groupes:\t"<<_groupes.size() <<endl;
    cout<<"Nb entites:\t"<<_entites.size() <<endl;
    cout<<"Nb variables:\t"<<_genes.size() <<endl;
}


Groupe* Instance::getGroupById ( unsigned int id ) const
{
    for ( vector<Groupe*>::const_reverse_iterator rit=_groupes.rbegin(); rit!=_groupes.rend(); rit++ )
        if ( ( *rit )->_id==id )
            return *rit;
    return 0; //Le groupe n'a pas encore été créé
}




































