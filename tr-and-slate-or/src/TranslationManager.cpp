#include "TranslationManager.h"
#include "FileManager.h"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <SimpleIni.h>


namespace translation
{
    /**
     * \brief Returns the singleton instance of the translation manager.
     * \return The singleton instance of the translation manager.
     */
    TranslationManager& TranslationManager::GetInstance()
    {
        static TranslationManager instance;

        return instance;
    }

    /**
     * \brief Loads the language codes from the given file path. A language is considered valid if it has an entry in the given json file. The language codes are loaded into a map, where the key is the language name in lowercase, and the value is the language code.
     * \param languageCodesFileStream_ The file path to load the language codes from.
     */
    void TranslationManager::LoadValidLanguageCodesFromJsonFile( std::ifstream& languageCodesFileStream_ )
    {
        nlohmann::json json;
        languageCodesFileStream_ >> json;

        for ( auto& language : json.items() )
        {
            std::string languageName = language.key();

            std::ranges::transform( languageName.begin(), languageName.end(), languageName.begin(),
                                    []( const char& c )
                                    {
                                        return std::tolower( c );
                                    } );

            m_validLanguageCodes[ languageName ] = language.value();
        }

        languageCodesFileStream_.close();
    }

    /**
     * \brief Returns the translation for the given string in the currently selected app language.
     * \param toTranslate_ The string to translate.
     * \return The translated string.
     */
    const std::string& TranslationManager::GetTranslation( const std::string& toTranslate_ ) const
    {
        const auto string_iterator = m_loadedTranslations.find( toTranslate_ );

        // If the string is not found, return the string as is.
        if ( string_iterator != m_loadedTranslations.end() )
        {
            const auto language_iterator = string_iterator->second.find( m_currentLanguage );

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
    void TranslationManager::GetTranslationsFromJsonFile( std::ifstream& fileStream_ )
    {
        nlohmann::json json;
        fileStream_ >> json;

        for ( const auto& translation : json.items() )
        {
            m_loadedTranslations[ translation.key() ][ m_currentLanguage ] = translation.value();
        }

        fileStream_.close();
    }

    /**
     * \brief Changes the language of the translation manager, and loads the language file if it is not already loaded.
     * \param targetLanguage_ the language to change to.
     */
    void TranslationManager::SetLanguage( const std::string& targetLanguage_ )
    {
        const std::optional< std::string > languageCode = IsLanguageValid( targetLanguage_ );

        if ( !languageCode.has_value() )
        {
            return;
        }

        m_currentLanguage = *languageCode;

        // If the language is not loaded, load it.
        if ( std::ranges::find( m_loadedLanguages, m_currentLanguage ) == m_loadedLanguages.end() )
        {
            m_loadedLanguages.push_back( m_currentLanguage );

            std::optional< std::ifstream > fileStream = FileManager::GetFileStream(
                m_basePath + m_currentLanguage + ".json" );

            if ( fileStream.has_value() )
            {
                GetTranslationsFromJsonFile( *fileStream );
            }
        }
    }

    /**
     * \brief Checks if the given language is valid. The language is valid if it is in the list of valid language codes.
     * \param targetLanguage_ the language to check.
     * \return The language code if the language is valid, or nullopt if it is not.
     */
    std::optional< std::string > TranslationManager::IsLanguageValid( std::string targetLanguage_ ) const
    {
        std::ranges::transform( targetLanguage_.begin(), targetLanguage_.end(), targetLanguage_.begin(),
                                []( const char& c_ )
                                {
                                    return std::tolower( c_ );
                                } );

        const auto languageIterator = m_validLanguageCodes.find( targetLanguage_ );

        if ( languageIterator == m_validLanguageCodes.end() )
        {
            // If the language is not found, check if the language code is valid, return it if it is.
            const auto isLanguageCodeValid = [&targetLanguage_]( const auto& it )
            {
                return it.second == targetLanguage_;
            };

            const auto it = std::ranges::find_if( m_validLanguageCodes.begin(), m_validLanguageCodes.end(),
                                                  isLanguageCodeValid );

            if ( it != m_validLanguageCodes.end() )
            {
                return it->second;
            }

            return std::nullopt;
        }

        return languageIterator->second;
    }

    /**
     * \brief Constructs a translation manager with a base path (current working dir\translations\).
     */
    TranslationManager::TranslationManager() : m_basePath( WORKING_DIR + "\\translations\\" )
    {
        if ( std::optional< std::ifstream > fileStream = FileManager::GetFileStream(
            m_basePath + "languages.json" ); fileStream.has_value() )
        {
            LoadValidLanguageCodesFromJsonFile( *fileStream );
            fileStream->close();
        }

        CSimpleIniA ini;
        ini.SetUnicode();
        SI_Error rc = ini.LoadFile( "configs.ini" );

        if ( rc < 0 )
        {
            SetLanguage( "en" );
        }

        SetLanguage( ini.GetValue( "Config", "Language", "en" ) );
    }
}
