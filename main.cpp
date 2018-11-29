//Thomas Kelly, Student Number: 16323455 
#include "header.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
using namespace std;
List a; 


/*Comment : 
In the interest of making it easier for you, I will roughly outline what this code contains, all of which can be verified by running and below/in additional files.

1. Read in products from a txt file, store them in a linked list, each assigned to a parent catergory, which in turn have a parent line.   
2. Either register or sign in as a user, storing Name, ID, points and address in a linked list.
3. Display and Navigate cleanly through lists using index numbers 
4. A search function, whereby user can enter the product name. Product details will be displayed with an option to purchase
5. If a user chooses to add a product to their cart, it will be added to a Cart linked list, and given an ID 
	corresponding to the user who bought it as an attribute
6. At several points the user has the option to proceed to the checkout or display their basket.
7. Based on whether the user is registered or not, they can get a 10% discount on shopping over 30, and also use their points to get discounts. 

There are of course many other functions at work in the list.cpp file. 

To save your time, the only thing I'm aware my code can't do is print a daily report to another file unfortunately.
There are of course some other ways and paths that will cause the code to malfunction, but following the instructions should 
avoid these. 
*/


//THE LCP FUNCTION PRINTS OUT THE LISTS AND CONTAINS SEARCH AND ADD_TO_CART FUNCTIONALITY
void LCP(bool status, string name, int& changeChoice, bool& signOut, double& returnedTotal);

void main() {
	//The value of this integer must be changed to correspond to the number of products in the read file 
	const int numProducts = 27;
	bool userProfile = false;
	int userPoints = 0; 
	double tillTotal = 0, retTotal;

	string soak;
	string title[numProducts];
	string date[numProducts];
	double price[numProducts];
	int quantity[numProducts];
	int ID[numProducts];
	int countt = 0;

	//SET ALL ELEMENTS OF EACH ARRAY TO NULL 
	for (int ii = 0; ii < numProducts; ii++) {
		title[ii] = "VOID";
		date[ii] = "VOID";
		price[ii] = 0;
		quantity[ii] = 0;
		ID[ii] = 0;
	}





	//READ FROM FILE 
	ifstream infile;
	infile.open("readfile.txt");

	for (int i3 = 0; i3 < numProducts; i3++) {
		//'SOAK' string takes the three X's at the start of each new product, which allows the program to recognise when it needs to move onto reading a new product 
		getline(infile, soak);
		getline(infile, title[i3]);
		getline(infile, date[i3]);
		infile >> price[i3];
		infile >> quantity[i3];
		infile >> ID[i3];
	}

	//Add to the lists, corresponding to ID 
	for (int g = 0; g < numProducts; g++) {

		a.addProduct(title[g], date[g], price[g], quantity[g], ID[g]);

	}

	Category();

	//ALL PRODUCTS ARE READ FROM THE TXT FILE, CATEGORIES AND LINES ARE ADDED BELOW
	a.addCategory("Fruit", 1);
	a.addCategory("Vegetables", 1);
	a.addCategory("Meat", 1);

	a.addLine("Fresh Food");

	a.addCategory("Bread", 2);
	a.addCategory("Pastries", 2);
	a.addCategory("Donuts", 2);
	a.addLine("Bakery");

	a.addCategory("Coffee", 3);
	a.addCategory("Soft Drinks", 3);
	a.addCategory("Alcohol", 3);

	a.addLine("Drinks");
	

	//ADD SOME TEST USER NAMES 
	a.addUser("John", "99 Elandsgracht", 222, 0);
	a.addUser("Sarah", "20 Rathgar", 333, 0);
	a.addUser("Adam", "Ashbourne", 444, 0);


	char answ1;
	bool wantToSignOut = false; 
	int choice = 1; 
	string regName, regAdd;
	string userName;

	//Choice determines if the user wants to exit the program 
	while (choice != 2) {
		//HOME
		cout << "| Sign in (s) | Register (r) | Continue unregistered(c) |\n";
		cin >> answ1;

		//SIGN IN PROCESS
		if (answ1 == 's') {
			cout << "Enter your user name: \n";
			cin >> userName;
			if (a.verifyUserName(userName)) {
				userProfile = true;
				LCP(userProfile, userName, choice, wantToSignOut, retTotal);
			}
		}
		//REGISTER PROCESS
		else if (answ1 == 'r') {
			cout << "Please enter your name: \n";
			cin >> regName;
			cout << "Please enter your address: \n";
			cin >> regAdd;
			a.addUser(regName, regAdd, 0, 0);
			//NEED TO GIVE 10% off all products here
			cout << "Thank you for registering " << regName << endl;
			userName = regName;
			userProfile = true;
			LCP(userProfile, userName, choice, wantToSignOut, retTotal);
			cout << endl << endl;

		}
		//NO USER PROFILE
		else if (answ1 == 'c') {
			userProfile = false;
			LCP(userProfile, userName, choice, wantToSignOut, retTotal);
		}

		//CHECKOUT 
		if (wantToSignOut == false) {

			char buy = 'n';
			char useP = 'n';
			int howMP; 
			char remChoice = 'n';
			string nameRem; 
			cout << "Do you want to remove anything from your cart? (y/n)\n";
			cin >> remChoice;
			if (remChoice == 'y') {
				cout << "Enter the name of the product you want to remove\n";
				cin >> nameRem; 
				a.removeCart(nameRem);
			}


			cout << "Your current points are " << a.getUserPoints(userName, retTotal) << ". For every ten points $1 will be deducted. Do you wish to use points?(y/n)\n";
			cin >> useP;
			if (useP == 'y') {
				cout << "How many?\n";
				cin >> howMP;
				if (howMP <= a.getUserPoints(userName, retTotal)) {
					cout << "Cost has been reduced based on points.\n";
					retTotal = retTotal - (howMP / 10);
				}
				else {
					cout << "You have entered an invalid amount of points and will be charged the full amount.\n";
				}
			}
			cout << "Total: $" << retTotal << endl;
			if (userProfile == true && retTotal > 30) {
				cout << "As a registered user and spending over $30, 10% will be taken from this price: \n ";
				retTotal = retTotal - (retTotal)*(0.1);
				cout << "New total: $" << retTotal;
			}
			
			cout << "Do you wish to confirm? (y/n) \n";
			cin >> buy;
			if (buy == 'y') {

				//Increment the shop's profit 
				tillTotal = tillTotal + retTotal;
				//Boost  the points 
				userPoints = a.getUserPoints(userName, retTotal);
		

				cout << "Your points have been increased to: " << userPoints << endl;
				cout << "Thank you for shopping\n";

			}
			else {
				//Doesnt wanna buy them, go back to lines list?? 
				cout << "You will be returned to sign in screen\n";
			}


		}
		else {
			cout << "You will be signed out.\n -----------------------------------\n";
		}
	}
	//Program will close 
}

