#include "datastore.h"
#include "util.h"
#include <map>
class MyDataStore : public DataStore {


    public:

  /**
     * Adds a product to the data store
     */
    virtual void addProduct(Product* p);

		~MyDataStore();

    /**
     * Adds a user to the data store
     */
    virtual void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    virtual std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
    virtual void dump(std::ostream& ofile);

    //creates a map with keywords to products;
    void makeMap();

    //add to cart
    void addToCart(std::string username, Product* hit);

    //view card
    void viewCart(std::string username);

    //buy from the cart
    void buyCart(std::string username);


    private:

		
    std::vector<Product*> products_;
	//	std::vector<Product*>searchResults_;
    std::map<std::string,User*> users_;
    std::map<std::string,std::set<Product*>> keyToProd_;
    std::map<std::string,std::vector<Product*>> cart;
};