// CSC305 Project1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

using namespace std;
#include <iostream>
#include <string>
#include<fstream>

//returns bool value for if the manufacturer exists in data when passed abreviation/manufacturer
bool manufacturerExists(string abrev1, string manuf1);

//returns bool value for if the dealer exists in data when passed dealer name/zipcode/phonenumber
bool dealerExists(string dealer1, int zip1, string phone_number1);

//returns bool value for if the manufacturer and dealer exists when passed VIN/dealer
bool manufacturerAndDealerExist(string vin, string dealer1);

//lists cars of a manufacturer from data when given manufacturer
void findManufacturer(string manufacturer1);

//lists cars in a zipcode from data when given the zipcode
void findZipcode(int zip1);

int main()
{
	//constant variables
	const int PHONE_NUM_LEN = 10;
	const int MANUF_ABREV_LEN = 3;
	const int VIN_LEN = 17;
	
	char menu_select = '\0';//menu selector
	
	string manufacturer = "", dealer = "";
	
	fstream file;
	
	int zipcode = 0, car_miles = 0, car_price = 0;
	
	string manuf_abrev = "";
	
	string phone_number = "";
	
	string vin_number = "";

	//greeting
	cout << "Hello. Welcome to the car database. Type 'h' for help." << endl;

	//menu loop
	do
	{
		cin >> menu_select;
		switch (menu_select)
		{
		case 'a'://add
			cin >> menu_select;
			switch(menu_select)
			{
			case 'c'://car
				cin >> vin_number;
				vin_number = vin_number.substr(0, VIN_LEN);//set vin length
				cin >> car_miles;
				cin >> dealer;
				cin >> car_price;
				if (!manufacturerAndDealerExist(vin_number, dealer))
					cout << "Error Adding Car" << endl;
				else
				{
					file.open("cars.txt", fstream::app);
					file << vin_number << " " << car_miles << " " << dealer << " " << car_price << endl;
					file.close();
					cout << "Car Added Successfully" << endl;
				}
				//cout << "add car" << endl;
				break;
			case 'm'://manufacturer
				cin >> manuf_abrev;
				manuf_abrev = manuf_abrev.substr(0, VIN_LEN);//set manufucturer abreviation length
				cin >> manufacturer;
				if (manufacturerExists(manuf_abrev, manufacturer))
					cout << "Manufacturer already exists" << endl;
				else
				{
					file.open("manufacturers.txt", fstream::app);
					file << manuf_abrev << " " << manufacturer << endl;
					file.close();
					cout << "Manufactuer Added Successfully" << endl;
				}
				//cout << "add manufacturer" << endl;
				break;
			case 'd'://dealer
				cin >> dealer;
				cin >> zipcode;
				cin >> phone_number;
				phone_number = phone_number.substr(0, PHONE_NUM_LEN);//set phone number length
				if (dealerExists(dealer, zipcode, phone_number))
					cout << "Dealer already exists" << endl;
				else
				{
					file.open("dealers.txt", fstream::app);
					file << dealer << " " << zipcode << " " << phone_number << endl;
					file.close();
					cout << "Dealer Added Successfully" << endl;
				}
				//cout << "add dealer" << endl;
				break;
			default:
				cout << "Error[1]" << endl;
			}
			break;
		case 'l'://list
			cin >> menu_select;
			switch (menu_select)
			{
			case 'c'://cars
				file.open("cars.txt");
				if (!file)
					cout << "No Cars" << endl;
				file >> vin_number >> car_miles >> dealer >> car_price;
				while (!file.eof() && file)
				{
					cout << vin_number << " " << car_miles << " " << dealer << " " << car_price << endl;
					file >> vin_number >> car_miles >> dealer >> car_price;
				}
				file.close();
				//cout << "list cars" << endl;
				break;
			case 'd'://dealers
				file.open("dealers.txt");
				if (!file)
					cout << "No Dealers" << endl;
				file >> dealer >> zipcode >> phone_number;
				while (!file.eof() && file)
				{
					cout << dealer << " " << zipcode << " " << phone_number << endl;
					file >> dealer >> zipcode >> phone_number;
				}
				file.close();
				//cout << "list dealers" << endl;
				break;
			default:
				cout << "Error[2]" << endl;
			}
			break;
		case 'f'://find
			cin >> menu_select;
			switch (menu_select)
			{
			case 'm'://manufacturers
				cin >> manufacturer;
				findManufacturer(manufacturer);
				//cout << "find manufacturer" << endl;
				break;
			case 'z'://zipcodes
				cin >> zipcode;
				findZipcode(zipcode);
				//cout << "find zipcode" << endl;
				break;
			default:
				cout << "Error[3]" << endl;
			}
			break;
		case 'h'://help
			cout << "command list:" << endl;
			cout << "add car: a c [VIN] [CAR MILES] [DEALER] [CAR PRICE]" << endl;
			cout << "add manufacturer: a m [ABBREVIATION] [MANUFACTURER]" << endl;
			cout << "add dealer: a d [DEALER] [ZIPCODE] [PHONE NUMBER]" << endl;
			cout << "list cars: l c" << endl;
			cout << "list dealers: l d" << endl;
			cout << "find manufacturers: f m [MANUFACTURER]" << endl;
			cout << "find zipcode: f m [ZIPCODE]" << endl;
			cout << "quit: q" << endl;
			break;
		case 'q'://quit
			cout << "Thank you! Goodbye!" << endl;
			break;
		default:
			cout << "Error[4]" << endl;
		}
		cin.ignore();
	} while (menu_select!='q');
	return 0;
}

