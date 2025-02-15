//
// Created by 李文迪 on 2/12/25.
//
#include "movie.h"
#include "util.h"
#include <sstream>
#include <vector>
#include <string>

using namespace std;

Movie::Movie(const string category, const string name, double price, int qty, string genre, string rating):
     Product(category, name, price, qty), genre_(genre), rating_(rating)
{
}

Movie::~Movie()
{
}

set<string> Movie::keywords() const
{
    set<string> keywords;
    set<string> product_name = parseStringToWords(name_);
    keywords = product_name;
    keywords.insert(convToLower(genre_));
    return keywords;
}

string Movie::displayString() const
{
    stringstream ss;
    ss << name_ << "\n";
    ss << "Genre: " << genre_ << " ";
    ss << "Rating: " << rating_ << "\n";
    ss << price_ << " " << qty_ << " left.";
    return ss.str();
}

void Movie::dump(ostream& os) const
{
    Product::dump(os);
    os << genre_ << "\n" << rating_ << endl;
}
