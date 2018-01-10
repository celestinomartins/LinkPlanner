#ifndef BOB_QKD_H_
#define BOB_QKD_H

#include "netxpto.h"


class BobQKD : public Block {
	/* input parameters*/


public:
	BobQKD(vector <Signal*> &inputSignals, vector <Signal*> &outputSignals) : Block(inputSignals, outputSignals) {};

	void initialize(void);

	bool runBlock(void);

};

#endif
