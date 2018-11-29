#include <string>
#include <iostream>
#include "header.h"
using namespace std;

int countLine = 0;
int countCat = 0;
int countProd = 0; 
int countUser = 0; 

user::user() {
	nextU = NULL; 
	name = " ";
	addU = " ";
	ID = 0;
	points = 0;
}

Line::Line() {
	next = NULL;
	lineID = 0; 
}

Category::Category() {

	nextC = NULL;
	//prev = NULL; 
	catID = 0; 
	HcatCount = 0; 
}

Product::Product() {
	name = " ";
	sellbyDate = " ";
	price = 0;
	quantity = 0;

	countP = 0; 
	index = 0;
	nextP = NULL;
	
}

List::List() {
	head = NULL;
	tail = NULL;

	headC = NULL;
	tailC = NULL;

	headP = NULL; 
	tailP = NULL; 

	headU = NULL; 
	tailU = NULL; 

	headCart = NULL;
	tailCart = NULL; 
}

Cart::Cart() {
	name = " ";
	price = 0; 
	ID = 0; 
	amountBought = 0;

	nextCart = NULL; 
}


void List::addLine(string t) {
	Line* temp = new Line();
	countLine++; 

	temp->setLID(countLine);
	temp->setTitle(t);
	
	temp->setNextL(NULL);
	if (head == NULL) {
		head = temp;
		tail = temp;
		temp = NULL;
	}
	else {
		tail->setNextL(temp);
		tail = temp;
	}
}

void List::displayLines() {
	Line* temp;
	temp = head;
	
	cout << "- Lines -\n";
	while (temp != NULL) {
		cout << "--------------------\n";
		cout << "[" << temp->getLID() << "] " << temp->getTitle() << endl;

		temp = temp->getNextL();
	}
	cout << "--------------------\n";
}

void List::addCategory(string title, int ID) {
	Category* tempC = new Category();
	countCat++;
	
	tempC->setCatCount(countCat);
	tempC->setIDofCat(ID);
	tempC->setCatTitle(title);

	if (headC == NULL) {
		headC = tempC;
		tailC = tempC;
		tempC = NULL;
	}
	else {
		tailC->setNextC(tempC);
		tailC = tempC;
	}
}

void List::displayCategories(int n) {
	Category* tempC;
	Line* tempL;
	tempC = headC; 
	tempL = head; 
	
	cout << "- Categories -\n";
	for (int i = 0; i < countLine; i++) {
		while (tempC != NULL) {
		if (tempC->getIDofCat() == n) {
			cout << "--------------------\n";
			cout << "[" << tempC->getCatCount() << "] " << tempC->getCatTitle() << endl;
		}
		tempC = tempC->getNextC();
	  }
		tempL = tempL->getNextL();
	}
	cout << "--------------------\n";
}



void List::addProduct(string n, string d, double p, int q, int ID) {
	Product* temp = new Product();
	countProd++; 

	temp->setProdCount(countProd); 
	temp->setIndex(ID);
	temp->setDate(d);
	temp->setName(n);
	temp->setPrice(p);
	temp->setQuantity(q);

	temp->setNextP(NULL);
	if (headP == NULL) {
		headP = temp;
		tailP = temp;
		temp = NULL;
	}
	else {
		tailP->setNextP(temp);
		tailP = temp;
	}

}



void List::displayProducts(int id) {
	Product* tempP;
	Category* tempC;
	tempP = headP;
	tempC = headC;

	cout << "- Products -\n";
	for (int i = 0; i < countCat; i++) {
		while (tempP != NULL) {
			if (tempP->getIndex() == id) {
				cout << "--------------------\n";
				cout << "[" << tempP->getProdCount() << "] " << tempP->getName() << endl;
			}
			tempP = tempP->getNextP();
		}
	}

	cout << "--------------------\n";
}

void List::displayDetails(int n) {
	Product* temp;
	temp = headP;

	while (temp != NULL) {
		if (n == temp->getProdCount()) {

			cout << "-Product details for " << temp->getName() << "-" << endl << "Price: " << temp->getPrice() << endl << "Sell by date: " << temp->getDate() << endl << "Quantity: " << temp->getQuantity() << endl;
			cout << endl << endl; 
		}
		temp = temp->getNextP();
		tailP = temp;
	}
}

void List::addUser(string n, string add, int _ID, int _points) {
	user* temp = new user();
	countUser++;


	temp->setID(countUser);
	temp->setName(n);
	temp->setPoints(_points);
	temp->setAdd(add);
	

	temp->setNextU(NULL);
	if (headU == NULL) {
		headU = temp;
		tailU = temp;
		temp = NULL;
	}
	else {
		tailU->setNextU(temp);
		tailU = temp;
	}
}

