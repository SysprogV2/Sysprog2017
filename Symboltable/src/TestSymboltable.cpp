#define CATCH_CONFIG_MAIN
#include "../includes/Symboltable.h"
#include "../includes/SymtabEntry.h"
#include "../includes/StringTab.h"
#include <iostream>
#include "../../catch.hpp"
#include <string.h>

//							NOTICE
// following primitive methods are not tested since they 
// merely retrieve values from the existing tables/arrays:
// 

TEST_CASE( "Symboltable.CPP TEST -> insert()", "[char]") {
	// setup
	Symboltable* symboltable = new Symboltable();
	
	// #1
	SymtabEntry *s1 = symboltable->insert("string1", 7);
	REQUIRE(s1 != NULL);
	
	
	// #2
	SymtabEntry *s2 = symboltable->insert("string2", 7);
	REQUIRE(s2 != NULL);
	
	// #3
	SymtabEntry *s3 = nullptr;
	REQUIRE(s3 == NULL);
}

TEST_CASE( "Symboltable.CPP TEST -> lookup()", "[char]") {
	// setup
	Symboltable* symboltable = new Symboltable();
	SymtabEntry *s1 = symboltable->insert("abc", 3);
	SymtabEntry *s2 = symboltable->insert("veryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryverylongstring", 114);
	
	// #1
	Information* info1 = symboltable->lookup("string1");
	REQUIRE(info1 == NULL);
	
	// #2
	Information* info2 = symboltable->lookup("abc");
	REQUIRE(info2 != NULL);
	REQUIRE(info2->getLexem() != NULL);
	REQUIRE( !strcmp(info2->getLexem(), "abc") );
	
	// #3
	Information* info3 = symboltable->lookup("veryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryverylongstring");
	REQUIRE(info3 != NULL);
	REQUIRE(info3->getLexem() != NULL);
	REQUIRE( !strcmp(info3->getLexem(), "veryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryverylongstring") );
}

TEST_CASE( "StringTab.CPP TEST -> insert()", "[char]") {
	// setup
	StringTab * st = new StringTab();
	
	char *charPtr1 = "a";
	int charPtrLen1 = 10;
	char *charPtr2 = "veryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryverylongstring";
	int charPtrLen2 = 114;
	char *charPtr3 = "veryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryverylongstringveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryverylongstringveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryverylongstringveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryverylongstringveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryverylongstring";
	int charPtrLen3 = 570;

	// #1
	char *entry1 = st->insert(charPtr1, charPtrLen1);
	REQUIRE(charPtr1 != entry1);
	REQUIRE( !strcmp(charPtr1, entry1) );
	
	// #2
	char *entry2 = st->insert(charPtr2, charPtrLen2);
	REQUIRE(charPtr2 != entry2);
	REQUIRE( !strcmp(charPtr2, entry2) );
	
	// #3
	char *entry3 = st->insert(charPtr3, charPtrLen3);
	REQUIRE(charPtr3 != entry3);
	REQUIRE( !strcmp(charPtr3, entry3) );
}