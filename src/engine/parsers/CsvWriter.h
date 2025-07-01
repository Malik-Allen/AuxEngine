// MIT License, Copyright (c) 2024 Malik Allen

#ifndef AUX_CSVWRITER_H
#define AUX_CSVWRITER_H

#include "csv-parser/csv.hpp"

#include <ostream>
#include <memory>

namespace AuxEngine
{
    template <class OutputStream, bool Flush = true>
    class CsvWriter
    {
    public:
        CsvWriter(const CsvWriter&) = delete;
        CsvWriter& operator=(const CsvWriter&) = delete;
        CsvWriter(CsvWriter&&) noexcept = default;
        CsvWriter& operator=(CsvWriter&&) noexcept = default;

        // Factory: CSV (comma-delimited)
        static CsvWriter FromCsv(OutputStream& stream)
        {
            return CsvWriter(std::make_unique<csv::CSVWriter<OutputStream, Flush>>(stream));
        }

        // Factory: TSV (tab-delimited)
        static CsvWriter FromTsv(OutputStream& stream)
        {
            return CsvWriter(std::make_unique<csv::TSVWriter<OutputStream, Flush>>(stream));
        }

        // Factory: custom delimiter and quote
        template <char Delim, char Quote>
        static CsvWriter FromCustom(OutputStream& stream)
        {
            return CsvWriter(std::make_unique<csv::DelimWriter<OutputStream, Delim, Quote, Flush>>(stream));
        }

        // Write row (supports vectors, arrays, tuples, etc.)
        template<typename T>
        CsvWriter& operator<<(const T& row)
        {
            (*writer) << row;
            return *this;
        }

        static void SetDecimalPlaces(int places)
        {
            csv::set_decimal_places(places);
        }

    private:
        using WriterType = csv::CSVWriter<OutputStream, Flush>;

        explicit CsvWriter(std::unique_ptr<WriterType> _writer)
            : writer(std::move(_writer))
        {
        }

        std::unique_ptr<WriterType> writer;
    };
}

#endif // !AUX_CSVWRITER_H