bool List::verifyUserName(string nombre) {
	user* temp;
	temp = headU; 

	while (temp != NULL) {
		if (temp->getName() == nombre) {
			cout << "User name verified, welcome back " << temp->getName() << endl; 
			cout << "---Your Details---\n" << "User ID: " << temp->getUID() << endl << "Address: " << temp->getAddress() << endl << "Points: " << temp->getPoints() << endl << endl << endl;

			return true;  
		}
		else {
			temp = temp->getNextU(); 
		}
	}
}

void List::searchProducts(string input) {
	Product* temp; 
	temp = headP; 
	char addQ = 'n'; 

	while (temp != NULL) {
		
		if (temp->getName() == input) {
			
			cout << "Item found: " << temp->getName() << " - " << temp->getPrice() << "$ - Best before: " << temp->getDate() << " - " << temp->getQuantity() << " in stock\n\n";
			//Product found
			break; 
			
		}
		else {
			temp = temp->getNextP(); 
		}
	}
	
}


void List::addToCart(int navigationNum, bool status, int quantityWanted, string n) {
	Product* tempP; 
	Cart* tempC = new Cart();
	user* tempU; 
	string holdName; 
	double holdPrice; 
	int holdQuantity; 
	int holdID; 
	cout << endl; 
	

	tempU = headU; 
	tempP = headP; 

	while (tempU != NULL) {
		
		if (tempU->getName() == n) {
			holdID = tempU->getUID(); 
			
			break; 
		}
		else {
			tempU = tempU->getNextU();
			
		}
	}
	
	while (tempP != NULL) {
		
		
		if (tempP->getProdCount() == navigationNum) {
			
			//Navigate through the products, find the one the user wants to add and store it's data in variables
			holdName = tempP->getName();
			
			holdPrice = tempP->getPrice();
			
			holdQuantity = tempP->getQuantity();
			
			break; 
			
		}
		else {
			tempP=(tempP->getNextP());
			
		}
	}
	

	if (quantityWanted < holdQuantity) {

		//WE have enough to give you 
		
		tempC->setAmt(quantityWanted);

	}
	else {
		cout << "We don't have enough of this product, we can give you " << holdQuantity << " though (I'm gonna give that amount to you anyway)\n";
		tempC->setAmt(holdQuantity);
	}

	
	//Set price to the quantity * price
	tempC->setPrice((tempC->getAmt()) * holdPrice);
	
	tempC->setName(holdName);
	tempC->setStatus(status);
	tempC->setID(holdID);


	
	
	tempC->setNextCart(NULL);
	
	if (headCart == NULL) {
		headCart = tempC;
		tailCart = tempC;
		tempC = NULL;
		
	} 
	else {
		
		tailCart->setNextCart(tempC);
		tailCart = tempC;
	}
	
	

	

	cout << "The product has been added to your cart.\n";

}

void List::displayCart(int _id) {
	Cart* temp;
	temp = headCart;
	

	if (headCart == NULL) 
	{
		cout << "Theres nothing in your cart.\n";
	}
	while (temp != NULL) {
		
		if (_id == temp->getUID()) {

			//cout << "Cart Items for " << temp->getName() << endl;
			cout << "----------------------------------------------\n";
			cout << "-" << temp->getAmt() << " " << temp->getName() << " at $" << temp->getPrice() << "\n";
			cout << endl << endl;
		}
		temp = temp->getNextCart();
		tailCart = temp;
		
	}
	
}

int List::getUserID(string name) {
	user* temp; 
	temp = headU; 

	while (temp != NULL) {
		if (name == temp->getName()) {
			//User found 
			return temp->getUID();
			
		}
		else {
			temp = temp->getNextU(); 
		}
	}
}

double List::calcTotalPrice(int _id) {
	Cart* temp; 
	temp = headCart; 
	double total =0; 

	while (temp != NULL) {
		
		if (_id == temp->getUID()) {
			
			total = total + temp->getPrice(); 
			temp = temp->getNextCart();
		}
		else {
			temp = temp->getNextCart(); 
			
		}

	}
	
	return total; 
}

int List::getProductIDFromName(string name) {
	Product* temp; 
	temp = headP; 

	while (temp != NULL) {
		
		if (name == temp->getName()) {
			return temp->getProdCount(); 
		}
		else {
			temp = temp->getNextP(); 
		}
	}
}

