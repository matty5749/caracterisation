#include "standard.h"
#include "comb.h"
#include "instance.h"
#include "groupe.h"
#include "entite.h"
#include "gene.h"

using namespace std;

void afficheVecteur ( vector<int> vecteur )
{
    for ( unsigned int i=0; i<vecteur.size(); i++ )
    {
        cout<<vecteur[i]<<" ";
    }
    cout<<endl;
}



int main ( int argc,char** argv )
{
    if ( argc<2 )
    {
        cout<<"Nombre d'arguments incorrect"<<endl;
        exit ( EXIT_FAILURE );
    }

    Instance* instance=new Instance();
    instance->parseDac ( argv[1] );
    instance->preTraitement();

    sleep ( 5 );

    int nbGenes=instance->_genes.size();
    int n=nbGenes;
    int k=nbGenes-1;



    //On part de kMax vers kMin
    do
    {
        vector<int> enumeration ( n );
        for ( int i=0; i<n; i++ )
            enumeration[i]=i;
        //Génération et parcours des combinaisons de taille k
        std::size_t comb_size = k;
        cout<<endl<<"\t\t****** Parcours des combinaisons de taille "<< k <<" ******"<<endl;
        do
        {
            //Combinaison à traiter
            vector<int> indices ( k );
            int i=0;
            for ( std::vector<int>::iterator it=enumeration.begin(); it!=enumeration.begin() +comb_size; it++ )
            {
                indices[i++]=*it;
// 								cout<<*it<<" ";
            } //Fin for
//             cout<<endl;

            bool identique;//Vrai si deux entités sont identiques,faux sinon
//             bool chgmtCombinaisons=false;//Vrai si l'on doit changer de combaisons
            //Parcours des groupes
            for ( unsigned int idGroupe=0; idGroupe<instance->_groupes.size(); idGroupe++ )
            {
//                 cout<<"Parcours du groupe "<<idGroupe<<" sur "<< instance->_vGroupes.size() <<endl;
                //Parcours des entités du groupes
                for ( unsigned int entite=0; entite<instance->_groupes[idGroupe]->_entites.size(); entite++ )
                {
                    Entite* pEntite=instance->_groupes[idGroupe]->_entites[entite];
                    //Nouveau parcours des groupes
                    for ( unsigned int idGroupe2=idGroupe+1; idGroupe2<instance->_groupes.size(); idGroupe2++ )
                    {
// 											cout<<"\tParcours du groupe "<<idGroupe2<<endl;
                        //Nouveau parcours des entite
                        for ( unsigned int entite2=0; entite2<instance->_groupes[idGroupe2]->_entites.size(); entite2++ )
                        {
                            Entite* pEntite2=instance->_groupes[idGroupe2]->_entites[entite2];
                            //Les k-uplets doivent être différents 2 à 2
                            //Parcours des indices
                            unsigned int indice;
                            bool tempIdentique;
                            identique=true;
// 														cout<<"DEBUT"<<endl;
                            for ( indice=0; indice<indices.size(); indice++ )
                            {
// 															cout<<*pEntite<<endl;
// 															cout<<*pEntite2<<endl;
// 															pEntite->affichage(cout);
// 															pEntite2->affichage(cout);
// 															cout<<endl;
// 															cout<<pEntite->_vVariables[indice]<<" <--> "<<pEntite2->_vVariables[indice];
                                assert ( ( pEntite->_genes[indices[indice]].first )->_id == ( pEntite2->_genes[indices[indice]].first )->_id );
                                tempIdentique=pEntite->_genes[indices[indice]].second==pEntite2->_genes[indices[indice]].second;
                                if ( !tempIdentique )
                                {
// 																	cout<<" <-- NON IDENTIQUE"<<endl;
                                    identique=false;
                                    break;
                                }
                            }//Fin parcours indices
                            //Si deux entites identique, changement de combinaisons
                            if ( identique )
                            {
// 															cout<<indice<<endl;
//                                 pEntite->affichage ( cout );
// 															pEntite2->affichage(cout);
// 															cout<<endl;
                                break;
                            }
                        }//Fin parcours entite2
                        if ( identique ) break;
                    }//Fin parcours idGroupe2
                    if ( identique ) break;
                }//Fin parcours entite
                if ( identique ) break;
            }//Fin parcours idGroupe
            if ( ! identique )
            {
                cout<<"Cette combinaison de taille "<< k <<" permet de caractériser l'instance"<<endl;
                afficheVecteur ( indices );
                break;//On passe à k-1
            }
        }
        while ( next_combination ( enumeration.begin(),enumeration.begin() + comb_size,enumeration.end() ) );
    }
    while ( --k>0 );

		delete instance;
    int temp;
    cin>>temp;
    return 0;
}













































