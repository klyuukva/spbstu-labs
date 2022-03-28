#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <functional>

#include "bookmarks.hpp"

using functionBookmark = std::function<void(Bookmarks& phonebook, std::ostream& out)>;
using functionMap = std::function<functionBookmark(std::istream&)>;

functionBookmark parseAdd(std::istream& in);
functionBookmark parseStore(std::istream& in);
functionBookmark parseInsert(std::istream& in);
functionBookmark parseDeleteMark(std::istream& in);
functionBookmark parseShow(std::istream& in);
functionBookmark parseMove(std::istream& in);

bool parseMarkName(std::string& name, std::istream& in);
bool checkNumber(const std::string& number);

std::istream& operator>>(std::istream& in, functionBookmark& functionBookmark);

void outputErrorMessage(Bookmarks&, std::ostream& out);
void outputErrorMessageForSteps(Bookmarks&, std::ostream& out);

#endif
