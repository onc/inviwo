/*********************************************************************************
 *
 * Inviwo - Interactive Visualization Workshop
 *
 * Copyright (c) 2017 Inviwo Foundation
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *********************************************************************************/

#include <modules/plotting/utils/csvreader.h>

#include <modules/plotting/datastructures/column.h>
#include <modules/plotting/datastructures/dataframe.h>
#include <inviwo/core/util/filesystem.h>

#include <fstream>

namespace inviwo {

CSVReader::CSVReader() : delimiters_(","), firstRowHeader_(true) {}

CSVReader* CSVReader::clone() const { return new CSVReader(*this); }

void CSVReader::setDelimiters(const std::string& delim) { delimiters_ = delim; }

void CSVReader::setFirstRowHeader(bool hasHeader) {
    firstRowHeader_ = true;
}

std::shared_ptr<plot::DataFrame> CSVReader::readData(const std::string& fileName) {
    std::ifstream file(fileName);

    if (!file.is_open()) {
        throw FileException(std::string("CSVReader: Could not open file \"" + fileName + "\"."));
    }

    file.seekg(0, std::ios::end);
    std::streampos len = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<char> buffer(len);
    // read in entire file
    file.read(buffer.data(), len);

    // create a string stream for easier handling
    std::stringstream in(buffer.data());

    // current line
    size_t lineNumber = 1u;

    auto extractColumn = [&]() -> std::pair<std::string, bool> {
        std::string value;
        size_t quoteCount = 0;
        char prev = 0;
        const size_t start = lineNumber;

        auto isLineBreak = [](const char ch, auto& in) {
            if (ch == '\r') {
                // consume potential LF (\n) following CR (\r)
                if (in.peek() == '\n') {
                    in.get();
                }
                return true;
            } else {
                return (ch == '\n');
            }
        };

        char ch;
        while (in.get(ch)) {
            bool linebreak = isLineBreak(ch, in);
            if (linebreak) {
                ++lineNumber;  // increase line counter
                // ensure that ch is equal to '\n'
                ch = '\n';
                // consume line break, if inside quotes
                if ((quoteCount & 1) != 0) {
                    value += ch;
                    prev = ch;
                    continue;
                }
            }
            if (ch == '"') {
                ++quoteCount;
            } else if (util::contains(delimiters_, ch) || linebreak) {
                // found a delimiter/newline, ensure that it isn't enclosed by quotes,
                // i.e. an even count of quotes
                if ((quoteCount == 0) || ((prev == '"') && ((quoteCount & 1) == 0))) {
                    return{ value, linebreak };
                }
            }
            prev = ch;
            value += ch;
        }
        if (((quoteCount & 1) != 0) && in.eof()) {
            throw Exception("CSVReader: unmatched quotes (line " + std::to_string(lineNumber) + ")");
        }
        return {value, false};
    };

    auto extractRow = [&]() -> std::vector<std::string> {        
        auto val = extractColumn();
        if (in.eof() && val.first.empty()) {
            // reached end of file, no more data
            return{};
        }
        std::vector<std::string> values;
        values.push_back(val.first);
        while (!val.second && !in.eof()) {
            val = extractColumn();
            values.push_back(val.first);
        }
        return values;
    };

    std::vector<std::string> headers;
    if (firstRowHeader_) {
        // read headers
        headers = extractRow();
        if (headers.empty()) {
            throw Exception("CSVReader: no column headers found.");
        }
    }
 
    std::vector<std::vector<std::string>> exampleRows;
    std::streampos streamPos = in.tellg();
    for (auto exampleRow = 0u; exampleRow < 50; ++exampleRow) {
        auto row = extractRow();
        if (exampleRow == 0 && row.empty()) {
            throw Exception("CSVReader: empty file, no data");
        }
        else if (row.empty()) {
            // No more rows
            in.clear(); // clear eof-bit
            break;
        }
        exampleRows.emplace_back(row);
    } 
    // Rewind to start position
    in.seekg(streamPos, std::ios::beg);
    if (!firstRowHeader_) {
        // assign default column headers
        for (size_t i = 0; i < exampleRows.front().size(); ++i) {
            headers.push_back(std::string("Column ") + std::to_string(i + 1));
        }
    }

    // figure out column types
    auto dataFrame = plot::createDataFrame(exampleRows, headers);
    size_t rowIndex = firstRowHeader_ ? 1 : 0;
    std::vector<std::string> data = extractRow();
    while (!data.empty()) {
        // Do not add empty rows, i.e. rows with only delimiters (,,,,) or newline
        auto emptyIt = std::find_if(std::begin(data), std::end(data),
                                    [](const auto& a) { return !a.empty(); });
        if (emptyIt != data.end()) {
            // May throw DataTypeMismatch, but do not catch it since it means that the DataFrame is
            // in an invalid state
            dataFrame->addRow(data);
        }
        data = extractRow();
        ++rowIndex;
    }
    dataFrame->updateIndexBuffer();
    return dataFrame;
}

}  // namespace inviwo
