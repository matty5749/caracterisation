template<typename T>
inline void afficheVecteur( const std::vector< T > & vecteur )
{
    for ( unsigned int i=0; i<vecteur.size(); i++ )
    {
        std::cout<<vecteur[i]<<" ";
    }
    std::cout<<std::endl;
}