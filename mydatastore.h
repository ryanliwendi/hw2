//
// Created by 李文迪 on 2/13/25.
//

#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include <vector>
#include <map>
#include <string>

class MyDataStore : public DataStore
{
  public:
    MyDataStore();
    ~MyDataStore();
    void addProduct(Product* p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);
    void addToCart(std::string username, Product* product);
    bool validUsername(std::string username);
    void printCart(std::string username);
    void buyCart(std::string username);

   private:
    std::vector<Product*> products_;
    std::vector<User*> users_;
    std::map<std::string, std::vector<Product*> > cart_;
};

#endif //MYDATASTORE_H
