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
		std::vector<std::pair<Gene*,bool> > _genes; /*<Indique la présence/absence des genes*/

    //METHODES
    Entite ( unsigned int id,unsigned int idGroupe,std::string chaine_de_bits, Instance* instance );

    void affichage ( std::ostream &os ) const;
};

std::ostream& operator<< ( std::ostream& os,Entite const & e );

/*!
 * \brief Deux entités différentes sont similaire si ils sont composées des même gênes
 * \warning Cette fonction ne doit servir que pour le pré traitement
 */
bool estSimilaire(Entite const * const e1,Entite const * const e2);

struct memeEntite : std::binary_function<std::pair<Entite*,bool>, Entite, bool>
{
    bool operator() ( const std::pair<Entite*,bool> &pair, const Entite & entite ) const
    {
        return ( ( pair.first )->_id == entite._id );
    }
};

#endif // ENTITE_H,,,,,

