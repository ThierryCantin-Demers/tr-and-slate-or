#include "TranslationManager.h"
#include "FileManager.h"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>


namespace translation
{
    /**
     * \brief Returns the singleton instance of the translation manager.
     * \return The singleton instance of the translation manager.
     */
    TranslationManager& TranslationManager::getInstance()
    {
        static TranslationManager instance;

        return instance;
    }

    void TranslationManager::loadLanguageCodes( const std::string& languageCodesFilePath_ )
    {
        std::optional< std::ifstream > fileStream = FileManager::getFileStream(
            languageCodesFilePath_ );

        if ( fileStream.has_value() )
        {
            nlohmann::json json;
            *fileStream >> json;

            for ( auto& language : json.items() )
            {
                std::string languageName = language.key();

                std::transform( languageName.begin(), languageName.end(), languageName.begin(),
                                []( const char& c )
                                {
                                    return std::tolower( c );
                                } );

                m_languageCodes[ languageName ] = language.value();
            }
        }
    }

    /**
     * \brief Returns the translation for the given string in the currently selected app language.
     * \param toTranslate_ The string to translate.
     * \return The translated string.
     */
    const std::string& TranslationManager::getTranslation( const std::string& toTranslate_ ) const
    {
        const auto string_iterator = m_translations.find( toTranslate_ );

        // If the string is not found, return the string as is.
        if ( string_iterator != m_translations.end() )
        {
            const auto language_iterator = string_iterator->second.find( m_language );

            // If the language is not found for the language, return the string as is.
            if ( language_iterator != string_iterator->second.end() )
            {
                return language_iterator->second;
            }
        }

        return toTranslate_;
    }

    /**
     * \brief Loads the translations from a file stream.
     * \param fileStream_ The file stream to load the translations from.
     */
    void TranslationManager::getTranslationsFromJSONFile( std::ifstream& fileStream_ )
    {
        nlohmann::json json;
        fileStream_ >> json;

        for ( const auto& translation : json.items() )
        {
            m_translations[ translation.key() ][ m_language ] = translation.value();
        }

        fileStream_.close();
    }

    /**
     * \brief Changes the language of the translation manager, and loads the language file if it is not already loaded.
     * \param language_ the language to change to.
     */
    void TranslationManager::setLanguage( const std::string& language_ )
    {
        std::string language = language_;

        std::ranges::transform( language.begin(), language.end(), language.begin(),
                                []( const char& c )
                                {
                                    return std::tolower( c );
                                } );

        const auto language_iterator = m_languageCodes.find( language );

        if ( language_iterator == m_languageCodes.end() )
        {
            return;
        }

        const std::string& languageCode = language_iterator->second;

        m_language = languageCode;

        if ( std::ranges::find( m_loadedLanguages, languageCode ) == m_loadedLanguages.end() )
        {
            m_loadedLanguages.push_back( languageCode );

            const std::string languageFilePath = m_basePath + languageCode + ".json";

            std::optional< std::ifstream > fileStream = FileManager::getFileStream(
                languageFilePath );

            if ( fileStream.has_value() )
            {
                getTranslationsFromJSONFile( *fileStream );
            }
        }
    }

    /**
     * \brief Constructs a translation manager with a base path.
     */
    TranslationManager::TranslationManager() : m_basePath( WORKING_DIR + "\\translations\\" )
    {
        loadLanguageCodes( m_basePath + "languages.json" );
    }
}
