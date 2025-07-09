// MIT License, Copyright (c) 2024 Malik Allen

#ifndef AUX_INIPARSER_H
#define AUX_INIPARSER_H

#include "mini/ini.h"

typedef mINI::INIFile Ini;
typedef mINI::INIStructure IniData;

namespace AuxEngine
{
    class IniParser
    {
    public:
        IniParser(const IniParser&) = delete;
        IniParser& operator=(const IniParser&) = delete;
        IniParser(IniParser&&) = delete;
        IniParser& operator=(IniParser&&) = delete;

        explicit IniParser(const std::string& filePath) 
            : file_(filePath)
        {};

        ~IniParser() {};

        std::string GetString(const std::string& section, const std::string& key)
        {
            return data_[section][key];
        }

        int GetInteger(const std::string& section, const std::string& key)
        {
            return std::stoi(data_[section][key]);
        }

        float GetFloat(const std::string& section, const std::string& key)
        {
            return std::stof(data_[section][key]);
        }

        bool GetBoolean(const std::string& section, const std::string& key)
        {
            std::string value = data_[section][key];
            std::transform(value.begin(), value.end(), value.begin(), ::tolower); // make lowercase
            return (value == "true" || value == "1" || value == "yes" || value == "on");
        }

        std::vector<std::string> Sections() const
        {
            std::vector<std::string> sections;
            for (const auto& pair : data_)
            {
                sections.push_back(pair.first);
            }
            return sections;
        }

        std::vector<std::string> Keys(const std::string& section) 
        {
            std::vector<std::string> keys;
            for (const auto& pair : data_[section])
            {
                keys.push_back(pair.second);
            }
            return keys;
        }

        bool HasSection(const std::string& section) const
        {
            return data_.has(section);
        }

        bool HasValue(const std::string& section, const std::string& key)
        {
            return data_.has(section) && data_[section].has(key);
        }

        void AddSection(const std::string& section)
        {
            data_[section];
        }

        bool Read()
        {
            return file_.read(data_);
        }

        bool Write()
        {
            return file_.write(data_);
        }

    private:
        Ini file_;
        IniData data_;
    };
}

#endif // !AUX_INIPARSER_H