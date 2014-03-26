#ifndef GENE_H
#define GENE_H

#include "standard.h"
#include "instance.h"




class Gene
{
    //ATTRIBUTS
private:
    int _nbOne;/*<Le nombre d'entite composé de ce gène*/
public:
    static Instance* _static_instance;
    unsigned int _id;
    std::vector<std::pair<Entite*,bool> > _entites;/*!<Présence/absence du gene dans l'entite*/

    //METHODES
    Gene ( unsigned int id , unsigned int nbEntites ,Instance* instance );

    /*!
     * \return Le nombre d'entite composé de ce gène
     */
    unsigned int nbOne();

    void affichage ( std::ostream &os ) const;
};
std::ostream& operator<< ( std::ostream& os, const Gene & g );

/*!
 * \brief Deux gènes différents sont similaire si ils composent les même entités
 * \warning Cette fonction ne doit servir que pour le pré traitement
 */
bool estSimilaire ( const Gene * const g1, const Gene * const g2 );


struct memeGene : std::binary_function<std::pair<Gene*,bool>, Gene, bool>
{
    bool operator() ( const std::pair<Gene*,bool> &pair, const Gene & gene ) const
    {
        return ( ( pair.first )->_id == gene._id );
    }
};




#endif //GENE_H
