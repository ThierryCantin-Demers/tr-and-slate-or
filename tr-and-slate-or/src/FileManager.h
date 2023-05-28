#pragma once
#include <string>
#include <fstream>
#include <optional>
#include <filesystem>
#include <vector>

#define WORKING_DIR translation::FileManager::getCurrentWorkingDirectory()

namespace translation
{
    class FileManager
    {
    public:
        static std::optional< std::ifstream > getFileStream( const std::string& filePath_ );
        static std::string getCurrentWorkingDirectory();
        static std::vector< std::string > listFilesInDirectory( const std::string& directoryPath_ );
    };
}
