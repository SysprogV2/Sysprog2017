#include "../includes/Symboltable.h"
#include "gtest/gtest.h"

//							NOTICE
// following primitive methods are not tested since they
// merely retrieve values from the existing tables/arrays:
//

TEST(symboltable, insert) {
	// setup
	Symboltable* symboltable = new Symboltable();

	// #1
	SymtabEntry *s1 = symboltable->insert("string1", 7);
	EXPECT_TRUE(s1 != NULL);


	// #2
	SymtabEntry *s2 = symboltable->insert("string2", 7);
	EXPECT_TRUE(s2 != NULL);

	// #3
	SymtabEntry *s3 = nullptr;
	EXPECT_TRUE(s3 == NULL);
}

TEST(symboltable, lookup) {
	// setup
	Symboltable* symboltable = new Symboltable();
	EXPECT_TRUE(symboltable != nullptr);
	EXPECT_TRUE(symboltable->insert("abc", 3) != nullptr);
	EXPECT_TRUE(symboltable->insert("veryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryverylongstring", 114) != nullptr);

	// #1
	Information* info1 = symboltable->lookup("string1");
	EXPECT_TRUE(info1 == NULL);

	// #2
	Information* info2 = symboltable->lookup("abc");
	EXPECT_TRUE(info2 != NULL);
	EXPECT_TRUE(info2->getLexem() != NULL);
	EXPECT_FALSE(strcmp(info2->getLexem(), "abc") );

	// #3
	Information* info3 = symboltable->lookup("veryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryverylongstring");
	EXPECT_TRUE(info3 != NULL);
	EXPECT_TRUE(info3->getLexem() != NULL);
	EXPECT_FALSE(strcmp(info3->getLexem(), "veryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryverylongstring") );
}

// TODO: StringTab Test here? Better move to TestStringTab
TEST(stringtable, insert) {
	// setup
	StringTab * st = new StringTab();

	const char *charPtr1 = "a";
	int charPtrLen1 = 10;
	const char *charPtr2 = "veryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryverylongstring";
	int charPtrLen2 = 114;
	const char *charPtr3 = "veryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryverylongstringveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryverylongstringveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryverylongstringveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryverylongstringveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryveryverylongstring";
	int charPtrLen3 = 570;

	// #1
	char *entry1 = st->insert(charPtr1, charPtrLen1);
	EXPECT_TRUE(charPtr1 != entry1);
	EXPECT_FALSE(strcmp(charPtr1, entry1) );

	// #2
	char *entry2 = st->insert(charPtr2, charPtrLen2);
	EXPECT_TRUE(charPtr2 != entry2);
	EXPECT_FALSE(strcmp(charPtr2, entry2) );

	// #3
	char *entry3 = st->insert(charPtr3, charPtrLen3);
	EXPECT_TRUE(charPtr3 != entry3);
	EXPECT_FALSE(strcmp(charPtr3, entry3) );
}