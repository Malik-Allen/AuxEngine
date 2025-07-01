# CSV Reader & Writer Documentation

This document provides an overview and usage examples for the `AuxEngine::CsvReader` and `AuxEngine::CsvWriter` classes — header-only C++ wrappers around the [csv-parser](https://github.com/vincentlaucsb/csv-parser) library, designed for easy reading and writing of CSV files with flexible formatting and type-safe access.

---

## CsvWriter

`CsvWriter` is a templated, header-only class that wraps the `csv::DelimWriter` from csv-parser to provide fluent, easy-to-use CSV writing capabilities. Supports writing standard CSV (comma-delimited), TSV, or custom-delimited files.

### Features
- Write CSV/TSV/custom-delimited files to any output stream (`ofstream`, `stringstream`, etc.)
- Fluent `operator<<` supports writing STL containers, tuples, arrays, etc.
- Control floating point decimal places globally
- Header-only and exception safe

### Usage Example: Writing CSV to File

```cpp
#include "CsvWriter.h"
#include <fstream>
#include <vector>
#include <tuple>
#include <string>
#include <iostream>

int main()
{
    // Open output file stream
    std::ofstream file("output.csv");
    if (!file.is_open()) {
        std::cerr << "Failed to open output.csv for writing.\n";
        return 1;
    }

    // Use CsvWriter with default flush behavior
    using Writer = AuxEngine::CsvWriter<std::ofstream, true>;
    Writer::SetDecimalPlaces(2);

    auto writer = Writer::FromCsv(file);

    // Write column headers
    writer << std::vector<std::string>{ "ID", "Name", "Price", "InStock" };

    // Write rows (convert bool to string to avoid warnings)
    writer << std::make_tuple(1, "Apple", 0.99, std::string("true"));
    writer << std::make_tuple(2, "Banana", 0.59, std::string("false"));
    writer << std::make_tuple(3, "Cherry", 1.99, std::string("true"));

    // Explicitly close the file to flush and release resource
    file.close();

    return 0;
}
```

### Usage Example: Reading CSV File

```cpp
#include "CsvReader.h"
#include <iostream>
#include <exception>

int main()
{
    try {
        // Initialize parser with path to CSV file
        AuxEngine::CsvReader reader("output.csv");

        // Iterate over each row in the file
        for (const auto& row : reader)
        {
            // Access by column name (case-sensitive)

            // Parse integer field "ID"
            if (row["ID"].is_int()) {
                int id = row["ID"].get<int>();
                std::cout << "ID: " << id << "\n";
            }

            // Parse string field "Name" (handles quotes)
            std::string name = row["Name"].get<>();
            std::cout << "Name: " << name << "\n";

            // Parse float field "Price"
            if (row["Price"].is_float()) {
                float price = row["Price"].get<float>();
                std::cout << "Price: " << price << "\n";
            }

            // Parse boolean-like field "InStock" as string
            std::string inStock = row["InStock"].get<>();
            std::cout << "InStock: " << inStock << "\n";

            std::cout << "---------------------\n";
        }
    }
    catch (const std::exception& ex) {
        std::cerr << "Error reading CSV: " << ex.what() << "\n";
    }

    return 0;
}
```