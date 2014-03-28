#include "groupe.h"

Instance* Groupe::_static_instance=0;

Groupe::Groupe ( unsigned int id , Instance* instance) :_id ( id )
{
	if ( ! _static_instance ) _static_instance=instance;
}
