//
// Created by 李文迪 on 2/12/25.
//
#include "book.h"
#include "util.h"
#include <sstream>
#include <vector>
#include <string>

using namespace std;

Book::Book(const string category, const string name, double price, int qty, string ISBN, string author):
     Product(category, name, price, qty), ISBN_(ISBN), author_(author)
{
}

Book::~Book()
{
}

set<string> Book::keywords() const
{
    set<string> keywords;
    set<string> product_name = parseStringToWords(name_);
    set<string> author_name = parseStringToWords(author_);
    keywords = setIntersection(product_name, author_name);
    keywords.insert(ISBN_);
    return keywords;
}

string Book::displayString() const
{
   stringstream ss;
   ss << name_ << "\n";
   ss << "Author: " << author_ << " ";
   ss << "ISBN: " << ISBN_ << "\n";
   ss << price_ << " " << qty_ << " left." << "\n";
   return ss.str();
}

void Book::dump(ostream& os) const
{
    Product::dump(os);
    os << ISBN_ << "\n" << author_ << endl;
}
