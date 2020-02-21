
#pragma once

#include <string>
#include <iostream>
#include <cstdint>
#include <sstream>

#include "BaseDatabase.hpp"

class StringDatabase : public BaseDatabase<std::string> {
public:
	StringDatabase() = default;
	virtual ~StringDatabase() noexcept = default;
	StringDatabase(const StringDatabase& other) = default;
	StringDatabase(StringDatabase&& other) noexcept = default;
	StringDatabase& operator=(const StringDatabase& other) = default;
	StringDatabase& operator=(StringDatabase&& other) noexcept = default;

	void read(std::istream& in) override;
	void write(std::ostream& out) const override;

};

inline void StringDatabase::read(std::istream& in) {
	std::string str;
	while (std::getline(in, str)) {
		Row row;
		std::stringstream s(str);
		std::string field;
		while (std::getline(s, field, '\t')) {
			row.push_back(std::move(field));
		}
		data.push_back(std::move(row));
	}
}

inline void StringDatabase::write(std::ostream& out) const {
	for (std::size_t i = 0; i < data.size(); ++i) {
		auto& row = data[i];

		for (std::size_t j = 0; j < row.size(); ++j) {
			auto& field = row[j];

			out << field;
			if (j < row.size() - 1) {	// skip last in a row
				out << '\t';
			}
		}
		if (i < data.size() - 1) {	// skip last newline
			out << '\n';
		}
	}
}

inline std::ostream& operator<<(std::ostream& os, const StringDatabase& db) {
	db.write(os);
	return os;
}

inline std::istream& operator>>(std::istream& is, StringDatabase& db) {
	db.read(is);
	return is;
}
