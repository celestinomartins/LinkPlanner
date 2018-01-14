#ifndef POLARIZE_H_
#define POLARIZER_H_

#include "netxpto.h"
#include <array>
#include <math.h>

class Polarizer : public Block{

public:
	/* input parameters */
	double samplesPerSymbol{ 0.0 };
	double phase{ 0.0 };
	double samplingPeriod{ 0.0 };

	Polarizer (vector <Signal*> &inputSignals, vector <Signal*> &outputSignals) : Block(inputSignals, outputSignals) {};

	void initialize(void);

	bool runBlock(void);

	void setSamplingPeriod(double per) { samplingPeriod = per; }
	double getSamplingPeriod() { return samplingPeriod; }

	void setSamplesPerSymbol(double samp) { samplesPerSymbol = samp; }
	double getSamplesPerSymbol() { return samplesPerSymbol; }


};
#endif // !POLARIZE_H_

