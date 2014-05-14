#ifndef SAXHANDLER_H
#define SAXHANDLER_H

#include "standard.h"
#include <QXmlDefaultHandler>

class Instance;

class SaxHandler : public QXmlDefaultHandler
{
private:
    static unsigned int _static_numEntite;
    Instance* _instance;

    std::string _idEntiteTemp;
    std::string _idGroupeRefEntiteTemp;
    std::string _nomEntiteTemp;
    std::string _chaineDeBitEntiteTemp;
    int _nbGroupes;
    int _nbGenes;
    int _nbEntites;


public:
    SaxHandler ( Instance* instance );

    bool startElement ( const QString &namespaceURI,
                        const QString &localName,
                        const QString &qName,
                        const QXmlAttributes &attributes );
    bool endElement ( const QString &namespaceURI,
                      const QString &localName,
                      const QString &qName );
    bool characters ( const QString &str );
    bool fatalError ( const QXmlParseException &exception );
};

#endif
