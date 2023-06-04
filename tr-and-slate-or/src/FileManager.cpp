#include "FileManager.h"

#include <filesystem>
#include <string>
#include <vector>

namespace translation
{
    /**
     * \brief Opens a file and returns the file stream.
     * \param filePath_ the path to the file to open.
     * \return the file stream if the file exists and is open, otherwise nullopt.
     */
    std::optional< std::ifstream > FileManager::GetFileStream( const std::string& filePath_ )
    {
        if ( !std::filesystem::exists( filePath_ ) )
        {
            return std::nullopt;
        }

        std::ifstream fileStream( filePath_ );

        if ( !fileStream.is_open() || fileStream.fail() )
        {
            return std::nullopt;
        }

        return fileStream;
    }

    /**
     * \brief Returns the current working directory.
     * \return the current working directory.
     */
    std::string FileManager::GetCurrentWorkingDirectory()
    {
        return std::filesystem::current_path().string();
    }

    /**
     * \brief Lists all the files in the given directory.
     * \param directoryPath_ the path to the directory to list the files from.
     * \return a vector containing the paths to all the files in the given directory.
     */
    std::vector< std::string > FileManager::ListFilesInDirectory( const std::string& directoryPath_ )
    {
        std::vector< std::string > files;

        for ( const auto& entry : std::filesystem::directory_iterator( directoryPath_ ) )
        {
            files.push_back( entry.path().string() );
        }

        return files;
    }
}
