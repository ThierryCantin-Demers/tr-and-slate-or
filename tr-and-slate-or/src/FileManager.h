#pragma once
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
    };
}
