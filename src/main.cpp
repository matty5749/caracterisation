#include "standard.h"

#include "instance.h"
#include "groupe.h"
#include "entite.h"
#include "gene.h"
#include "solveur.h"
#include "rechercheapproche.h"

using namespace std;


int main ( int argc,char** argv )
{
    if ( argc<2 )
    {
        cout<<"Nombre d'arguments incorrect"<<endl;
        exit ( EXIT_FAILURE );
    }

    srand ( time ( NULL ) );
		
		
    Instance instance;
    instance.parseDac ( argv[1] );
    instance.preTraitement();
		
// 		Solveur solveur ( &instance );
// 		solveur.parcoursSansHeuristique();
// 
// 		solveur.rechercheExacteEnProfondeurAPartirde ( instance._genes.size()-1,false );
// // 		solveur.rechercheExacteEnProfondeurAPartirde(18,false);
// // 		solveur.rechercheExacteEnLargeurAPartirde(instance._borneMin);
		
		
		RechercheApproche aleaSearch( &instance );
		aleaSearch.rechercheLocaleAleatoire(instance._genes.size()-1,10000);
    



//     int temp;
//     std::cin>>temp;
    return 0;
}














































