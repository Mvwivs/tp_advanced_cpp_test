
#include <string>
#include <sstream>
#include <cassert>

#include "StringDatabase.hpp"

// test usage
int main() {

	std::string data = "first\t" "second\t" "third\n"	// test data
						"first\t" "second";
	std::stringstream ss(data);
	std::istream& in = ss;	// mock std::cin
	
	StringDatabase db;
	in >> db;
	db.add({ 0, 0 }, "new");
	db.remove({ 1, 0 });
	db[{ 0, 2 }] = "update";
	
	bool exceptionThrown = false;
	try {
		db.remove({ 2, 1 });	// expecting out of range exception to occur
	}
	catch (const std::exception& e) {
		exceptionThrown = true;
	}
	assert(exceptionThrown);

	std::stringstream result;
	std::ostream& out = result;	// mock std::cout
	out << db;

	std::string expected = "new\t" "first\t" "update\t" "third\n"	// expected result
							"second";
	assert(result.str() == expected);

	return 0;
}
