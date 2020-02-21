#pragma once

#include <stdexcept>
#include <vector>
#include <string>
#include <iostream>
#include <cstdint>
#include <utility>

template <typename T>
class BaseDatabase {
public:
	BaseDatabase() = default;
	virtual ~BaseDatabase() noexcept = default;
	BaseDatabase(const BaseDatabase& other) = default;
	BaseDatabase(BaseDatabase&& other) noexcept = default;
	BaseDatabase& operator=(const BaseDatabase& other) = default;
	BaseDatabase& operator=(BaseDatabase&& other) noexcept = default;

	using Position = std::pair<std::size_t, std::size_t>;

	// add element to database
	virtual void add(const Position& pos, const T& val);
	// remove element from database
	virtual void remove(const Position& pos);
	// read element from database
	virtual const T& operator[](const Position& pos) const;
	// access element from database
	virtual T& operator[](const Position& pos);

protected:
	// fill database from stream
	virtual void read(std::istream& in) = 0;
	// output database to stream
	virtual void write(std::ostream& out) const = 0;

	using Row = std::vector<T>;
	std::vector<Row> data;
};

template <typename T>
inline void BaseDatabase<T>::add(const Position& pos, const T& val) {
	auto& row = data.at(pos.first);
	if (pos.second > row.size()) { // forbid skipping elements
		throw std::out_of_range("Field " + std::to_string(pos.second) + " is out of range");
	}
	else if (pos.second == row.size()) {	// add new element to end of string
		row.push_back(val);
	}
	else {	// insert element in the middle of string
		row.insert(row.begin() + pos.second, val);
	}
}

template <typename T>
inline void BaseDatabase<T>::remove(const Position& pos) {
	auto& row = data.at(pos.first);
	if (pos.second >= row.size()) {	// element at pos doesn't exist
		throw std::out_of_range("Field " + std::to_string(pos.second) + " is out of range");
	}
	row.erase(row.begin() + pos.second);
}

template <typename T>
inline const T& BaseDatabase<T>::operator[](const Position& pos) const {
	auto& row = data.at(pos.first);
	return row.at(pos.second);
}

template <typename T>
inline T& BaseDatabase<T>::operator[](const Position& pos) {
	auto& row = data.at(pos.first);
	return row.at(pos.second);
}
