#ifndef ENTITE_H
#define ENTITE_H

#include "standard.h"
#include "instance.h"
#include "gene.h"

class Entite
{
public:
    //ATTRIBUTS
    static Instance* _static_instance;
    unsigned int _id;
    unsigned int _idGroupe;
    std::string _idString;
    std::string _nom;
    std::string _groupeRef;

    std::vector<std::pair<Gene*,bool> > _genes; /*<Indique la présence/absence des genes*/

    std::map<Entite*, int> _poidsCritique;/*!<Poid >= k-1 avec chaque entite comparé*/
    std::map<Entite*, int> _poidsNonCritique;/*!<Poid < k-1 avec chaque entite comparé*/

    std::set<Entite*> _entitesCritique;/*!<Poid = k-1 avec chaque entite comparé*/

    unsigned int _poid;/*<! poid de l'entite lors de la caractérisation courante
		dans Algo::estCaracterisePar_version2 ,valeur reinitialiser à 0
		à chaque nouveau parcours par la méthode Instance::reInitialisationEntites();*/

    bool _ref;/*<!Vrai si l'entite a déjà été utilisé comme réference
		lors de la caractérisation courante dans Algo::estCaracterisePar_version2,
		valeur reinitialiser à false à chaque nouveau parcours par la méthode
		Instance::reInitialisationEntites();*/

    //METHODES
    Entite ( unsigned int id,unsigned int idGroupe,std::string chaine_de_bits, Instance* instance ,std::string idString="",std::string nom="",std::string groupeRef="" );

    /*!\brief Sort l'élément de _poidsCritique pour le mettre dans _poidsNonCritique
     * \warning Ne pas utiliser dans une boucle itérant sur la map _poidsCritique (utilisation de erase)
     */
    void basculerVersPoidsNonCritique ( Entite* const &elmt, const int &poid );

    /*!\brief Sort l'élément de _poidsNonCritique pour le mettre dans _poidsCritique
     * \warning Ne pas utiliser dans une boucle itérant sur la map _poidsNonCritique (utilisation de erase)
     */
    void basculerVersPoidsCritique ( Entite* const &elmt, const int &poid );

    void affichage ( std::ostream &os ) const;
};

std::ostream& operator<< ( std::ostream& os,Entite const & e );

bool operator< ( const Entite &e1, const Entite &e2 );
bool comparaisonSurPointeurEntite ( const Entite * const e1, const Entite * const e2 );

/*!
 * \brief Deux entités différentes sont similaire si ils sont composées des même gênes
 * \warning Cette fonction ne doit servir que pour le pré traitement
 */
bool estSimilaire ( Entite const * const e1,Entite const * const e2 );

struct memeEntite : std::binary_function<std::pair<Entite*,bool>, Entite, bool>
{
    bool operator() ( const std::pair<Entite*,bool> &pair, const Entite & entite ) const
    {
        return ( ( pair.first )->_id == entite._id );
    }
};

#endif // ENTITE_H,,,,,

