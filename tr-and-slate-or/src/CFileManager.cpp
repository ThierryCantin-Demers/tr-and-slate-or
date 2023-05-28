#include "CFileManager.h"

#include <filesystem>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

namespace util
{
    std::optional< std::ifstream > CFileManager::getFileStream( const std::string& filePath_ )
    {
        try
        {
            std::ifstream fileStream( filePath_ );
            return fileStream;
        }
        catch ( std::ifstream::failure e )
        {
            return std::nullopt;
        }
    }

    std::string CFileManager::getCurrentWorkingDirectory()
    {
        return std::filesystem::current_path().string();
    }


    std::vector< std::string > CFileManager::listFilesInDirectory( const std::string& directoryPath_ )
    {
        std::vector< std::string > files;

        for ( const auto& entry : std::filesystem::directory_iterator( directoryPath_ ) )
        {
            files.push_back( entry.path().string() );
        }

        return files;
    }
}
