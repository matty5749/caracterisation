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
		
		unsigned int _nbEntites;

    //METHODES
    Instance();
		~Instance();
		
		/*!
     * \brief Permet d'initialiser l'instance à partir d'un fichier .dac
     */
		void parseDac(char* nomFic);

		/*!
     * \brief Permet de supprimer les redondances afin de réduire la taille de l'instance
     */
		void preTraitement();

    /*!
     * \warning La valeur de retour peut-être 0
     * \return Le pointeur vers le groupe d'identifiant id si celui existe, 0 sinon
     */
    Groupe* getGroupById ( unsigned int id ) const;
		
};

#endif // INSTANCE_H
