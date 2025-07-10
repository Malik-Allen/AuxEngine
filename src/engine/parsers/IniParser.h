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
        explicit IniParser(const std::string& filePath)
            : file_(filePath)
        {};

        IniParser(const IniParser& other)
            : file_(other.file_)
            , data_(other.data_)
        {};

        IniParser(IniParser&& other) noexcept
            : file_(other.file_)
            , data_(other.data_)
        {
            other.file_ = Ini("");
            other.data_ = IniData();
        };

        IniParser& operator=(const IniParser& other)
        {
            file_ = other.file_;
            data_ = other.data_;
            return *this;
        };

        IniParser& operator=(IniParser&& other) noexcept
        {
            if (this != &other)
            {
                file_ = other.file_;
                data_ = other.data_;

                other.file_ = Ini("");
                other.data_ = IniData();
            }
            return *this;
        };

        ~IniParser() {};

        std::string GetString(const std::string& section, const std::string& key, const std::string& defaultValue = "")
        {
            if (!data_[section][key].empty())
            {
                return data_[section][key];
            }
            else
            {
                return defaultValue;
            }
        }

        int GetInteger(const std::string& section, const std::string& key, int defaultValue = 0)
        {
            if (!data_[section][key].empty())
            {
                return std::stoi(data_[section][key]);
            }
            else
            {
                return defaultValue;
            }
        }

        float GetFloat(const std::string& section, const std::string& key, float defaultValue = 0.0f)
        {
            if (!data_[section][key].empty())
            {
                return std::stof(data_[section][key]);
            }
            else
            {
                return defaultValue;
            }
        }
        float GetDouble(const std::string& section, const std::string& key, float defaultValue = 0.0)
        {
            if (!data_[section][key].empty())
            {
                return std::stod(data_[section][key]);
            }
            else
            {
                return defaultValue;
            }
        }

        bool GetBoolean(const std::string& section, const std::string& key, bool defaultValue = false)
        {
            std::string value = data_[section][key];
            if (value.empty())
            {
                return defaultValue;
            }
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

        void Set(const std::string& section, const std::string& key, const std::string& value)
        {
            data_[section][key] = value;
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