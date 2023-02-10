#include "mydatastore.h"
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;


   /**
     * Adds a product to the data store
     */
		MyDataStore::~MyDataStore(){

			//std::vector<Product*> products_;
    	//std::map<std::string,User*> users_;
			for (int i = 0; i < products_.size(); i ++){
				delete products_[i];
			}
			
		
		

			map<string,User*>::iterator it;
			for (it = users_.begin(); it != users_.end(); ++it){
				delete (it->second);
			}

		}
    void MyDataStore::addProduct(Product* p){
        
        products_.push_back(p);
				
				
        set<string> keys;
				keys = p->keywords();
			set<string>::iterator it;
			 for (it = keys.begin() ; it != keys.end(); it++){
                //check if keyword is in the map
                //if in the map, add prod to the set
								
                if (keyToProd_.find(*it) != keyToProd_.end()){
                   keyToProd_[*it].insert(p);
                }
								
                //if not in map, create a set and add to mapz
                else {
                    set<Product*> newSet;
                    newSet.insert(p);
                    keyToProd_[*it] = newSet;
                }
								
            }
    }

    /**
     * Adds a user to the data store
     */
    void MyDataStore::addUser(User* u){
    

        users_[ (u->getName())] = u;
    }


    void MyDataStore::makeMap() {
			keyToProd_.clear();
        set<string> keys;
         //create map with keywords and products 
				 cout << "product size" << products_.size() <<endl;
         for (int i = 0; i < (int)products_.size(); i++){
            keys = products_[i]->keywords();
						cout <<"keys" << endl;
						for(string k :keys) cout << k <<endl;
            //go through keys and add each keyword to map

            set<string>::iterator it;
						cout<<"KEYS SIZE" << keys.size()<<endl;
						
            for (it = keys.begin() ; it != keys.end(); it++){
                //check if keyword is in the map
                //if in the map, add prod to the set
								
                if (keyToProd_.find(*it) != keyToProd_.end()){
                   keyToProd_[*it].insert(products_[i]);
                }
								
                //if not in map, create a set and add to mapz
                else {
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


				map<string,set<Product*>>::iterator it;

			//	for (it = keyToProd_.begin(); it != keyToProd_.end(); ++it){
				//	cout<<(it->first)<<endl;
				//}
        vector<Product*> nulProd;

         //create map with keywords and products 

        //makeMap();
       
        int termSize = terms.size();
			
    //no terms
        if (termSize == 0){
            return nulProd;
            //displayProducts(nulProd);
        }

    //only one term
       // else if (termSize == 1){

            // if (keyToProd_.find(terms[0]) != keyToProd_.end()){
							
               //vector<Product*> singleProd ( keyToProd_[terms[0]].begin(),keyToProd_[terms[0]].end()  );
              //  displayProducts(singleProd);
		  //  vector<Product*> singleProd ( keyToProd_[terms[0]].begin(),keyToProd_[terms[0]].end()  );

           //    return singleProd;
            //}
      //  }
				// return nulProd;

      
        //if term size is more than 1
        set<Product*> intersectSet;
        set<Product*> unionSet;
        set<Product*> temp;

        //and search (intersection)
        if (type == 0){      
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

                else if (initalized){
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
					
            vector<string>::iterator it;
            for (it = terms.begin(); it != terms.end(); ++it){
				
                if (!initalized){
								//	cout<<"search1"<<endl;
                    if (keyToProd_.find((*it)) != keyToProd_.end()){											
                        unionSet = keyToProd_[*it];
                        initalized = true;
                    } 
                }

                else if (initalized){
									//cout<<"search2"<<endl;
                    if (keyToProd_.find((*it)) != keyToProd_.end()){
											
                        temp = setUnion(unionSet, keyToProd_[*it]);
                        unionSet = temp;
                    }
                    
                }
                
            }
						//cout<<"search3"<<endl;
				vector<Product*> unionVect(unionSet.begin() , unionSet.end());
                return unionVect;
				


        }


        return nulProd;
    }


    /**
     * Reproduce the database file from the current Products and User values
     */

    void MyDataStore::dump(std::ostream& ofile){

        ofile<<"<products>"<<endl;
        for (int i = 0; i < (int)products_.size(); i ++){
            products_[i]->dump(ofile);
        
        }

        ofile<< "</products>"<<'\n'<< "<users>"<<endl;

        map<string,User*>::iterator it;
        for (it = users_.begin(); it != users_.end(); it ++){
            (it->second)->dump(ofile);
        }


        ofile<<"</users>"<<endl;
    

    }

  

     //add to cart
    void MyDataStore::addToCart(std::string username, Product* hit){

      // index--;
	
			
        //if user exisits in set, add to exisiting cart
        if (users_.find(username) == users_.end()){
            cout<< "Invalid request"<<endl;
            return;
        }
        else if (cart.find(username) != cart.end()){
            cart.find(username)->second.push_back(hit);
						
        }
        //if user dne, create a new cart and add to map
        else if (cart.find(username) == cart.end()){
            vector<Product*> newSet;
            newSet.push_back(hit);
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

        
        //cout<<"Viewing Cart: "<<endl;
            //get the set of products from cart
           vector<Product*> newSet =  cart[username];
					
           
           for (int i = 0; i < newSet.size(); i++){
               cout<<"Item "<<index<<endl<<newSet[i]->displayString()<<endl;
							 cout<<endl;
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
            vector<Product*> newSet =  cart.find(username)->second;
            //get user balance
            double currBalance = users_.find(username)->second->getBalance();
            
						vector<Product*> temp;
            //go through items in users cart
            for (int i = 0; i < newSet.size(); ++i){
                //if enought money and enought in stock
                if ( (newSet[i]->getPrice() <= currBalance) && ( newSet[i]->getQty() >= 1) ){
                    //deduct from balance
                    currBalance -= newSet[i]->getPrice();
                    users_.find(username)->second->deductAmount(newSet[i]->getPrice());
                    //remove from stock
                    newSet[i]->subtractQty(1);
                }

								else {
									temp.push_back(newSet[i]);
								}
            }
						if (temp.size() == 0){
             cart.erase(username);
           }
           else {
             cart[username]=temp;
           }




        }



    }


