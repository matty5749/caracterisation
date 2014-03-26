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

  //METHODES
  Groupe( unsigned int id , Instance* instance);
};

#endif //GROUPE_H
