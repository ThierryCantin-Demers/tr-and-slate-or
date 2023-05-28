#pragma once

#include <string>
#include <unordered_map>

#define TR(str) CTranslationManager::getInstance().getTranslation(str)

namespace util
{
    class CTranslationManager
    {
    public:
        static CTranslationManager& getInstance();

        const std::string& getTranslation( const std::string& toTranslate_ ) const;

        void getTranslationsFromFile( std::ifstream& fileStream_ );

        void setLanguage( const std::string& language_ );
        const std::string& getCurrentLanguage() const { return m_language; }

    private:
        std::unordered_map< std::string, std::unordered_map< std::string, std::string > > m_translations;
        std::string m_language;
        std::vector< std::string > m_loadedLanguages;
    };
}
