/**
 * @file Morse2TxtModuleExt.cpp
 * @brief Morse2TxtModule extension
 *
 * This file is created at "DO bots". It is open-source software and part of "dodedodo". 
 * This software is published under the Apache Licence license (LGPLv3).
 *
 * Copyright © 2013 Marc Hulscher <marc@almende.org>
 *
 * @author                   Marc Hulscher
 * @date                     dec 11, 2013
 * @organisation             DO bots
 * @project                  dodedodo
 */

#include <Morse2TxtModuleExt.h>

#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>				//usleep
#include <vector>

using namespace rur;

//! Replace with your own code
Morse2TxtModuleExt::Morse2TxtModuleExt() {
	mMessage.clear();
	morse.push_back("10111"        ); // a
	morse.push_back("111010101"    ); // b
	morse.push_back("11101011101"  ); // c
	morse.push_back("1110101"      ); // d
	morse.push_back("1"            ); // e
	morse.push_back("101011101"    ); // f
	morse.push_back("111011101"    ); // g
	morse.push_back("1010101"      ); // h
	morse.push_back("101"          ); // i
	morse.push_back("1011101110111"); // j
	morse.push_back("111010111"    ); // k
	morse.push_back("101110101"    ); // l
	morse.push_back("1110111"      ); // m
	morse.push_back("11101"        ); // n
	morse.push_back("11101110111"  ); // o
	morse.push_back("10111011101"  ); // p
	morse.push_back("1110111010111"); // q
	morse.push_back("1011101"      ); // r
	morse.push_back("10101"        ); // s
	morse.push_back("111"          ); // t
	morse.push_back("1010111"      ); // u
	morse.push_back("101010111"    ); // v
	morse.push_back("101110111"    ); // w
	morse.push_back("11101010111"  ); // x
	morse.push_back("1110101110111"); // y
	morse.push_back("11101110101"  ); // z

	morse.push_back("1110111011101110111"  ); // 0
	morse.push_back("10111011101110111"    ); // 1
	morse.push_back("101011101110111"      ); // 2
	morse.push_back("1010101110111"        ); // 3
	morse.push_back("10101010111"          ); // 4
	morse.push_back("101010101"            ); // 5
	morse.push_back("11101010101"          ); // 6
	morse.push_back("1110111010101"        ); // 7
	morse.push_back("111011101110101"      ); // 8
	morse.push_back("11101110111011101"    ); // 9

	morse.push_back("10111010111010111"    ); // .
	morse.push_back("1110111010101110111"  ); // ,
	morse.push_back("101011101110101"      ); // ?
	morse.push_back("1011101110111011101"  ); // '
	morse.push_back("1110101110101110111"  ); // !
	morse.push_back("1110101011101"        ); // /
	morse.push_back("111010111011101"      ); // (
	morse.push_back("1110101110111010111"  ); // )
	morse.push_back("10111010101"          ); // &
	morse.push_back("11101110111010101"    ); // :
	morse.push_back("11101011101011101"    ); // ;
	morse.push_back("1110101010111"        ); // =
	morse.push_back("1011101011101"        ); // +
	morse.push_back("111010101010111"      ); // -
	morse.push_back("10101110111010111"    ); // _
	morse.push_back("101110101011101"      ); // "
	morse.push_back("10101011101010111"    ); // $
	morse.push_back("10111011101011101"    ); // @
	morse.push_back("0");                     // space

	chars.push_back('a' );
	chars.push_back('b' );
	chars.push_back('c' );
	chars.push_back('d' );
	chars.push_back('e' );
	chars.push_back('f' );
	chars.push_back('g' );
	chars.push_back('h' );
	chars.push_back('i' );
	chars.push_back('j' );
	chars.push_back('k' );
	chars.push_back('l' );
	chars.push_back('m' );
	chars.push_back('n' );
	chars.push_back('o' );
	chars.push_back('p' );
	chars.push_back('q' );
	chars.push_back('r' );
	chars.push_back('s' );
	chars.push_back('t' );
	chars.push_back('u' );
	chars.push_back('v' );
	chars.push_back('w' );
	chars.push_back('x' );
	chars.push_back('y' );
	chars.push_back('z' );

	chars.push_back('0' );
	chars.push_back('1' );
	chars.push_back('2' );
	chars.push_back('3' );
	chars.push_back('4' );
	chars.push_back('5' );
	chars.push_back('6' );
	chars.push_back('7' );
	chars.push_back('8' );
	chars.push_back('9' );

	chars.push_back('.' );
	chars.push_back(',' );
	chars.push_back('?' );
	chars.push_back('\'');
	chars.push_back('!' );
	chars.push_back('/' );
	chars.push_back('(' );
	chars.push_back(')' );
	chars.push_back('&' );
	chars.push_back(':' );
	chars.push_back(';' );
	chars.push_back('=' );
	chars.push_back('+' );
	chars.push_back('-' );
	chars.push_back('_' );
	chars.push_back('"' );
	chars.push_back('$' );
	chars.push_back('@' );
	chars.push_back(' ' );
}

//! Replace with your own code
Morse2TxtModuleExt::~Morse2TxtModuleExt() {

}

//! Replace with your own code
void Morse2TxtModuleExt::Tick() {
	std::vector<std::string> words,letters;
	std::string message;
	// read incoming string
	const std::string* read = readMorse(false);
	if (read != NULL && !read->empty()) {
		std::string copy = *read;
		std::cout << "Received string to convert: " << copy << std::endl;
		// split the sentence in individual words
		const std::string wordDelimeter = "0000000";
		words = split(copy,wordDelimeter);
//		std::cout << "there are " << words.size() << " words" << std::endl;
		//split the words into letters & translate
		const std::string letterDelimeter = "000";
		for(unsigned i=0;i<words.size();++i){
			letters.clear();
			letters = split(words[i],letterDelimeter);
//			std::cout << "word: " << i << " has " << letters.size() << " letters" << std::endl;
			for(unsigned j=0;j<letters.size();++j){
//				std::cout << "letter " << j << " is " << letters[j] << " and has length " << letters[j].size() <<
//						" this is converted to: " << convertSingleCharacter(letters[j]) << std::endl;
				message.append(convertSingleCharacter(letters[j]));
			}
			message.append(" ");
		}
		std::cout << "Converted " << copy << " to " << message << std::endl;
		writeTxt(message);
	}
	usleep(10000);
}

//! Replace with your own code
bool Morse2TxtModuleExt::Stop() {
	return false;
}

std::string Morse2TxtModuleExt::convertSingleCharacter(std::string thestring){
	unsigned pos = findPos(thestring);
	if(pos>=morse.size()){
		return "";
	} else {
		//std::cout << pos << " corresponds to " << chars[pos] << std::endl;
		std::stringstream ss;
		ss << chars[pos];
		return ss.str();
//		return std::to_string(chars[pos]);
	}
}

unsigned Morse2TxtModuleExt::findPos(std::string thestring){
	for(unsigned i=0;i<morse.size();++i){
		if(thestring==morse[i]){
			//std::cout << "theString = " << thestring << " and the morse code = " << morse[i] << std::endl;
			return i;
		}
	}
	return morse.size();
}