int List::getUserPoints(string name, int money) {
	user* temp; 
	temp = headU; 

	while (temp != NULL) {
		if (name == temp->getName()) {
			temp->setPoints(money + temp->getPoints());
			return temp->getPoints(); 
		}
		else {
			temp = temp->getNextU(); 
		}
	}
}

void List::changeQuantity(string name, int navNum, int quantWanted) {
	Product* temp; 
	temp = headP; 

	while (temp != NULL) {
	
		if (temp->getProdCount() == navNum) {
			cout << "Name: " << temp->getName() << endl; 
			
			temp->setQuantity(temp->getQuantity() - quantWanted);
			
			break; 
		}
		else {
			temp = temp->getNextP(); 
		}
	}
	
}


void List::removeCart(string name) {
	Cart* temp;
	Cart* prev; 
	temp = headCart;
	prev = headCart; 

	while (temp != NULL) {
		if (name == temp->getName()) {
			if (temp == headCart) {
				headCart->setNextCart(NULL);
				headCart = temp->getNextCart(); 
			}
			else if (temp == tailCart){
				tailCart->setNextCart(NULL);
				tailCart = prev; 
			}
			else {
				prev->setNextCart(temp->getNextCart());
				temp->setNextCart(NULL);
			}
		}
		prev = temp; 
		temp = temp->getNextCart();
	}
}



//LINE 
string Line::getTitle() {
	return title;
}

void Line::setTitle(string _title) {
	title = _title;
}

int Line::getLID() {
	return lineID;
}
void Line::setLID(int _id) {
	lineID = _id;
}
//END OF LINE 


//CATEGORY
string Category::getCatTitle() {
	return catTitle;
}
void Category::setCatTitle(string _title) {
	catTitle = _title;
}
Line* Line::getNextL() {
	return next;
}
void Line::setNextL(Line* _next) {
	next = _next;
}
void Category::setIDofCat(int id) {
	lineID = id;
}
int Category::getIDofCat() {
	return lineID;
}

int Category::getCatCount() {
	return HcatCount; 
}
void Category::setCatCount(int _catCount) {
	HcatCount = _catCount;
}
//END OF CATEGORY 


string Product::getName() {
	return name;
}
string Product::getDate() {
	return sellbyDate;
}
double Product::getPrice() {
	return price;
}
int Product::getQuantity() {
	return quantity;
}

void Product::setPrice(double p) {
	price = p;
}
void Product::setQuantity(int q) {
	quantity = q;
}
void Product::setName(string n) {
	name = n;
}
void Product::setDate(string d) {
	sellbyDate = d;
}




Category* Category::getNextC() {
	return nextC;
}

void Category::setNextC(Category* _next) {
	nextC = _next;
}
/*void Category::setPrevC(Category* _prev) {
prev = _prev;
}*/

void Product::setNextP(Product* _next) {
	nextP = _next;
}



Product* Product::getNextP() {
	return nextP;
}

int Product::getIndex() {
	return index;
}

void Product::setIndex(int _d) {
	index = _d;
}

int Product::getProdCount() {
	return countP; 
}

void Product::setProdCount(int _pcount) {
	countP = _pcount; 
}

//USER STUFF 

string user::getName() {
	return name; 
}
void user::setName(string _name) {
	name = _name; 
}

void user::setNextU(user* _nextU) {
	nextU = _nextU; 
}
user* user::getNextU() {
	return nextU; 
}

int user::getUID() {
	return ID; 
}
void user::setID(int _idU) {
	ID = _idU; 
}

int user::getPoints() {
	return points; 
}
void user::setPoints(int _points) {
	points = _points; 
}
string user::getAddress() {
	return addU; 
}
void user::setAdd(string _add) {
	addU = _add; 
}


//CART STUFF 
string Cart::getName() {
	return name; 
}
void Cart::setName(string _name) {
	name = _name; 
}

double Cart::getPrice() {
	return price; 
}
void Cart::setPrice(double _price) {
	price = _price; 
}

int Cart::getAmt() {
	return amountBought;
}
void Cart::setAmt(int _amt) {
	amountBought = _amt; 
}
Cart* Cart::getNextCart() {
	return nextCart; 
}
void Cart::setNextCart(Cart* _next) {
	nextCart = _next; 
}

bool Cart::getStatus() {
	return userStatus;
}
void  Cart::setStatus(bool _status) {
	userStatus = _status; 
}

int  Cart::getUID() {
	return ID; 
}
void  Cart::setID(int _ID) {
	ID = _ID; 
}