#ifndef GROUPE_H
#define GROUPE_H

#include "standard.h"
#include "entite.h"
#include "instance.h"

class Groupe
{
public:
  //ATTRIBUTS
	static Instance* _static_instance;
	unsigned int _id;
	std::vector<Entite*> _entites;
	std::vector<float> _masque;
	std::map<Groupe*,std::set<int> > _tabous; /*!< Contient les éléments de combinaisons tabous entre ce 
	groupe et les autres groupes avec qui il doit être comparé*/
	float _ratio; /*!< Correspond au pourcentage de valeur entière présentent dans le masque*/

  //METHODES
  Groupe( unsigned int id , Instance* instance);
	
	void calculMasque();
	
	void afficheMasque() const;
};

#endif //GROUPE_H
