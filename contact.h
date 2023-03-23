#ifndef CONTACT_H
#define CONTACT_H

#include<iostream>
using namespace std;

class Contact
{
	public:
		string fname;
		string lname;
		string email;
		string primaryPhone;
		string city;
		string country;
		bool isFav;

	// public:
		Contact(string fname, string lname, string email, string primaryPhone, string city, string country, bool isFav)
		:fname(fname), lname(lname), email(email), primaryPhone(primaryPhone), city(city), country(country), isFav(isFav)
		{}
		Contact(){} // # why do I need a no argument contructor?
		
};

#include "contact.cpp"
#endif