void LCP(bool status, string name, int& changeChoice, bool& signOut, double& returnedTotal) {
	string answ = "y";
	string searchProd;
	char addQ = 'n';
	int lineNav = 1, catNav = 1, prodNav = 1, addAmt = 0;
	while (answ != "x") {

		a.displayLines();
		cout << endl << endl;
		cout << "-Press '0' to search for a product\n";
		cout << "-Enter 222 to display your basket\n";
		cout << "-Enter 333 to proceed to checkout\n";
		cout << "-Enter '444' to sign out \n";
		cout << "-Enter index to navigate lists \n";
		
		cin >> lineNav;

		if (lineNav == 222) {
			cout << "-------------------------\n";
			a.displayCart(a.getUserID(name));
			cout << "-------------------------\n";
		}
		if (lineNav == 999) {
			signOut = true; 
			break; 
		}
		
		if (lineNav == 333) {
			//Proceed to checkout! 1. Display cartList, corresponding to the current user's ID 
			//Calculate a total cost 
			//Add a confirm function, which adds total cash to till and minuses cart quantity from total quantity 
			cout << "Cart details for " << name << endl;
			a.displayCart(a.getUserID(name));
		   returnedTotal = a.calcTotalPrice(a.getUserID(name));
			
			
			//Stay signed in 
			//Break blocks the program from displaying lines again when we want to proceed to checout 
			break;
		}
		if (lineNav != 0) {
			a.displayCategories(lineNav);
			cout << "Enter an index to navigate the categories, or 0 to return to lines list. \n";
			cin >> catNav;
			if (catNav != 0) {
				a.displayProducts(catNav);
				cout << "Enter the index of the product you wish to view or 0 to return to lines list. \n";
				cin >> prodNav;
				if (prodNav != 0) {
					a.displayDetails(prodNav);

					cout << "Would you like to add this item to your cart? (y/n) \n";
					cin >> addQ;
					if (addQ == 'y') {
						cout << "Please specify quantity: \n";
						cin >> addAmt;
						
						//ADD CART FUNCTION HERE, TAKING IN PARAMETER OF QUANTITY, PRODNAV ASWELL, USE STATUS BOOL TO INDICATE TO THE ADDCART FUNCTION THEY ARE REGISTERED, maybe need ID aswell ***
						a.addToCart(prodNav, status, addAmt, name);
						a.changeQuantity(name, prodNav, addAmt);
						cout << endl;
					}

					cout << "-Press 'x' if you wish to signout.\n -Press 'o' to proceed to the checkout.\n -Press any other key to return to the lines list and continue browsing.\n";
					cin >> answ;
					if (answ == "o") {
						//Proceed to checkout! 1. Display cartList, corresponding to the current user's ID 
						//Calculate a total cost 
						//Add a confirm function, which adds total cash to till and minuses cart quantity from total quantity 
						cout << "---CHECKOUT---\n";
						cout << "-Cart details for " << name << "-"<< endl;
						a.displayCart(a.getUserID(name));
						
						
						//Use a function to calculate total price 
						
						 returnedTotal = a.calcTotalPrice(a.getUserID(name));
						

						//Break blocks the program from displaying lines again when we want to proceed to checout 
						break;
					}
				}
			}
		}
		else if (lineNav == 0) {
			//SEARCH ALL PRODUCTS 
			cout << "Enter the product you want to search for: (please enter exactly as specified in 'readfile.txt')";
			cin >> searchProd;
			cout << endl;

			a.searchProducts(searchProd);
			

			cout << "Would you like to add this item to your cart? (y/n) \n";
			cin >> addQ;
			if (addQ == 'y') {
				cout << "Please specify quantity: \n";
				cin >> addAmt;
				
				//ADD CART FUNCTION HERE, TAKING IN PARAMETER OF QUANTITY, PRODNAV ASWELL, USE STATUS BOOL TO INDICATE TO THE ADDCART FUNCTION THEY ARE REGISTERED, maybe need ID aswell ***
				a.addToCart(a.getProductIDFromName(searchProd), status, addAmt, name);
				
				a.changeQuantity(name, prodNav, addAmt);

				cout << "Item has been added to cart \n"; 
				cout << "-Press 'x' if you wish to signout.\n -Press any other key to return to the lines list and continue browsing.\n";
				cin >> answ;
				if (answ == "x") {
					signOut = true;
					break; 
				}
				cout << endl;
			}
			else {
				cout << "Item will not be added to your cart.\n";
			}
		}
	}
}