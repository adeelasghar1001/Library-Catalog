#include "Header.h"

//Item Class===============================================================================
	item::item(){};
	void item::setID(int i){
		id = i;
	}
	void item::setTitle(string n){
		title = n;
	}
	void item::setStatus(int s){
		status = s;
	}
	
	string item::getTitle() const{
		return title;
	}

	int item::getID() const{
		return id;
	}
	int item::getStatus() const{
		return status;
	}


//Book Class===============================================================================
	book::book(string t, string a, int i, int s){
		setTitle(t);
		author = a;
		setID(i);
		setStatus(s);
	}

	string book::getAuthor() const{
		return author;
	}

//Journal Class============================================================================
	journal::journal(string t, int v, int i, int s){
		setTitle(t);
		volume = v;
		setID(i);
		setStatus(s);
	}
	int journal::getJournal() const{
		return volume;
	}

//Magazine Class===========================================================================
	magazine::magazine(string t, int i, int id, int s){
		setTitle(t);
		issue = i;
		setID(id);
		setStatus(s);
	}
	int magazine::getMag() const{
		return issue;
	}