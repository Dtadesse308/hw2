#include "mydatastore.h"
#include <iostream>
#include <string>

using namespace std;


   /**
     * Adds a product to the data store
     */

    void MyDataStore::addProduct(Product* p){
        
        products_.push_back(p);

    }

    /**
     * Adds a user to the data store
     */
    void MyDataStore::addUser(User* u){
        users_[ (u->getName())] = u;
    }


    void MyDataStore::makeMap() {
        set<string> keys;
         //create map with keywords and products 
         for (int i = 0; i < (int)products_.size(); i ++){
            keys = products_[i]->keywords();
            //go through keys and add each keyword to map
            set<string>::iterator it;
            for (it = keys.begin() ; it != keys.end(); i ++){
                //check if keyword is in the map
                //if in the map, add prod to the set
                if (keyToProd_.find(*it) != keyToProd_.end()){
                    keyToProd_.find(*it)->second.insert(products_[i]);
                }
                //if not in map, create a set and add to mapz
                else if (keyToProd_.find(*it) == keyToProd_.end()){
                    set<Product*> newSet;
                    newSet.insert(products_[i]);
                    keyToProd_[*it] = newSet;
                }
            }
         }


    }

  
    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){

        vector<Product*> nulProd;

         //create map with keywords and products 
        makeMap();
       
        int termSize = terms.size();
    //no terms
        if (termSize == 0){
            return nulProd;
            //displayProducts(nulProd);
        }

    //only one term
        else if (termSize == 1){

            if (keyToProd_.find(terms[0]) != keyToProd_.end()){
                vector<Product*> singleProd ( keyToProd_.find(terms[0])->second.begin(),keyToProd_.find(terms[0])->second.end()  );
               // displayProducts(singleProd);
               return singleProd;
            }
        }

      
        //if term size is more than 1
        set<Product*> intersectSet;
        set<Product*> unionSet;
        set<Product*> temp;

        //and search (intersection)
        if (type == 2){
           
           
            bool initalized = false;
            for (int i = 0; i < (int)terms.size(); i ++){

                //initalize set with first terms products
                if (!initalized){
                    if (keyToProd_.find(terms[i]) != keyToProd_.end()) {
                    intersectSet = keyToProd_.find(terms[i])->second;

                    initalized = true;
                    }

                }

                 //on second set, place all intersection(s1 and s2) sets into tempset
                //set first set to temp and repeat for rest of the terms

                if (initalized){
                    if (keyToProd_.find(terms[i]) != keyToProd_.end()){
                        temp = setIntersection(intersectSet, keyToProd_.find(terms[i])->second);
                        intersectSet = temp;
                    }
                    
                }

            }

            vector<Product*> intersectionVect (intersectSet.begin() , intersectSet.end());
            //displayProducts(intersectionVect);
            return intersectionVect;
        }

        
        //or search (union / all)
        else if (type == 1){
           bool initalized = false;
            for (int i = 0; i < (int)terms.size(); ++i){

                if (!initalized){
                    if (keyToProd_.find(terms[i]) != keyToProd_.end()){
                        unionSet = keyToProd_.find(terms[i])->second;
                        initalized = true;
                    }
                }

                else if (initalized){
                    if (keyToProd_.find(terms[i]) != keyToProd_.end()){
                        temp = setUnion(unionSet, keyToProd_.find(terms[i])->second);
                        unionSet = temp;
                    }
                    
                }

                vector<Product*> unionVect (unionSet.begin() , unionSet.end());
               // displayProducts(unionVect);
                return unionVect;
            }
           
        }


        return nulProd;
    }


    /**
     * Reproduce the database file from the current Products and User values
     */

    void MyDataStore::dump(std::ostream& ofile){

        ofile<<"<products>"<<endl;
        for (int i = 0; i < (int)products_.size(); i ++){
            ofile<<products_[i]->getCategory()<<endl;
            ofile<<products_[i]->getName()<<endl; 
            ofile<<products_[i]->getPrice()<<endl; 
            ofile<<products_[i]->getQty()<<endl; 
            ofile<<products_[i]->getSpecific()<<endl; 
        }

        ofile<<'\n'<< "</products>"<<'\n'<< "<users>"<<endl;

        map<string,User*>::iterator it;
        for (it = users_.begin(); it != users_.end(); it ++){
            ofile<< (it->first)<<" "<<( (it->second)->getBalance()) <<" "<<  ( (it->second)->getType())<<endl;
        }

        ofile<<'\n';
    

    }

  

     //add to cart
    void MyDataStore::addToCart(std::string username, int index){

       

        //if user exisits in set, add to exisiting cart
        if (cart.find(username) != cart.end()){
            cart.find(username)->second.insert(products_[index]);
        }
        //if user dne, create a new cart and add to map
        else if (cart.find(username) == cart.end()){
            set<Product*> newSet;
            newSet.insert(products_[index]);
            cart[username] = newSet;
        }

    }

    //view card
    void MyDataStore::viewCart(std::string username){

        
        if (cart.find(username) == cart.end()){
            cout<<"Invalid username"<<endl;
            return;
        }

        else if ( cart.find(username) != cart.end() ){

        int index = 1;

        
        cout<<"Viewing Cart: "<<endl;
            //get the set of products from cart
           set<Product*> newSet =  cart.find(username)->second;
           set<Product*>::iterator it;
           for (it = newSet.begin(); it != newSet.end(); ++it){
               cout<<index<<": "<<(*it)->getName()<<endl;
               index++;
           }
        }
    }

    //buy from the cart
    void MyDataStore::buyCart(std::string username){

        
        //if enough money and in stock, 

        if ( (cart.find(username) == cart.end()) || (users_.find(username) == users_.end())){
            cout<<"Invalid username"<<endl;
            return;
        }

        else if ( cart.find(username) != cart.end() ){
            //get the set of product*'s
            set<Product*> newSet =  cart.find(username)->second;
            //get user balance
            double currBalance = users_.find(username)->second->getBalance();
            set<Product*>::iterator it;
            //go through items in users cart
            for (it = newSet.begin(); it != newSet.end(); ++it){
                //if enought money and enought in stock
                if ( ((*it)->getPrice() <= currBalance) && ( (*it)->getQty() >= 1) ){
                    //deduct from balance
                    currBalance -= (*it)->getPrice();
                    users_.find(username)->second->deductAmount((*it)->getPrice());
                    //remove from stock
                    (*it)->subtractQty(1);
                }
            }

        }



    }


