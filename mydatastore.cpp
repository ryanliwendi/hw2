//
// Created by 李文迪 on 2/13/25.
//

#include "mydatastore.h"
#include "util.h"
#include <vector>
#include <map>
using namespace std;

MyDataStore::MyDataStore()
{

}

MyDataStore::~MyDataStore()
{

}

void MyDataStore::addProduct(Product *product)
{
    products_.push_back(product);
}

void MyDataStore::addUser(User *user)
{
    users_.push_back(user);
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type)
{
    set<Product*> valid_products;
    map<string, set<Product*> > keywords_map;
    for(vector<Product*>::iterator it = products_.begin(); it != products_.end(); ++it)
    {
        set<string> key = (*it) -> keywords();
        for(set<string>::iterator it2 = key.begin(); it2 != key.end(); ++it2)
            keywords_map[*it2].insert(*it);
    }
    if(type == 0)
    {
        valid_products = keywords_map[terms[0]];
        for(int i = 1;i < terms.size(); i++)
        {
          if(keywords_map.find(terms[i]) == keywords_map.end())
          {
            valid_products.clear();
            continue;
          }
          valid_products = setIntersection(valid_products, keywords_map[terms[i]]);
        }
    }
    if(type == 1)
        for(int i = 0;i < terms.size(); i++)
        {
          if(keywords_map.find(terms[i]) == keywords_map.end())
            continue;
          valid_products = setUnion(valid_products, keywords_map[terms[i]]);
        }
    vector<Product*> result;
    for(set<Product*>::iterator it = valid_products.begin(); it != valid_products.end(); ++it)
      result.push_back((*it));
    return result;
}

void MyDataStore::dump(ostream& ofile)
{
    ofile << "<products>" << endl;
    for(vector<Product*>::iterator it = products_.begin(); it != products_.end(); ++it)
      (*it) -> dump(ofile);
    ofile << "</products>" << endl;
    ofile << "<users>" << endl;
    for(vector<User*>::iterator it = users_.begin(); it != users_.end(); ++it)
      (*it) -> dump(ofile);
}

void MyDataStore::addToCart(string username, Product *product)
{
  	cart_[username].push_back(product);
}

bool MyDataStore::validUsername(string username)
{
  	bool flag = false;
    for(vector<User*>::iterator it = users_.begin(); it != users_.end(); ++it)
      if(username == (*it) -> getName())
        flag = true;
  	return flag;
}

void MyDataStore::printCart(string username)
{
  	int id = 0;
  	for(vector<Product*>::iterator it = cart_[username].begin(); it != cart_[username].end(); ++it)
    {
        id++;
        cout << id << ": ";
        cout << (*it) -> displayString() << endl;
    }
}

void MyDataStore::buyCart(string username)
{
    int user_idx = 0;
    for(int i = 0; i < users_.size(); i++)
      if(users_[i] -> getName() == username)
      	user_idx = i;
	for(int i = 0; i < cart_[username].size(); i++)
    {
       if(cart_[username][i] -> getQty() >= 1 && users_[user_idx] -> getBalance() >= cart_[username][i] -> getPrice())
       {
         cart_[username][i] -> subtractQty(1);
         users_[user_idx] -> deductAmount(cart_[username][i] -> getPrice());
         cart_[username].erase(cart_[username].begin() + i);
         i--;
       }
    }
}