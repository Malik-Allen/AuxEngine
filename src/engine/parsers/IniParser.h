// MIT License, Copyright (c) 2024 Malik Allen

#ifndef AUX_INIPARSER_H
#define AUX_INIPARSER_H

#include "engine/parsers/inih/cpp/INIReader.h"

#include <fstream>
#include <iostream>

typedef inih::INIReader ini;

namespace  AuxEngine
{
    class IniParser
    {
    public:
        IniParser(const IniParser&) = delete;
        IniParser& operator=(const IniParser&) = delete;
        IniParser(IniParser&&) = delete;
        IniParser& operator=(IniParser&&) = delete;

        explicit IniParser(const std::string& fileName):
            iniReader(ini(fileName))
        {};

        ~IniParser() {};

        // Load INI data from file.
        bool ParseFromFile(const std::string& fileName)
        {
            std::ifstream file(fileName);
            if (!file.is_open())
            {
                std::cerr << "Unable to open file: " << fileName << '\n';
                return false;
            }

            iniReader = ini(fileName);

            if (iniReader.ParseError() < 0)
            {
                std::cerr << "Unable to read ini file: " << fileName << '\n';
                return false;
            }

            return true;
        }

        std::string GetString(const std::string& section, const std::string& name, const std::string& default_value) const
        {
            return iniReader.GetString(section, name, default_value);
        }

        int GetInteger(const std::string& section, const std::string& name, long default_value) const
        {
            return static_cast<int>(iniReader.GetInteger(section, name, default_value));
        }

        float GetFloat(const std::string& section, const std::string& name, double default_value) const
        {
            return static_cast<float>(iniReader.GetReal(section, name, default_value));
        }

        bool GetBoolean(const std::string& section, const std::string& name, bool default_value) const
        {
            return iniReader.GetBoolean(section, name, default_value);
        }

        std::vector<std::string> Sections() const
        {
            return iniReader.Sections();
        }

        std::vector<std::string> Keys(const std::string& section) const 
        {
            return iniReader.Keys(section);
        }

        bool HasSection(const std::string& section) const
        {
            return iniReader.HasSection(section);
        }

        bool HasValue(const std::string& section, const std::string& name) const
        {
            return iniReader.HasValue(section, name);
        }

        // Returns true if the ini file has been opened. May still have line errors.
        bool IsOpen() const
        {
            return iniReader.ParseError() >= 0;
        }

        // Return the result of ini_parse(), i.e., 0 on success, line number of
        // first error on parse error, or -1 on file open error.
        int ParseError() const
        {
            return iniReader.ParseError();
        }

    private:
        ini iniReader;
    };
}

#endif // !AUX_INIPARSER_H