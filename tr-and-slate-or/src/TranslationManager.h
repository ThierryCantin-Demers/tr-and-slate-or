#pragma once

#include <string>
#include <unordered_map>

#include "FileManager.h"

#define TR(str) translation::TranslationManager::GetInstance().GetTranslation(str)

namespace translation
{
    class TranslationManager
    {
    public:
        static TranslationManager& GetInstance();
        

        [[nodiscard]] const std::string& GetTranslation( const std::string& toTranslate_ ) const;

        void SetLanguage( const std::string& language_ );

        [[nodiscard]] const std::string& GetCurrentLanguage() const { return m_currentLanguage; }
        [[nodiscard]] const std::string& GetBasePath() const { return m_basePath; }
        void SetBasePath( const std::string& basePath_ ) { m_basePath = basePath_; }

    private:
        TranslationManager();

        void LoadValidLanguageCodesFromJsonFile( std::ifstream& languageCodesFileStream_ );
        void GetTranslationsFromJsonFile( std::ifstream& fileStream_ );
        [[nodiscard]] std::optional< std::string > IsLanguageValid( std::string targetLanguage_ ) const;
    private:
        std::unordered_map< std::string, std::unordered_map< std::string, std::string > > m_loadedTranslations;
        std::unordered_map< std::string, std::string > m_validLanguageCodes;
        std::vector< std::string > m_loadedLanguages;

        std::string m_basePath;

        // The current language is the language code of the current language.
        std::string m_currentLanguage;
    };
}
