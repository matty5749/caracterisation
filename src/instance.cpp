#include "instance.h"

#include "groupe.h"
#include "entite.h"
#include "gene.h"
#include "combinaison.h"

using namespace std;


Instance::Instance ( std::string nom ) :_nom ( nom )
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
//         _nbEntites++;
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
}

void Instance::parseXml ( char* nomFic )
{
    QFile file ( nomFic );
    QXmlInputSource inputSource ( &file );
    QXmlSimpleReader reader;
    SaxHandler handler ( this );
    reader.setContentHandler ( &handler );
    reader.setErrorHandler ( &handler );
    reader.parse ( inputSource );
}

void Instance::preTraitement()
{
//     afficheInstance();
//     exit ( EXIT_SUCCESS );

    cout<<"Avant traitement:"<<endl;
    cout<<"Nb groupes:\t"<<_groupes.size() <<endl;
    cout<<"Nb entites:\t"<<_entites.size() <<endl;
    cout<<"Nb variables:\t"<<_genes.size() <<endl;

    bool supression;
    do
    {
        supression=false;
        set<Gene*> geneASupprimer;
        set<Entite*> entiteASupprimer;
        //1.Colonne dont toutes les valeurs sont identiques (tout a 1 ou tout a 0)
        for ( vector<Gene*>::iterator it=_genes.begin(); it!=_genes.end(); it++ )
        {
            if ( ( *it )->nbOne() ==0 || ( *it )->nbOne() == _entites.size() )
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

    //Calcul de _borneMin
    _borneMin=ceil ( log2 ( _groupes.size() ) );
    cout<<endl;
    cout<<"Après traitement:"<<endl;
    cout<<"Nb groupes:\t"<<_groupes.size() <<endl;
    cout<<"Nb entites:\t"<<_entites.size() <<endl;
    cout<<"Nb variables:\t"<<_genes.size() <<endl<<endl;
		
    cout<<"Borne minimum;\t"<<_borneMin<<endl<<endl;
}

bool trieGroupeParTau ( Groupe const * const g1,Groupe const * const g2 )
{
    return g1->_moyenneTauxDeSimilariteLocal>g2->_moyenneTauxDeSimilariteLocal;
}

bool trieGroupeParRatio ( Groupe const * const g1,Groupe const * const g2 )
{
    return g1->_ratio>g2->_ratio;
}

void Instance::heuristiqueDesMasques()
{
    //Calcul des masques de groupes
    calculMasqueDesGroupesEtMajImage();
    cout<<endl<<"Image brute"<<endl;
    afficheImage();

    trieSurLesGenesDApresLeursTauxDeSimilarite();

    calculMasqueDesGroupesEtMajImage();
    cout<<endl<<"Image triée par TAU"<<endl;
    afficheImage();


    //Heuristique sur les taux de similarite locale (petit tau)
    //Parcours exhaustif des groupe
    for ( vector<Groupe*>::const_iterator itRef=_groupes.begin(); itRef!=_groupes.end(); itRef++ )
    {
        //Initialisation _moyenneTauxDeSimilariteLocal
        ( *itRef )->_moyenneTauxDeSimilariteLocal=0;
        for ( vector<Groupe*>::const_iterator itComp=_groupes.begin(); itComp!=_groupes.end(); itComp++ )
        {
            if ( *itRef==*itComp ) continue;
            //Calcul du tauxDeSimilariteLocal entre *itRef et *itComp
            float moyTemp=0;
            for ( unsigned int i =0; i<_genes.size(); i++ )
                moyTemp+= ( ( *itRef )->_masque[i]+ ( *itComp )->_masque[i] ) /2;
            moyTemp/=_genes.size();

            ( *itRef )->_moyenneTauxDeSimilariteLocal+=moyTemp;
        }
        ( *itRef )->_moyenneTauxDeSimilariteLocal/=_groupes.size()-1;
    }

    //Trie des groupes par petit tau
    sort ( _groupes.begin(),_groupes.end(),trieGroupeParTau );
    //FIN (petit tau)

//     //AFFICHAGE
//     for ( vector<Groupe*>::const_iterator itRef=_groupes.begin(); itRef!=_groupes.end(); itRef++ )
//         cout<< ( *itRef )->_moyenneTauxDeSimilariteLocal<<endl;

// 		//Heuristique de trie par ratio de masques
// 		sort(_groupes.begin(),_groupes.end(),trieGroupeParRatio);
// 		//Fin Heuristique de trie par ratio de masques

    calculMasqueDesGroupesEtMajImage();
    cout<<endl<<"Image triée par TAU et tau"<<endl;
    afficheImage();


    //Moyenne des taux de similarite:NOTE: peut servir de coef pour determiner une instance difficile
    float moy=0;
    for ( vector<float>::const_iterator it=_tauxDeSimilariteGlobale.begin(); it!=_tauxDeSimilariteGlobale.end(); it++ )
        moy+=*it;
    moy=moy/_tauxDeSimilariteGlobale.size();

    cout<<endl<<"Coeficient de difficulté rho de l'instance: "<<moy<<endl;

    //Moyenne des ratio:NOTE: peut servir de coef pour determiner une instance difficile
    moy=0;
    for ( vector<Groupe*>::const_iterator it=_groupes.begin(); it!=_groupes.end(); it++ )
        moy+= ( *it )->_ratio;
    moy=moy/_groupes.size();
    cout<<endl<<"Coeficient de difficulté sigma de l'instance: "<<moy<<endl;

    //MAJ attribut _tabous dans chaque groupe
    majListeTabousDansLesGroupes();
}


Groupe* Instance::getGroupById ( unsigned int id ) const
{
    for ( vector<Groupe*>::const_reverse_iterator rit=_groupes.rbegin(); rit!=_groupes.rend(); rit++ )
        if ( ( *rit )->_id==id )
            return *rit;
    return 0; //Le groupe n'a pas encore été créé
}

void Instance::reInitialiseEntites() const
{
    for ( vector<Entite*>::const_iterator it=_entites.begin(); it!=_entites.end(); it++ )
    {
        ( *it )->_poid=0;
        ( *it )->_ref=false;
    }
}

void Instance::trieDesEntitesParPoidCritique() const
{
// 	for (vector<Entite*>::const_iterator it=_entites.begin();it!=_entites.end();it++) cout<<(*it)->_poid<<" ";
// 	cout<<endl<<endl;

    sort ( ( const_cast<Instance*> ( this ) )->_entites.begin(), ( const_cast<Instance*> ( this ) )->_entites.end(),comparaisonSurPointeurEntite );

// 	for (vector<Entite*>::const_iterator it=_entites.begin();it!=_entites.end();it++) cout<<(*it)->_poid<<" ";
// 	cout<<endl;
}


void Instance::calculMasqueDesGroupesEtMajImage()
{
    //Initialisation de _image
    _image.resize ( _groupes.size() );
    for ( vector<vector<float> >::iterator it=_image.begin(); it!=_image.end(); it++ )
        it->resize ( _genes.size() );
    //Fin Initialisation

    int i=0;
    for ( vector<Groupe*>::const_iterator it=_groupes.begin(); it!=_groupes.end(); it++ ,i++ )
    {
        ( *it )->calculMasque();
        //MAJ _empreinte
        _image[i]= ( *it )->_masque;
    }

    //Calcul de _tauxDeSimilariteGlobale
    _tauxDeSimilariteGlobale.clear();
    _tauxDeSimilariteGlobale.resize ( _genes.size(),0 );
    for ( vector<vector<float> >::const_iterator l=_image.begin(); l!=_image.end(); l++ )
    {
        int ind=0;
        for ( vector<float>::const_iterator c=l->begin(); c!=l->end(); c++ , ind++ )
            _tauxDeSimilariteGlobale[ind]+=*c;
    }
    //Moyenne (calcul du taux intermediaire entre 0 et 0.5 et 0.5 et 1)
    for ( vector<float>::iterator it=_tauxDeSimilariteGlobale.begin(); it!=_tauxDeSimilariteGlobale.end(); it++ )
        *it=*it/_groupes.size();

    //Transformation (calcul du taux véritable entre 0 et 1)
    for ( vector<float>::iterator it=_tauxDeSimilariteGlobale.begin(); it!=_tauxDeSimilariteGlobale.end(); it++ )
        if ( *it<0.5 ) *it= ( 0.5-*it ) *2;
        else *it= ( 0.5- ( 1-*it ) ) *2;
}

void Instance::afficheImage() const
{
//     for ( vector<Groupe*>::const_iterator it=_groupes.begin(); it!=_groupes.end(); it++ )
//     {
//         ( *it )->afficheMasque();
// //         cout<<endl;
//     }

    for ( vector<vector<float> >::const_iterator it=_image.begin(); it!=_image.end(); it++ )
    {
        for ( vector<float>::const_iterator it2=it->begin(); it2!=it->end(); it2++ )
            if ( *it2 == 1 || *it2 == 0 ) cout<<*it2<<" ";
            else cout<<"  ";
        cout<<endl;
    }

//     //Affichage taux de similarite globale
//     for ( vector<float>::const_iterator it=_tauxDeSimilariteGlobale.begin(); it!=_tauxDeSimilariteGlobale.end(); it++ )
//         cout<<*it<<endl;
//     cout<<endl;
}

//Fonction locale pour trieSurLesGenesDApresLeursTauxDeSimilarite
bool comp ( const pair<float,unsigned int> &p1,const pair<float,unsigned int> &p2 )
{
    return p1.first<p2.first;
}
//Fin fonction locale trieSurLesGenesDApresLeursTauxDeSimilarite

void Instance::trieSurLesGenesDApresLeursTauxDeSimilarite()
{
    vector<pair<float,unsigned int>> temp;
    temp.resize ( _tauxDeSimilariteGlobale.size() );

    for ( unsigned int i=0; i<_tauxDeSimilariteGlobale.size(); i++ )
        temp[i]=make_pair ( _tauxDeSimilariteGlobale[i],i );

    sort ( temp.begin(),temp.end(),comp );

// 		//Affichage
// 		for (unsigned int i=0;i<temp.size();i++)
// 			cout<<temp[i].first<<"\t\t"<<temp[i].second<<endl;

    //trie des gènes pour chaque entite
    for ( vector<Entite*>::const_iterator it=_entites.begin(); it!=_entites.end(); it++ )
    {
        vector<pair<Gene*,bool> > genesTemp;
        genesTemp.resize ( _genes.size() );
        for ( unsigned int i=0; i<temp.size(); i++ )
            genesTemp[i]= ( *it )->_genes[temp[i].second];

        ( *it )->_genes=genesTemp;
    }
}

void Instance::majListeTabousDansLesGroupes() const
{
    for ( vector<Groupe*>::const_iterator itGroupeRef=_groupes.begin(); itGroupeRef!=_groupes.end(); itGroupeRef++ )
    {
        for ( vector<Groupe*>::const_iterator itGroupeComp=itGroupeRef+1; itGroupeComp!=_groupes.end(); itGroupeComp++ )
        {
            set<int> indiceTabou;
            for ( unsigned int indice=0; indice< ( *itGroupeRef )->_masque.size(); indice++ )
            {
                if
                (
                    ( ( *itGroupeRef )->_masque[indice]==0 || ( *itGroupeRef )->_masque[indice]==1 )
                    && ( ( *itGroupeComp )->_masque[indice]==0 || ( *itGroupeComp )->_masque[indice]==1 )
                    && ( ( *itGroupeRef )->_masque[indice]!= ( *itGroupeComp )->_masque[indice] )
                )
                    indiceTabou.insert ( indice );
            }
            if ( indiceTabou.size() )
                ( *itGroupeRef )->_tabous[*itGroupeComp]=indiceTabou;
        }
    }
}


bool Instance::certificat ( const vector< int >& solutions ) const
{
    return true;
}

void Instance::afficheInstance() const
{
    for ( vector<Entite*>::const_iterator it=_entites.begin(); it!=_entites.end(); it++ )
        cout<<**it;

}

























