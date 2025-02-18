//
// Created by 李文迪 on 2/13/25.
//

#include "mydatastore.h"
#include "util.h"
#include "user.h"
#include "product.h"
#include <vector>
#include <map>
using namespace std;

MyDataStore::MyDataStore()
{

}

MyDataStore::~MyDataStore()
{
	for(int i = 0; i < products_.size(); i++)
        delete products_[i];
    for(int i = 0; i < users_.size(); i++)
        delete users_[i];
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
    vector<Product*> result;
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
          	return result;
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
    {
      (*it) -> dump(ofile);
      ofile << endl;
    }
    ofile << "</users>" << endl;
}

void MyDataStore::addToCart(string username, Product *product)
{
    if(!validUsername(username))
    {
        cout << "Invalid request" << endl;
        return;
    }
  	cart_[username].push_back(product);
}

bool MyDataStore::validUsername(string username)
{
    for(vector<User*>::iterator it = users_.begin(); it != users_.end(); ++it)
      	if(username == (*it) -> getName())
        	return true;
  	return false;
}

void MyDataStore::printCart(string username)
{
  	int id = 0;
  	for(vector<Product*>::iterator it = cart_[username].begin(); it != cart_[username].end(); ++it)
    {
        id++;
        cout << "Item " << id << endl;
        cout << (*it) -> displayString() << endl;
    }
}

void MyDataStore::buyCart(string username)
{
    int user_idx = 0;
    for(int i = 0; i < users_.size(); i++)
    	if(users_[i] -> getName() == username)
      		user_idx = i;

    vector<Product*>::iterator it = cart_[username].begin();
    while(it != cart_[username].end())
    {
        if((*it) -> getQty() >= 1 && users_[user_idx] -> getBalance() >= (*it) -> getPrice())
        {
          	(*it) -> subtractQty(1);
            users_[user_idx] -> deductAmount((*it) -> getPrice());
            it = cart_[username].erase(it);
        }
        else
          ++it;
    }
}