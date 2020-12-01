/*
 * literal.h
 *
 *  Created on: Nov 25, 2020
 *      Author: theo
 */

#ifndef HEADERS_LITERAL_H_
#define HEADERS_LITERAL_H_

class Literal{
public:
	Literal();
	Literal(const Literal& l);
	Literal& operator=(const Literal& l){return l;}

};

class LRational : public Literal {
public:
	LRational(const Literal& l);
};

#endif /* HEADERS_LITERAL_H_ */
