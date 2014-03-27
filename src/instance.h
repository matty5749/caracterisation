#ifndef INSTANCE_H
#define INSTANCE_H

#include "standard.h"

class Groupe;
class Entite;
class Gene;

class Instance
{
public:
    //ATTRIBUTS
    std::vector<Groupe*> _groupes;
    std::vector<Entite*> _entites;
    std::vector<Gene*> _genes;
		std::vector<int> _parcours;/*!<L'ordre dans lequel sera parcouru l'espace de recherche, initialiser par les méthodes de type parcoursSansHeuristique , parcours.............*/
    

    //METHODES
    Instance();
    ~Instance();

    /*!
    * \brief Permet d'initialiser l'instance à partir d'un fichier .dac
    */
    void parseDac ( char* nomFic );

    /*!
    * \brief Permet de supprimer les redondances afin de réduire la taille de l'instance
    */
    void preTraitement();

    /*!
     * \warning La valeur de retour peut-être 0
     * \return Le pointeur vers le groupe d'identifiant id si celui existe, 0 sinon
     */
    Groupe* getGroupById ( unsigned int id ) const;

    /*!
    * \param k borne supérieur
    * \param allSolution si vrai, cherchera toute les formules de taille k caractérisant l'instance
    */
    void rechercheExacteEnProfondeurAPartirde ( unsigned int k , bool allSolution=false ) const;

    /*!
     * \param k borne inférieur
     * \param allSolution si vrai, cherchera toute les formules de taille k caractérisant l'instance
     */
    void rechercheExacteEnLargeurAPartirde ( unsigned int k , bool allSolution=false ) const;

    /*!
     * \brief Renvoie vrai si l'instance est caractérisable par les gènes présent aux positions d'indices dans _genes
     * \param indices est composé des positions des gènes dont on veut savoir si ils caractérisent l'instance
     */
    bool estCaracterisePar ( const std::vector<int> &indices ) const;
		
		/*!
		 * \brief Instancie le vecteur _parcours d'entier de 1 à _genes.size() dans l'ordre croissant
		 */
		void parcoursSansHeuristique();
		
		void test() const;

};


#endif // INSTANCE_H
