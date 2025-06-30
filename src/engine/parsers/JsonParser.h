// MIT License, Copyright (c) 2024 Malik Allen

#ifndef AUX_JSONPARSER_H
#define AUX_JSONPARSER_H

#include "nlohmann/json.hpp"

#include <fstream>
#include <iostream>

typedef nlohmann::json json;

namespace  AuxEngine
{
    class JsonParser
    {
    public:
        JsonParser( const JsonParser& ) = delete;
        JsonParser& operator=( const JsonParser& ) = delete;
        JsonParser( JsonParser&& ) = delete;
        JsonParser& operator=( JsonParser&& ) = delete;

        JsonParser() :
            jsonData(json())
        {};

        ~JsonParser() {};

        bool ParseFromString( const std::string& jsonString )
        {
            try
            {
                jsonData = json::parse( jsonString );
                return true;
            }
            catch( json::parse_error& e )
            {
                std::cerr << "JSON Parse Error: " << e.what() << '\n';
                return false;
            }
        }

        // Load JSON from a file
        bool ParseFromFile( const std::string& fileName )
        {
            std::ifstream file( fileName );
            if( !file.is_open() )
            {
                std::cerr << "Unable to open file: " << fileName << '\n';
                return false;
            }

            try
            {
                file >> jsonData;
                return true;
            }
            catch( json::parse_error& e )
            {
                std::cerr << "JSON Parse Error: " << e.what() << '\n';
                return false;
            }
        }

        // Get a value from the JSON data
        template <typename T>
        T GetValue( const std::string& key )
        {
            return jsonData[key].get<T>();
        }

        // Check if a key exists in the JSON data
        bool Contains( const std::string& key ) const
        {
            return jsonData.contains( key );
        }

    private:
        json jsonData;
    };
}

#endif // !AUX_JSONPARSER_H