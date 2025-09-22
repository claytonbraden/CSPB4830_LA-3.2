#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "functions_to_implement.cpp"
#include <vector>
#include <string>

TEST_CASE ( "Factorials are computed", "[factorial]") // tag
{
  CHECK( Factorial(0) == 1 ); // assertion
  REQUIRE( Factorial(1) == 1 );
  REQUIRE( Factorial(2) == 2 );
  REQUIRE( Factorial(3) == 6 );
  REQUIRE( Factorial(10) == 3628800 );
}

TEST_CASE("incrementing values in integer vector", "[addN]")
{
	std::vector<int> v{1,2,3,5,6,7,8,10};

	SECTION("checking with +ve n")
  {
		int n=5;
		std::vector<int> res = AddN(v, n);
		srand(time(NULL));
		int random = rand()%v.size();
		REQUIRE(v.size() == res.size());
		REQUIRE( res[0] == 6 );
		REQUIRE( res[v.size()-1] == 15 );
		REQUIRE(res[random] == v[random]+n);
	}
	SECTION("checking with -ve n")
  {
		int n=-5;
		std::vector<int> res = AddN(v, n);
		srand(time(NULL));
		int random = rand()%v.size();
		REQUIRE(v.size() == res.size());
		REQUIRE( res[0] == -4 );
		REQUIRE( res[v.size()-1] == 5 );
		REQUIRE(res[random] == v[random]+n);
	}

}


TEST_CASE("Splitting single string into vector of string", "[Split]")
{
	std::vector<std::string> s{};
	std::string seperator = ";";
	std::string wordToSplit_1 = "I;like;to;go;to;the;beach";
	std::string wordToSplit_2 = "Numbers/symbols;should;be;included;123456789@#$%&*()...";
	std::string wordToSplit_3 = "Null strings;should;be;included;;";

	SECTION("checking basic string")
  {
		s = Split(wordToSplit_1, seperator);
		REQUIRE(s == std::vector<std::string>{"I","like","to","go","to","the","beach"});
	}
	SECTION("checking with numbers/symbols")
  {
		s = Split(wordToSplit_2, seperator);
		REQUIRE(s == std::vector<std::string>{"Numbers/symbols","should","be","included","123456789@#$%&*()..."});
	}
	SECTION("checking with seperator at beginning/end and consecutive, also white space")
	  {
		s = Split(wordToSplit_3, seperator);
		REQUIRE(s == std::vector<std::string>{"Null strings","should","be","included",""});
	}

}

TEST_CASE("Removing substrings s2 from word s1", "[RemoveAllSubstrings]")
{
	std::string s1_1 = "Words";
	std::string s2_1 = "Wordsy";

	std::string s1_2 = "Wordsy";
	std::string s2_2 = "Words";

	std::string s1_3 = "Remove all lowercase a's, leave uppercase A's";
	std::string s2_3 = "a";
	
	std::string s1_4 = "Remove all dollar sign symbols there are three here-->$$$";
	std::string s2_4 = "$";

	std::string s1_5 = "Remove all instances of the phrase --> Peter Piper <--";
	std::string s2_5 = "Peter Piper";

	std::string s;
	SECTION("checking basic string where s2 length > s1, should return s1")
  {
		s = RemoveAllSubstrings(s1_1,s2_1);
		REQUIRE(s == s1_1);
	}

	SECTION("checking single word string, only y should be left")
  {
		s = RemoveAllSubstrings(s1_2,s2_2);
		REQUIRE(s == "y");
	}
	SECTION("Removing all lowercase a's from string")
  {
		s = RemoveAllSubstrings(s1_3,s2_3);
		REQUIRE(s == "Remove ll lowercse 's, leve uppercse A's");
	}
	SECTION("Removing single symbol $ at end of string")
	  {
		s = RemoveAllSubstrings(s1_4,s2_4);
		REQUIRE(s == "Remove all dollar sign symbols there are three here-->");
	}
	SECTION("Checking multiworded string against multiworded string")
	  {
		s = RemoveAllSubstrings(s1_5,s2_5);
		REQUIRE(s == "Remove all instances of the phrase -->  <--");
	}
}

TEST_CASE("Dividing integer by 2 and returning the last number that is not divisable by", "[RemoveTwos]")
{


	int checkValue;
	SECTION("Testing -3 to 3 (should return the original value)")
  {
		for(int i = -3; i<4; i++) {
			checkValue = RemoveTwos(i);
			REQUIRE(checkValue == i);
		}
	}

	SECTION("checking 52, should return 13")
  {
		checkValue = RemoveTwos(52);
		REQUIRE(checkValue == 13);
	}
	SECTION("checking 26, should return 13")
  {
		checkValue = RemoveTwos(26);
		REQUIRE(checkValue == 13);
	}
	SECTION("checking 7, should return 7")
  {
		checkValue = RemoveTwos(7);
		REQUIRE(checkValue == 7);
	}
	SECTION("checking 16, should return 1")
  {
		checkValue = RemoveTwos(16);
		REQUIRE(checkValue == 1);
	}
}

TEST_CASE("Taking string vector and using glue string to make one string", "[Join]")
{

	std::vector<std::string> join_string_vector;
	std::string glue_string;
	std::string result_string;
	SECTION("Testing periods in between each word")
  {
		join_string_vector= {"Adding","periods","in","between","each","word"};
		glue_string = ".";
		result_string = Join(join_string_vector, glue_string);
		REQUIRE(result_string == "Adding.periods.in.between.each.word"); 
		
	}
		SECTION("Testing spaces in between each word")
  {
		join_string_vector = {"Adding","spaces","in","between","each","word"};
		glue_string = " ";
		result_string = Join(join_string_vector, glue_string);
		REQUIRE(result_string == "Adding spaces in between each word"); 
	}

	SECTION("Testing numbers in between each word")
  {
		join_string_vector = {"Adding","numbers","in","between","each","word"};
		glue_string = "123";
		result_string = Join(join_string_vector, glue_string);
		REQUIRE(result_string == "Adding123numbers123in123between123each123word"); 
	}
}