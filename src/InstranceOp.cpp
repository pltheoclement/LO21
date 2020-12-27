/*
 * InstranceOp.cpp
 *
 *  Created on: Dec 26, 2020
 *      Author: theo
 */
#include <iostream>
#include <string>
#include <map>

#include "../include/operator.h"
#include "../include/unaryOperator.h"
#include "../include/binaryOperator.h"
#include "../include/computer.h"
#include "../include/literal.h"
/*

void creationOperators(){
	Clear::get();

	NegInt negInt;
	NegReal negReal;
	NegRational negRational;

	Not::get();

	Dup::get();

	Drop::get();

	Swap::get();

	AddIntInt addIntInt;
	AddIntReal addIntReal;
	AddRealInt addRealInt;
	AddIntRational addIntRational;
	AddRationalInt addRationalInt;
	AddRationalRational addRationalRational;
	AddRealReal addRealReal;
	AddRealRational addRealRational;
	AddRationalReal addRationalReal;

	MulIntInt mulIntInt;
	MulIntReal mulIntReal;
	MulRealInt mulRealInt;
	MulIntRational mulIntRational;
	MulRationalInt mulRationalInt;
	MulRationalRational mulRationalRational;
	MulRealReal mulRealReal;
	MulRealRational mulRealRational;
	MulRationalReal mulRationalReal;

	SubIntInt subIntInt;
	SubIntReal subIntReal;
	SubRealInt subRealInt;
	SubIntRational subIntRational;
	SubRationalInt subRationalInt;
	SubRationalRational subRationalRational;
	SubRealReal subRealReal;
	SubRealRational subRealRational;
	SubRationalReal subRationalReal;

	DivIntInt divIntInt;
	DivIntReal divIntReal;
	DivRealInt divRealInt;
	DivIntRational divIntRational;
	DivRationalInt divRationalInt;
	DivRationalRational divRationalRational;
	DivRealReal divRealReal;
	DivRealRational divRealRational;
	DivRationalReal divRationalReal;

	ModIntInt modIntInt;

	DivEIntInt diveIntInt;

	EquIntInt equIntInt;
	EquIntReal equIntReal;
	EquRealInt equRealInt;
	EquIntRational equIntRational;
	EquRationalInt equRationalInt;
	EquRationalRational equRationalRational;
	EquRealReal equRealReal;
	EquRealRational equRealRational;
	EquRationalReal equRationalReal;

	DifIntInt difIntInt;
	DifIntReal difIntReal;
	DifRealInt difRealInt;
	DifIntRational difIntRational;
	DifRationalInt difRationalInt;
	DifRationalRational difRationalRational;
	DifRealReal difRealReal;
	DifRealRational difRealRational;
	DifRationalReal difRationalReal;

	InfEquIntInt infEquIntInt;
	InfEquIntReal infEquIntReal;
	InfEquRealInt infEquRealInt;
	InfEquIntRational infEquIntRational;
	InfEquRationalInt infEquRationalInt;
	InfEquRationalRational infEquRationalRational;
	InfEquRealReal infEquRealReal;
	InfEquRealRational infEquRealRational;
	InfEquRationalReal infEquRationalReal;

	InfIntInt infIntInt;
	InfIntReal infIntReal;
	InfRealInt infRealInt;
	InfIntRational infIntRational;
	InfRationalInt infRationalInt;
	InfRationalRational infRationalRational;
	InfRealReal infRealReal;
	InfRealRational infRealRational;
	InfRationalReal infRationalReal;

	SupEquIntInt supEquIntInt;
	SupEquIntReal supEquIntReal;
	SupEquRealInt supEquRealInt;
	SupEquIntRational supEquIntRational;
	SupEquRationalInt supEquRationalInt;
	SupEquRationalRational supEquRationalRational;
	SupEquRealReal supEquRealReal;
	SupEquRealRational supEquRealRational;
	SupEquRationalReal supEquRationalReal;

	SupIntInt supIntInt;
	SupIntReal supIntReal;
	SupRealInt supRealInt;
	SupIntRational supIntRational;
	SupRationalInt supRationalInt;
	SupRationalRational supRationalRational;
	SupRealReal supRealReal;
	SupRealRational supRealRational;
	SupRationalReal supRationalReal;

	And::get();

	Or::get();

	Swap::get();
}
*/
void destructionOperators(){
	Clear::free();
	Neg::free();
	Not::get();
	Dup::get();
	Drop::get();
	Swap::get();
	Add::free();
	Mul::free();
	Sub::free();
	Div::free();
	Mod::free();;
	DivE::free();
	Equ::free();
	Dif::free();
	InfEqu::free();
	Inf::free();
	SupEqu::free();
	Sup::free();
	And::free();
	Or::free();
	Swap::free();

	Operator::freeInstance();
}





















