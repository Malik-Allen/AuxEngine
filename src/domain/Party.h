// MIT License, Copyright (c) 2025 Malik Allen

#ifndef AUX_PARTY_H
#define AUX_PARTY_H

#include <string>

namespace AuxEngine
{
    struct PersonName 
    {
        std::string given_;
        std::string family_;
    };

    struct PostalAddress 
    {
        std::string street_;
        std::string city_;
        std::string region_;
        std::string country_;
        std::string postalCode_;
    };

    struct ContactDetails 
    {
        std::string email_;
    };

    struct Party 
    {
        PersonName name_;
        PostalAddress address_;
        ContactDetails contact_;
    };

}

#endif