bool manufacturerExists(string abrev1, string manuf1)
{
	bool exists = false;
	string abrev2 = "", manuf2 = "";
	ifstream file;
	file.open("manufacturers.txt");
	while (!file.eof()&&file)
	{
		file >> abrev2 >> manuf2;
		if (abrev1 == abrev2 || manuf1 == manuf2)
			exists = true;
	}
	file.close();
	return exists;
}

bool dealerExists(string dealer1, int zip1, string phone_number1)
{
	bool exists = false;
	string dealer2, phone_number2;
	int zip2;
	ifstream file;
	file.open("dealers.txt");
	while (!file.eof() && file)
	{
		file >> dealer2 >> zip2 >> phone_number2;
		if (dealer1 == dealer2)
			exists = true;
	}
	file.close();
	return exists;
}

bool manufacturerAndDealerExist(string vin, string dealer1)
{
	bool manuf_exists = false;
	bool dealer_exists = false;
	string manuf1 = vin.substr(0, 3);
	string manuf2, dealer2;
	string skip;
	ifstream file;
	file.open("manufacturers.txt");
	while (!file.eof() && file)
	{
		file >> manuf2 >> skip;
		if (manuf1 == manuf2)
		{
			//cout << "the manufacturer exists" << endl;
			manuf_exists = true;
		}
		/*else
			cout << "Could not find manufacturer" << endl;*/
	}
	file.close();
	file.open("dealers.txt");
	while (!file.eof() && file)
	{
		file >> dealer2 >> skip >> skip;
		if (dealer1 == dealer2)
		{
			//cout << "the dealer exists" << endl;
			dealer_exists = true;
		}
		/*else
			cout << "Could not find dealer" << endl;*/
	}
	file.close();
	if (!manuf_exists)
		cout << "This Manufacturer does not exist" << endl;
	if (!dealer_exists)
		cout << "This Dealer does not exist" << endl;
	return (manuf_exists&&dealer_exists);
}

void findManufacturer(string manufacturer1)
{
	ifstream file1, file2;
	string manuf_abrev = "";
	string manufacturer2 = "";
	string vin = "", dealer1 = "", dealer2 = "", phone_number = "";
	int car_miles = 0, car_price = 0, zip = 0;

	file1.open("manufacturers.txt");
	while (!file1.eof() && file1 && manufacturer1!=manufacturer2)
	{
		file1 >> manuf_abrev >> manufacturer2;
	}
	file1.close();
	file1.open("cars.txt");
	file1 >> vin >> car_miles >> dealer1 >> car_price;
	while (!file1.eof() && file1)
	{
		if (manuf_abrev == vin.substr(0, 3))
		{
			file2.open("dealers.txt");
			file2 >> dealer2 >> zip >> phone_number;
			while (!file2.eof() && file2 && dealer1!=dealer2)
			{
				file2 >> dealer2 >> zip >> phone_number;
			}
			file2.close();
			cout << manufacturer1 << ":" << car_miles << " miles, $" << car_price << ": " << dealer1;
			cout << "[(" << phone_number.substr(0, 3) << ")" << phone_number.substr(3, 3) << "-" << phone_number.substr(6, 4) << "]" << endl;
		}
		file1 >> vin >> car_miles >> dealer1 >> car_price;
	}
	file1.close();
	return;
}

void findZipcode(int zip1)
{
	string dealer1 = "", dealer2 = "", phone_number = "", vin = "", manuf_abrev = "", manufacturer = "";
	int zip2 = 0, car_miles = 0, car_price = 0;
	ifstream file_d, file_c, file_m;
	file_d.open("dealers.txt");
	file_d >> dealer1 >> zip2 >> phone_number;
	while (!file_d.eof() && file_d)
	{
		if (zip1 == zip2)
		{
			file_c.open("cars.txt");
			file_c >> vin >> car_miles >> dealer2 >> car_price;
			while (!file_c.eof() && file_c)
			{
				if (dealer1 == dealer2)
				{
					file_m.open("manufacturers.txt");
					file_m >> manuf_abrev >> manufacturer;
					while (!file_m.eof() && file_m)
					{
						if (manuf_abrev == vin.substr(0, 3))
						{
							cout << manufacturer << ":" << car_miles << " miles, $" << car_price << ": " << dealer1;
							cout << "[(" << phone_number.substr(0, 3) << ")" << phone_number.substr(3, 3) << "-" << phone_number.substr(6, 4) << "]" << endl;
						}
						file_m >> manuf_abrev >> manufacturer;
					}
					file_m.close();
				}
				file_c >> vin >> car_miles >> dealer2 >> car_price;
			}
			file_c.close();
		}
		file_d >> dealer1 >> zip2 >> phone_number;
	}
	file_d.close();
	return;
}
