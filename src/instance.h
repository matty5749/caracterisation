#ifndef INSTANCE_H
#define INSTANCE_H

#include "standard.h"
#include "saxhandler.h"

class Groupe;
class Entite;
class Gene;

class Instance
{
public:
    //ATTRIBUTS
		std::string _nom;
    std::vector<Groupe*> _groupes;
    std::vector<Entite*> _entites;
    std::vector<Gene*> _genes;
    unsigned int _borneMin;/*!<Partie entiere de log à base 2 de _groupes.size()*/
		std::vector<std::vector<float> > _image; /*!<Tableau des masques de groupe*/
		std::vector<float> _tauxDeSimilariteGlobale; /*!<Taux de similarité entre 0 et 1 pour chaque colonne de _image*/



    //METHODES
    Instance(std::string nom="");
    ~Instance();

		///!\brief Permet d'initialiser l'instance à partir d'un fichier .dac
    void parseDac ( char* nomFic );

    ///!\brief Permet d'initialiser l'instance à partir d'un fichier .xml
    void parseXml ( char* nomFic );
		
    /*!
    * \brief Permet de supprimer les redondances afin de réduire la taille de l'instance
    */
    void preTraitement();
		
		void heuristiqueDesMasques ();

    /*!
     * \warning La valeur de retour peut-être 0
     * \return Le pointeur vers le groupe d'identifiant id si celui existe, 0 sinon
     */
    Groupe* getGroupById ( unsigned int id ) const;

    ///!\brief Remets tout les poids des entités à 0
    void reInitialiseEntites() const;

    void trieDesEntitesParPoidCritique() const;

    /*!
     * \brief Verifie l'exactitude d'une solution
     */
    bool certificat ( const std::vector<int> &solutions ) const;

		///!\brief calcul les masques de chaque groupe qui permettent de définir l'_image et de calculer le _tauxDeSimilariteGlobale
    void calculMasqueDesGroupesEtMajImage() ;

		void trieSurLesGenesDApresLeursTauxDeSimilarite();
		
		void majListeTabousDansLesGroupes () const;
		
    void afficheImage() const;
		
		void afficheInstance() const;
};


#endif // INSTANCE_H
