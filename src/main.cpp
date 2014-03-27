#include "standard.h"

#include "instance.h"
#include "groupe.h"
#include "entite.h"
#include "gene.h"

using namespace std;

int main ( int argc,char** argv )
{
    if ( argc<2 )
    {
        cout<<"Nombre d'arguments incorrect"<<endl;
        exit ( EXIT_FAILURE );
    }

    Instance instance;
		
// 		instance.test();
		
    instance.parseDac ( argv[1] );
    instance.preTraitement();
		instance.parcoursSansHeuristique();
		instance.rechercheExacteEnProfondeurAPartirde(instance._genes.size()-1,false);
// 		instance.rechercheExacteEnProfondeurAPartirde(40,true);
// instance.rechercheExacteEnLargeurAPartirde(2);


    

    int temp;
    std::cin>>temp;
    return 0;
}














































