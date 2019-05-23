#pragma once
#include <string>

namespace cz_mg_logger
{
    class Logger
    {
    public:
        static std::string filename;

    public:
        static void log(std::string message);
    };
}
