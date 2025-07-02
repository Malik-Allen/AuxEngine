// MIT License, Copyright (c) 2025 Malik Allen

#ifndef AUX_CSVREADER_H
#define AUX_CSVREADER_H

#include "csv-parser/csv.hpp"

#include <string>

namespace AuxEngine
{
    class CsvReader
    {
    public:
        using RowType = csv::CSVRow;
        using Iterator = csv::CSVReader::iterator;

        CsvReader(const CsvReader&) = delete;
        CsvReader& operator=(const CsvReader&) = delete;
        CsvReader(CsvReader&&) = delete;
        CsvReader& operator=(CsvReader&&) = delete;

        explicit CsvReader(const std::string& filePath)
            : reader_(filePath)
        {}

        CsvReader(const std::string& filePath, const csv::CSVFormat& format)
            : reader_(filePath, format)
        {}

        Iterator begin() { return reader_.begin(); }
        Iterator end() { return reader_.end(); }

    private:
        csv::CSVReader reader_;
    };
}

#endif // !AUX_CSVREADER_H