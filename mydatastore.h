//
// Created by 李文迪 on 2/13/25.
//

#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include <vector>

class MyDataStore : public DataStore
{
  public:
    MyDataStore();
    ~MyDataStore();
    void addProduct(Product* p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);

   private:
     std::vector<Product*> products_;
     std::vector<User*> users_;
};

#endif //MYDATASTORE_H
