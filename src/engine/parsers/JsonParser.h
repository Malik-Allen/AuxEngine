// MIT License, Copyright (c) 2024 Malik Allen

#ifndef AUX_JSONPARSER_H
#define AUX_JSONPARSER_H

#include "nlohmann/json.hpp"

#include <fstream>
#include <iostream>


namespace AuxEngine
{
    typedef nlohmann::json json;

    class JsonParser
    {
    public:
        JsonParser( const JsonParser& ) = delete;
        JsonParser& operator=( const JsonParser& ) = delete;
        JsonParser( JsonParser&& ) = delete;
        JsonParser& operator=( JsonParser&& ) = delete;

        JsonParser() :
            jsonData_(json())
        {};

        ~JsonParser() {};

        bool ParseFromString( const std::string& jsonString )
        {
            try
            {
                jsonData_ = json::parse( jsonString );
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
                file >> jsonData_;
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
            return jsonData_[key].get<T>();
        }

        // Check if a key exists in the JSON data
        bool Contains( const std::string& key ) const
        {
            return jsonData_.contains( key );
        }

    private:
        json jsonData_;
    };
}

#endif // !AUX_JSONPARSER_H