#include <QtXml>
#include "saxhandler.h"
#include "instance.h"
#include "groupe.h"


using namespace std;

unsigned int SaxHandler::_static_numEntite=1;

SaxHandler::SaxHandler ( Instance* instance )
    :_instance ( instance ),_idEntiteTemp ( "" ),_idGroupeRefEntiteTemp ( "" ),_nomEntiteTemp ( "" ),_chaineDeBitEntiteTemp ( "" ),_nbGroupes ( 0 ),_nbGenes ( 0 ),_nbEntites ( 0 )
{

}

bool SaxHandler::startElement ( const QString & /* namespaceURI */,
                                const QString & /* localName */,
                                const QString &qName,
                                const QXmlAttributes &attributes )
{
    if ( qName == "instance" )
    {
        _instance->_nom=attributes.value ( 0 ).toStdString();
        _nbGroupes=toInt ( attributes.value ( 1 ).toStdString() );
        _nbGenes=toInt ( attributes.value ( 2 ).toStdString() );
        _nbEntites=toInt ( attributes.value ( 3 ).toStdString() );

        _instance->_groupes.reserve ( _nbGroupes );
        _instance->_genes.reserve ( _nbGenes );
        _instance->_entites.reserve ( _nbEntites );
    }
    else if ( qName == "groupe" )
    {
        string idGroupe=attributes.value ( 0 ).toStdString();
        idGroupe.erase ( 0 , 1 ); //Supression de la lettre g
        string nom=attributes.value ( 1 ).toStdString();

        Groupe* groupe=new Groupe ( toInt ( idGroupe ), _instance , nom );
        _instance->_groupes.push_back ( groupe );
    }
    else if ( qName == "attribut" )
    {
        string idGene=attributes.value ( 0 ).toStdString();
        idGene.erase ( 0 , 1 ); //Supression de la lettre a
        string nom=attributes.value ( 1 ).toStdString();

        Gene* gene=new Gene ( toInt ( idGene ), _nbEntites , _instance , nom );
        _instance->_genes.push_back ( gene );
    }
    else if ( qName == "entite" )
    {
        _idEntiteTemp=attributes.value ( 0 ).toStdString();
        _idGroupeRefEntiteTemp=attributes.value ( 1 ).toStdString();
        _idGroupeRefEntiteTemp.erase ( 0 , 1 ); //Suppression de g
        _nomEntiteTemp=attributes.value ( 2 ).toStdString();
    }
    else if ( qName == "valuationsPositives" )
    {
        _chaineDeBitEntiteTemp.clear();
        _chaineDeBitEntiteTemp.resize ( _instance->_genes.size(),'0' );
        string positifs=attributes.value ( 0 ).toStdString();

        set<int> setPositifs;
        istringstream iss ( positifs );
        string idStringGene="";
				while ( std::getline ( iss, idStringGene, 'a' ) )
        {
            if ( !idStringGene.empty() )
                setPositifs.insert ( toInt ( idStringGene ) );
        }

        for ( set<int>::const_iterator it=setPositifs.begin(); it!=setPositifs.end(); it++ )
        {
            _chaineDeBitEntiteTemp[ ( *it )-1]='1';
        }
    }
    return true;
}

bool SaxHandler::characters ( const QString &str )
{
    return true;
}

bool SaxHandler::endElement ( const QString & /* namespaceURI */,
                              const QString & /* localName */,
                              const QString &qName )
{
    if ( qName == "entite" )
    {
        Entite* entite=new Entite ( _static_numEntite++,toInt ( _idGroupeRefEntiteTemp ),_chaineDeBitEntiteTemp, _instance , _idEntiteTemp , _nomEntiteTemp , _idGroupeRefEntiteTemp );
        _instance->_entites.push_back ( entite );

        if ( _instance->getGroupById ( toInt ( _idGroupeRefEntiteTemp ) ) ) _instance->getGroupById ( toInt ( _idGroupeRefEntiteTemp ) )->_entites.push_back ( entite );
        else
        {
            cout<<"Cas impossible dans bool SaxHandler::endElement ( const QString & /* namespaceURI */,const QString & /* localName */,const QString &qName )"<<endl;
            exit ( EXIT_FAILURE );
        }
    }
    return true;
}

bool SaxHandler::fatalError ( const QXmlParseException &exception )
{
    std::cout<<"SAX Handler \n Erreur de parsage \n Ligne : "<<exception.lineNumber() << "\nColonne : "<<exception.columnNumber() <<"\nMessage : "<<exception.message().toStdString() <<std::endl;
    exit ( EXIT_FAILURE );
    return false;
}



