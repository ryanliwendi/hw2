//
// Created by 李文迪 on 2/12/25.
//

#ifndef MOVIE_H
#define MOVIE_H

#include "product.h"

class Movie: public Product
{
public:
    Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating);
    ~Movie();
    std::set<std::string> keywords() const;
    std::string displayString() const;
    void dump(std::ostream& os) const;

private:
    std::string genre_;
    std::string rating_;
};

#endif //MOVIE_H
