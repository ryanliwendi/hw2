//
// Created by 李文迪 on 2/12/25.
//
#include "clothing.h"
#include "util.h"
#include <sstream>
#include <vector>
#include <string>

using namespace std;

Clothing::Clothing(const string category, const string name, double price, int qty, string size, string brand):
     Product(category, name, price, qty), size_(size), brand_(brand)
{
}

Clothing::~Clothing()
{
}

set<string> Clothing::keywords() const
{
    set<string> keywords;
    set<string> product_name = parseStringToWords(name_);
    set<string> brand_name = parseStringToWords(brand_);
    keywords = setIntersection(product_name, brand_name);
    return keywords;
}

string Clothing::displayString() const
{
    stringstream ss;
    ss << name_ << "\n";
    ss << "Size: " << size_ << " ";
    ss << "Brand: " << brand_ << "\n";
    ss << price_ << " " << qty_ << " left." << "\n";
    return ss.str();
}

void Clothing::dump(ostream& os) const
{
    Product::dump(os);
    os << size_ << "\n" << brand_ << endl;
}
