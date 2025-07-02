// MIT License, Copyright (c) 2024 Malik Allen

#ifndef AUX_INIPARSER_H
#define AUX_INIPARSER_H

#include "inifile/inifile.h"

typedef ini::inifile Ini;

namespace AuxEngine
{
    class IniParser
    {
    public:
        IniParser(const IniParser&) = delete;
        IniParser& operator=(const IniParser&) = delete;
        IniParser(IniParser&&) = delete;
        IniParser& operator=(IniParser&&) = delete;

        IniParser() {};
        ~IniParser() {};

        std::string GetString(const std::string& section, const std::string& key)
        {
            return parser_[section][key];
        }

        int GetInteger(const std::string& section, const std::string& key)
        {
            return parser_[section][key].as<int>();
        }

        float GetFloat(const std::string& section, const std::string& key)
        {
            return parser_[section][key].as<float>();
        }

        bool GetBoolean(const std::string& section, const std::string& key)
        {
            return parser_[section][key].as<bool>();
        }

        std::vector<std::string> Sections() const
        {
            return parser_.sections();
        }

        std::vector<std::string> Keys(const std::string& section) 
        {
            return parser_[section].keys();
        }

        bool HasSection(const std::string& section) const
        {
            return parser_.contains(section);
        }

        bool HasValue(const std::string& section, const std::string& key)
        {
            return parser_.contains(section) && parser_[section].contains(key);
        }

        template <typename T>
        void Set(const std::string& section, const std::string& key, const T& value)
        {
            parser_.set(section, key, value);
        }

        bool LoadFile(const std::string& filePath)
        {
            return parser_.load(filePath);
        }

        bool WriteToFile(const std::string& filePath) const
        {
            return parser_.save(filePath);
        }

    private:
        Ini parser_;
    };
}

#endif // !AUX_INIPARSER_H