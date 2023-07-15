#pragma once

#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>
#include <fstream>
#include <optional>
#include <filesystem>
#include <vector>

#define WORKING_DIR translation::FileManager::GetCurrentWorkingDirectory()

namespace translation
{
    class FileManager
    {
    public:
        static std::optional< std::ifstream > GetFileStream( const std::string& filePath_ );
        static std::string GetCurrentWorkingDirectory();
        static std::vector< std::string > ListFilesInDirectory( const std::string& directoryPath_ );

        /*template < typename Class >
        static void UseFileFromPath( Class* object_, void ( Class::*function_ )( std::ifstream& ),
                                     const std::string& filePath_ );*/
    };
}

#endif // FILE_MANAGER_H
