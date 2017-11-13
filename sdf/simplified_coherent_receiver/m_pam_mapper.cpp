# include <complex>
# include <fstream>
# include <iostream>
# include <math.h>
# include <stdio.h>
# include <string>
# include <strstream>
# include <vector>
# include <algorithm>

# include "netxpto.h"
//# include "m_qam_mapper.h"
# include "m_pam_mapper.h"			// modification_Romil 


using namespace std;

/*
MQamMapper::MQamMapper(vector<Signal *> &InputSig, vector<Signal *> &OutputSig):Block(InputSig, OutputSig) {

2016-08-03
numberOfInputSignals = InputSig.size();
numberOfOutputSignals = OutputSig.size();

inputSignals = InputSig;
outputSignals = OutputSig;

outputSignals[0]->symbolPeriod = 2 * inputSignals[0]->symbolPeriod;
outputSignals[0]->samplingPeriod = 2 * inputSignals[0]->samplingPeriod;

outputSignals[1]->symbolPeriod = 2 * inputSignals[0]->symbolPeriod;
outputSignals[1]->samplingPeriod = 2 * inputSignals[0]->samplingPeriod;

setM(m);
}*/

void MPamMapper::initialize(void) {																	// WHY? (outputSignals[0] : For inphase data  &&&&  outputSignals[1] : Quadrature data){Make sure}

	outputSignals[0]->symbolPeriod = log2(m) * inputSignals[0]->symbolPeriod;						// Symbol period    = 
	outputSignals[0]->samplingPeriod = log2(m) * inputSignals[0]->samplingPeriod;					// Sampling period  =
	outputSignals[0]->samplesPerSymbol = 1;															// Sample per Symbol
	outputSignals[0]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());			// Set first value to be saved

	/*outputSignals[1]->symbolPeriod = log2(m) * inputSignals[0]->symbolPeriod;
	outputSignals[1]->samplingPeriod = log2(m) * inputSignals[0]->samplingPeriod;
	outputSignals[1]->samplesPerSymbol = 1;
	outputSignals[1]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());*/
	//setM(m);
}

bool MPamMapper::runBlock(void) {																	// :: can be used to define a method{bool runBlock(void)} of the class{MPamMapper} outside the class{MPamMapper}.

	int ready = inputSignals[0]->ready();
	int space = outputSignals[0]->space();															// Added : write "space" inplace of "space1" for MPAM
	//int space1 = outputSignals[0]->space();
	//int space2 = outputSignals[1]->space();

	//int space = (space1 <= space2) ? space1 : space2;												// equivalent to min(space1, space2);
	int length = (ready <= (2 * space)) ? ready : space;											// equivalent to min(ready, 2 * space);

	if (length <= 0) return false;

	int binaryValue;
	int nBinaryValues = (int)log2(m);
	for (int i = 0; i < length; i++) {
		inputSignals[0]->bufferGet(&binaryValue);
		auxSignalNumber = auxSignalNumber + (int)pow(2, nBinaryValues - 1 - auxBinaryValue) * binaryValue;
		auxBinaryValue++;
		if (auxBinaryValue == nBinaryValues) {
			t_real auxI = iqAmplitudes[auxSignalNumber].real();
			//t_real auxQ = iqAmplitudes[auxSignalNumber].imag();
			outputSignals[0]->bufferPut((t_real)auxI);												// Real part (For MPAM consider only this one : Revise it and make sure)
			//outputSignals[1]->bufferPut((t_real)auxQ);												// Imaginary part
			auxBinaryValue = 0;
			auxSignalNumber = 0;
		}
	}

	return true;
}

void MPamMapper::setIqAmplitudes(vector<t_iqValues> iqAmplitudesValues) {
	m = iqAmplitudesValues.size();
	iqAmplitudes.resize(m);
	iqAmplitudes = iqAmplitudesValues;
};

// We can set either iqAmplitudes OR "m"

void MPamMapper::setM(int mValue) {
	m = mValue;

	iqAmplitudes.resize(m);
	switch (m) {
	case 4:
		iqAmplitudes = { { 0.0, 0.0 },{ 1.0, 0.0 },{ 2.0, 0.0 },{ 3.0, 0.0 } };

	case 16:
		iqAmplitudes = { { 0.0, 0.0 },{ 1.0, 0.0 },{ 2.0, 0.0 },{ 3.0, 0.0 },{ 4.0, 0.0 },{ 5.0, 0.0 },{ 6.0, 0.0 },{ 7.0, 0.0 },{ 8.0, 0.0 },{ 9.0, 0.0 },{ 10.0, 0.0 },{ 11.0, 0.0 },{ 12.0, 0.0 },{ 13.0, 0.0 },{ 14.0, 0.0 },{ 15.0, 0.0 } };
	};
};