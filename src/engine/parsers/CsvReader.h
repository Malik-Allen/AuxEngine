// MIT License, Copyright (c) 2025 Malik Allen

#ifndef AUX_CSVREADER_H
#define AUX_CSVREADER_H

#include "csv-parser/csv.hpp"

#include <string>

namespace AuxEngine
{
    using CsvFormat = csv::CSVFormat;
    using CsvRow = csv::CSVRow;

    class CsvReader
    {
    public:
        using Iterator = csv::CSVReader::iterator;

        CsvReader(const CsvReader&) = delete;
        CsvReader& operator=(const CsvReader&) = delete;
        CsvReader(CsvReader&&) = delete;
        CsvReader& operator=(CsvReader&&) = delete;

        explicit CsvReader(const std::string& filePath)
            : reader_(filePath)
        {}

        CsvReader(const std::string& filePath, const CsvFormat& format)
            : reader_(filePath, format)
        {}

        Iterator begin() { return reader_.begin(); }
        Iterator end() { return reader_.end(); }
        std::vector<std::string> get_col_names() const { return reader_.get_col_names(); }

    private:
        csv::CSVReader reader_;
    };
}

#endif // !AUX_CSVREADER_H