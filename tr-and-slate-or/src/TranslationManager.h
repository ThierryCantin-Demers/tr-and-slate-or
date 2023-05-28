#pragma once

#include <string>
#include <unordered_map>

#include "FileManager.h"

#define TR(str) translation::TranslationManager::getInstance().getTranslation(str)

namespace translation
{
    class TranslationManager
    {
    public:
        static TranslationManager& getInstance();

        const std::string& getTranslation( const std::string& toTranslate_ ) const;
        void getTranslationsFromFile( std::ifstream& fileStream_ );

        void setLanguage( const std::string& language_ );
        const std::string& getCurrentLanguage() const { return m_language; }
        const std::string& getBasePath() const { return m_basePath; }
        void setBasePath( const std::string& basePath_ ) { m_basePath = basePath_; }

    private:
        TranslationManager();

        std::unordered_map< std::string, std::unordered_map< std::string, std::string > > m_translations;
        std::string m_language;
        std::vector< std::string > m_loadedLanguages;
        std::string m_basePath;
    };
}
