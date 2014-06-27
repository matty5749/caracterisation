#include "standard.h"

#include "instance.h"
#include "groupe.h"
#include "entite.h"
#include "gene.h"
#include "solveur.h"
#include "rechercheapproche.h"
#include "combinaison.h"

using namespace std;

int main ( int argc,char** argv )
{

    

    if ( argc<2 )
    {
        cout<<"Nombre d'arguments incorrect"<<endl;
        exit ( EXIT_FAILURE );
    }

		
    string data(argv[1]);
		string extension=data.substr(data.find_last_of(".")+1);
		bool xml=extension=="xml";
		
    srand ( time ( NULL ) );
    Instance instance;
		
		if (xml) instance.parseXml ( argv[1] );
		else instance.parseDac ( argv[1] );
    
		instance.preTraitement();
		
		
    instance.heuristiqueDesMasques();

		// sleep(5);

// 		RechercheApproche roulette( &instance );
// 		roulette.roulette();
//		roulette.rouletteAdaptative(0.02);
		
		Solveur solveur ( &instance );
    solveur.parcoursStandard();
// 
    solveur.rechercheExacteEnProfondeurAPartirde_heuristique4 ( instance._genes.size()-1,false );
// 					solveur.rechercheExacteEnProfondeurAPartirde_heuristique3 ( instance._genes.size()-1,false );
// 		solveur.rechercheExacteEnProfondeurAPartirde ( instance._genes.size()-1,false );


    // 			solveur.rechercheExacteEnProfondeurAPartirde_heuristique2 ( instance._genes.size()-1,false );
// 			solveur.rechercheExacteEnProfondeurAPartirde_heuristique1 ( instance._genes.size()-1,false );
// 							solveur.rechercheExacteEnProfondeurAPartirde(18,false);
// 		solveur.rechercheExacteEnLargeurAPartirde(instance._borneMin);


// 		RechercheApproche aleaSearch( &instance );
// 		aleaSearch.rechercheLocaleAleatoire(instance._genes.size()-1,1000000);




//     int temp;
//     std::cin>>temp;
    return 0;
}





// 	multimap<int,string> mmTest;
// 	mmTest.emplace(3,"trois");
// 	mmTest.emplace(3,"three");
// 	mmTest.emplace(3,"drei");
// 	mmTest.emplace(1,"un");
// 	mmTest.emplace(1,"one");
// 	mmTest.emplace(1,"ein");
// 	mmTest.emplace(2,"deux");
// 	mmTest.emplace(2,"zwei");
// 	mmTest.emplace(2,"two");
//
//
// 	for(multimap<int,string>::iterator it=--mmTest.upper_bound(2-1);it!=--mmTest.begin();it--)
// 	{
// 		cout<<it->first<<" --> "<<it->second<<endl;
// 		if (it->second == "one") mmTest.erase(it);
// 	}
//
// 	cout<<endl<<endl;
// 	for(multimap<int,string>::iterator it=mmTest.begin();it!=mmTest.end();it++)
// 	{
// 		cout<<it->first<<" --> "<<it->second<<endl;
// 	}








































