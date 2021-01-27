/* Standard C++ includes */
//#include <cstdlib>
#include <iostream>

/*
  Include directly the different
  headers from cppconn/ and mysql_driver.h + mysql_util.h
  (and mysql_connection.h). This will reduce your build time!
*/
#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <conio.h>


using namespace std;

// reads in a password without echoing it to the screen
//    WARNING: Does not work in VS2015. 
string myget_passwd()
{
	string passwd;

	for (;;)
	{
		char ch;
		ch = _getch();           // get char WITHIOUT echo!
		if (ch == 13 || ch == 10) // if done ...
			break;           //  stop reading chars!
		cout << '*';  // dump * to screen
		passwd += ch;   // addd char to password
	}
	cin.sync(); // flush anything else in the buffer (remaining newline)
	string dummy;
	getline(cin, dummy);
	cout << endl;  // simulate the enter that the user pressed

	return passwd;
}



int main(void)
{
	// database credentials
	string db_host, db_user, db_password, db_name;

	// get database credentials. 
	cout << "Enter hostname:";
	cin >>  db_host;
	cout << "Enter username:";
	cin >> db_user;
	cout << "Enter password:";
	db_password = myget_passwd();


	db_name = db_user;



	try {
		sql::Driver* driver;
		sql::Connection* con;
		sql::Statement* stmt;
		sql::ResultSet* res;

		// Create a connection */
		driver = get_driver_instance();
		con = driver->connect(db_host, db_user, db_password);
		
		// choose database
		con->setSchema(db_name);

		if (con == NULL)
		{
			cout << "Connection Failed!!" << endl;
			return 1;
		}


		//CREATE TABLES IF THEY DON'T EXIST
		string myQuery = "";
		//cout << "table creation:" << endl;
		myQuery = "create table if not exists Car_T ";
		myQuery += "(vin char(17), manufacturer_abreviation char(3), miles int, dealer char(40), price int, ";
		myQuery += "primary key (vin) )";
		//cout << "Sending query: " << myQuery << endl;
		stmt = con->createStatement();
		stmt->execute(myQuery);
		delete stmt;
		myQuery = "create table if not exists Manufacturer_T ";
		myQuery += "(abreviation char(3), manufacturer char(40), ";
		myQuery += "primary key (abreviation) )";
		//cout << "Sending query: " << myQuery << endl;
		stmt = con->createStatement();
		stmt->execute(myQuery);
		delete stmt;
		myQuery = "create table if not exists Dealer_T ";
		myQuery += "(dealer char(40), zip char(10), pnumber char(10), ";
		myQuery += "primary key (dealer) )";
		//cout << "Sending query: " << myQuery << endl;
		stmt = con->createStatement();
		stmt->execute(myQuery);
		delete stmt;

		string code = "";//codes user inputs
		
		//code decipherers
		char firstcodechar, secondcodechar, thirdcodechar, fourthcodechar, charcounter;
		int firstspace, secondspace, thirdspace, fourthspace, fifthspace, sixthspace;

		//string and ints for insertion
		string vin = "", manufacturer_abreviation = "";
		int miles = 0, price = 0;
		string abreviation = "", manufacturer = "";
		string dealer = "", zip = "", pnumber = "";

		//queries to stop invalid insertion
		string manufQuery = "", dealerQuery = "", vinQuery = "";
		string abrevQuery = "";

		do
		{
			firstcodechar = secondcodechar = thirdcodechar = fourthcodechar = ' ';
			firstspace = secondspace = thirdspace = fourthspace = fifthspace = sixthspace = -1;

			getline(cin, code);//user input code

			for (int i = 0; i < code.length(); i++)//checks first 4 characters
			{
				if (i == 0)
					firstcodechar = code.at(i);
				if (i == 1)
					secondcodechar = code.at(i);
				if (i == 2)
					thirdcodechar = code.at(i);
				if (i == 3)
					fourthcodechar = code.at(i);
			}

			for (int i = 0; i < code.length(); i++)//checks location of first 6 spaces in code string
			{
				charcounter = code.at(i);
				if (charcounter == ' ' && firstspace == -1)
					firstspace = i;
				else if (charcounter == ' ' && secondspace == -1)
					secondspace = i;
				else if (charcounter == ' ' && thirdspace == -1)
					thirdspace = i;
				else if (charcounter == ' ' && fourthspace == -1)
					fourthspace = i;
				else if (charcounter == ' ' && fifthspace == -1)
					fifthspace = i;
			}

			if (firstcodechar == 'a' && secondcodechar == ' ' && thirdcodechar == 'c' && fourthcodechar == ' ')
			{
				//cout << "add car" << endl;
				vin = code.substr(secondspace + 1, thirdspace - secondspace - 1);
				//cout << vin << vin.length() << endl;
				manufacturer_abreviation = code.substr(secondspace + 1, 3);
				//cout << manufacturer_abreviation << manufacturer_abreviation.length() << endl;
				miles = stoi(code.substr(thirdspace + 1, fourthspace - thirdspace - 1));
				//cout << miles << endl;
				dealer = code.substr(fourthspace + 1, fifthspace - fourthspace - 1);
				//cout << dealer << dealer.length() << endl;
				price = stoi(code.substr(fifthspace + 1, sixthspace - fifthspace - 1));
				//cout << price << endl;

				//check if manufacturer exists
				myQuery = "select abreviation from Manufacturer_T where abreviation=\"";
				myQuery += manufacturer_abreviation;
				myQuery += "\"";

				stmt = con->createStatement();
				res = stmt->executeQuery(myQuery);

				manufQuery = "";

				while (res->next()) {
					manufQuery = res->getString("abreviation");
				}

				delete res;
				delete stmt;

				//check if dealer exists
				myQuery = "select dealer from Dealer_T where dealer=\"";
				myQuery += dealer;
				myQuery += "\"";

				stmt = con->createStatement();
				res = stmt->executeQuery(myQuery);

				dealerQuery = "";

				while (res->next()) {
					dealerQuery = res->getString("dealer");
				}

				delete res;
				delete stmt;

				//check if car with vin already exists
				myQuery = "select vin from Car_T where vin=\"";
				myQuery += vin;
				myQuery += "\"";

				stmt = con->createStatement();
				res = stmt->executeQuery(myQuery);

				vinQuery = "";

				while (res->next()) {
					vinQuery = res->getString("vin");
				}

				delete res;
				delete stmt;
				
				//error outputs
				if (manufQuery != manufacturer_abreviation)
					cout << "Error: Manufacturer Does Not Exist" << endl;
				if (dealerQuery != dealer)
					cout << "Error: Dealer Does Not Exist" << endl;
				if (vinQuery == vin)
					cout << "Error: A Car With VIN:" << vin << " Already Exists" << endl;

				if (vin != "" && vinQuery != vin && manufQuery == manufacturer_abreviation && dealerQuery == dealer)//insert car
				{
					myQuery = "insert into Car_T values (\"";
					myQuery += vin;
					myQuery += "\", \"";
					myQuery += manufacturer_abreviation;
					myQuery += "\", ";
					myQuery += to_string(miles);
					myQuery += ", \"";
					myQuery += dealer;
					myQuery += "\", ";
					myQuery += to_string(price);
					myQuery += ")";

					//cout << "Sending:" << myQuery << endl;
					stmt = con->createStatement();
					stmt->execute(myQuery);
					delete stmt;

					cout << "Car Added Successfully" << endl;
				}
				else
					cout << "Car Was Not Added" << endl;
				
			}
			else if (firstcodechar == 'a' && secondcodechar == ' ' && thirdcodechar == 'm' && fourthcodechar == ' ')
			{
				//cout << "add manufacturer" << endl;
				abreviation = code.substr(secondspace + 1, thirdspace - secondspace - 1);
				//cout << abreviation << abreviation.length()<<endl;
				manufacturer = code.substr(thirdspace + 1, fourthspace - thirdspace - 1);
				//cout << manufacturer << manufacturer.length()<<endl;
				
				//check if manufacturer already exists
				myQuery = "select abreviation from Manufacturer_T where abreviation=\"";
				myQuery += abreviation;
				myQuery += "\"";

				stmt = con->createStatement();
				res = stmt->executeQuery(myQuery);

				abrevQuery = "";

				while (res->next()) {
					dealerQuery = res->getString("abreviation");
				}

				delete res;
				delete stmt;

				//error output
				if (dealerQuery == abreviation)
					cout << "Error: A Manufacturer With Abreviation:" << abreviation << " Already Exists" << endl;

				if (abreviation.length() == 3 && dealerQuery != abreviation && abreviation!= "" && manufacturer!= "")//insert manufacturer
				{
					myQuery = "insert into Manufacturer_T values (\"";
					myQuery += abreviation;
					myQuery += "\", \"";
					myQuery += manufacturer;
					myQuery += "\")";

					//cout << "Sending:" << myQuery << endl;
					stmt = con->createStatement();
					stmt->execute(myQuery);
					delete stmt;

					cout << "Manufacturer Added Successfully" << endl;
				}
				else
					cout << "Manufacturer Was Not Added" << endl;
			}
			else if (firstcodechar == 'a' && secondcodechar == ' ' && thirdcodechar == 'd' && fourthcodechar == ' ')
			{
				//cout << "add dealer" << endl;
				dealer = code.substr(secondspace + 1, thirdspace - secondspace - 1);
				//cout << dealer << dealer.length() << endl;
				zip = code.substr(thirdspace + 1, fourthspace - thirdspace - 1);
				//cout << zip << zip.length() << endl;
				pnumber = code.substr(fourthspace + 1, fifthspace - fourthspace - 1);
				//cout << pnumber << pnumber.length() << endl;
				
				//check if dealer exists
				myQuery = "select dealer from Dealer_T where dealer=\"";
				myQuery += dealer;
				myQuery += "\"";

				stmt = con->createStatement();
				res = stmt->executeQuery(myQuery);

				dealerQuery = "";

				while (res->next()) {
					dealerQuery = res->getString("dealer");
				}

				delete res;
				delete stmt;

				//error output
				if (dealerQuery == dealer)
					cout << "Error: A Dealer With Name:" << dealer << " Already Exists" << endl;

				if (dealer != "" && dealerQuery != dealer && zip != "" && pnumber.length() == 10 && pnumber != "")//insert dealer
				{
					myQuery = "insert into Dealer_T values (\"";
					myQuery += dealer;
					myQuery += "\", \"";
					myQuery += zip;
					myQuery += "\", \"";
					myQuery += pnumber;
					myQuery += "\")";

					//cout << "Sending:" << myQuery << endl;
					stmt = con->createStatement();
					stmt->execute(myQuery);
					delete stmt;

					cout << "Dealer Added Successfully" << endl;
				}
				else
					cout << "Dealer Was Not Added" << endl;
			}
			else if (firstcodechar == 'l' && secondcodechar == ' ' && thirdcodechar == 'c' && fourthcodechar == ' ')
			{
				cout << "List Cars: " << endl;
				myQuery = "select * from Car_T order by vin";

				stmt = con->createStatement();
				res = stmt->executeQuery(myQuery);

				while (res->next()) {
					cout << "VIN: ";
					cout << res->getString("vin") << ", Miles: ";
					cout << res->getString("miles") << ", Dealer: ";
					cout << res->getString("dealer") << ", Price: $";
					cout << res->getString("price") << endl;
				}

				delete res;
				delete stmt;
			}
			else if (firstcodechar == 'l' && secondcodechar == ' ' && thirdcodechar == 'd' && fourthcodechar == ' ')
			{
				cout << "List Dealers: " << endl;
				myQuery = "select * from Dealer_T order by zip, dealer";

				stmt = con->createStatement();
				res = stmt->executeQuery(myQuery);

				while (res->next()) {
					cout << "Dealer: ";
					cout << res->getString("dealer") << ", ZIPCODE: ";
					cout << res->getString("zip") << ", Phone Number: ";
					cout << res->getString("pnumber") << endl;
				}

				delete res;
				delete stmt;
			}
			else if (firstcodechar == 'f' && secondcodechar == ' ' && thirdcodechar == 'm' && fourthcodechar == ' ')
			{
				manufacturer = code.substr(secondspace + 1, thirdspace - secondspace - 1);
				cout << "Find Cars Manufacturered By " << manufacturer << ": " << endl;

				myQuery = "select miles, price, Dealer_T.dealer, pnumber from Car_T, Manufacturer_T, Dealer_T where manufacturer=\"";
				myQuery += manufacturer;
				myQuery += "\" and abreviation=manufacturer_abreviation and Dealer_T.dealer=Car_T.dealer order by price desc, miles asc, dealer";

				stmt = con->createStatement();
				res = stmt->executeQuery(myQuery);

				while (res->next()) {
					cout << "Miles: ";
					cout << res->getString("miles") << ", PRICE: $";
					cout << res->getString("price") << ", Dealer: ";
					cout << res->getString("dealer") << ", Phone Number: ";
					cout << res->getString("pnumber") << endl;
				}

				delete res;
				delete stmt;
			}
			else if (firstcodechar == 'f' && secondcodechar == ' ' && thirdcodechar == 'z' && fourthcodechar == ' ')
			{
				zip = code.substr(secondspace + 1, thirdspace - secondspace - 1);
				cout << "Find Cars In ZIPCODE " << zip << ": " << endl;

				myQuery = "select manufacturer, miles, price, Dealer_T.dealer, pnumber from Car_T, Manufacturer_T, Dealer_T where zip=\"";
				myQuery += zip;
				myQuery += "\" and Dealer_T.dealer=Car_T.dealer order by manufacturer asc, price desc, dealer";

				stmt = con->createStatement();
				res = stmt->executeQuery(myQuery);

				while (res->next()) {
					cout << "Manufacturer: ";
					cout << res->getString("manufacturer") << ", Miles: ";
					cout << res->getString("miles") << ", Price: $";
					cout << res->getString("price") << ", Dealer: ";
					cout << res->getString("dealer") << ", Phone Number: ";
					cout << res->getString("pnumber") << endl;
				}

				delete res;
				delete stmt;
			}
			else if (firstcodechar == 'd' && secondcodechar == ' ' && thirdcodechar == 'c' && fourthcodechar == ' ')
			{
				vin = code.substr(secondspace + 1, thirdspace - secondspace - 1);
				cout << "Delete Car: " << vin << endl;

				myQuery = "delete from Car_T where vin=\"";
				myQuery += vin;
				myQuery += "\"";

				//cout << "Sending:" << myQuery << endl;
				stmt = con->createStatement();
				stmt->execute(myQuery);
				delete stmt;
			}
			else if (firstcodechar == 'd' && secondcodechar == ' ' && thirdcodechar == 'd' && fourthcodechar == ' ')
			{
				dealer = code.substr(secondspace + 1, thirdspace - secondspace - 1);
				cout << "Delete Dealer and Cars: " << dealer << endl;

				myQuery = "delete from Dealer_T where dealer=\"";
				myQuery += dealer;
				myQuery += "\"";
				
				//cout << "Sending:" << myQuery << endl;
				stmt = con->createStatement();
				stmt->execute(myQuery);
				delete stmt;

				myQuery = "delete from Car_T where dealer=\"";
				myQuery += dealer;
				myQuery += "\"";

				//cout << "Sending:" << myQuery << endl;
				stmt = con->createStatement();
				stmt->execute(myQuery);
				delete stmt;
			}
			else if (firstcodechar == 's' && code == "s")
			{
				cout << "Summary: " << endl;

				myQuery = "select manufacturer, avg(price) from Car_T, Manufacturer_T where manufacturer_abreviation=abreviation group by manufacturer";

				stmt = con->createStatement();
				res = stmt->executeQuery(myQuery);

				while (res->next()) {
					cout << "Manufacturer: ";
					cout << res->getString("manufacturer") << ", Average Price: $";
					cout << res->getString("avg(price)") << endl;
				}

				delete res;
				delete stmt;
			}
			else if (firstcodechar == 'q' && code == "q")
			{
				cout << "Quitting! Bye!" << endl;
			}
			else
			{
				cout << "Invalid Code Entered" << endl;
			}
		} while (firstcodechar != 'q' || code != "q");

		delete con;
	}
	catch (sql::SQLException& e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}

	cout << endl;

	return 0;
}