#pragma once
#include <string>
#include <iostream>
#include <string>
using namespace std;

class Product {
private:
	string name;
	string sellbyDate;
	double price;
	int quantity;

	int index;
	int countP; 

	Product* nextP;

public:
	Product();


	//Getters and setters 
	string getName();
	string getDate();
	double getPrice();
	int getQuantity();
	Product* getNextP();
	void setNextP(Product* _next);
	void setName(string n);
	void setDate(string d);
	void setPrice(double p);
	void setQuantity(int q);

	int getIndex();
	void setIndex(int _d);

	int getProdCount(); 
	void setProdCount(int _pcount);
};





class Category {
private:
	string catTitle;
	int catID;
	int HcatCount; 

	Category* nextC;
	
	int lineID;
	Product* nestedP;
public:
	Category();


	//Getters and setters 
	string getCatTitle();
	void setCatTitle(string _title);

	int getCatCount();
	void setCatCount(int _catCount);
	
	void setNextC(Category* _next);
	Category* getNextC();

	void setIDofCat(int id);
	int getIDofCat();
};



class Line {
private:
	string title;
	int lineID;


	Line* next;
public:

	Line();

	//Getters and setters 
	string getTitle();
	void setTitle(string _title);

	void setNextL(Line* _next);
	Line* getNextL();

	int getLID();
	void setLID(int _id);

	


};


class user {
private:
	string name;
	string addU;
	int ID;
	int points;

	user* nextU;
public:
	user();

	string getName();
	void setName(string _name);

	void setNextU(user* _nextU);
	user* getNextU();

	int getUID();
	void setID(int _idU);

	int getPoints();
	void setPoints(int _points);

	string getAddress();
	void setAdd(string _add);
};

class Cart {
private: 
	string name; 
	double price; 
	int amountBought;
	int ID; 
	bool userStatus; 

	Cart* nextCart; 
public: 

	Cart(); 
	string getName();
	void setName(string _name);

	double getPrice();
	void setPrice(double _price);

	int getAmt();
	void setAmt(int _amt);

	Cart* getNextCart();
	void setNextCart(Cart* _next);

	bool getStatus();
	void setStatus(bool _status);

	int getUID();
	void setID(int _ID);
};



class List {
private:
	Line* head;
	Line* tail;

	Category* headC;
	Category* tailC;

	Product* headP;
	Product* tailP;

	user* headU; 
	user* tailU; 

	Cart* headCart; 
	Cart* tailCart; 
public:
	List();
	//~List();



	void addLine(string t);
	void displayLines();

	void addCategory(string title, int ID);
	void displayCategories(int n);

	void addProduct(string n, string d, double p, int q, int ID);
	void displayProducts(int id);

	void displayDetails(int n);

	void addUser(string n, string add, int _ID, int _points);
	bool verifyUserName(string nombre);

	void searchProducts(string input);

	void addToCart(int navigationNum, bool status, int quantityWanted, string n);
	void displayCart(int _id);

	//Function to loop through user list, find the ID of the inputed name 
	int getUserID(string name);

	double calcTotalPrice(int _id);

	int getProductIDFromName(string name);

	int getUserPoints(string name, int money); 

	void changeQuantity(string name, int navNum, int quantWanted);
	void removeCart(string name);

	//LAB6 

};

