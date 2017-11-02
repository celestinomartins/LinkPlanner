# include "netxpto.h"
# include "clock.h"

# include <algorithm>
# include <complex>
# include <iostream>
# include <fstream>
# include <random>

using namespace std;

void Clock::initialize(void) {

	outputSignals[0]->setSamplingPeriod(samplingPeriod);

	outputSignals[0]->setSamplesPerSymbol((int)round(period / samplingPeriod));

};

bool Clock::runBlock(void) {

	int space = outputSignals[0]->space();

	if (space == 0) return false;

	int numberOfSamplesPerSymbol = (int) outputSignals[0]->getSamplesPerSymbol();

	if (index != 0) {
		for (int i = index; (i < numberOfSamplesPerSymbol) & (space>0); i++) {
			outputSignals[0]->bufferPut(0);
			space--;
			index++;
		};

		index = index % numberOfSamplesPerSymbol;
	};

	for (int k = 0; k < space; k++) {
		if (index == 0) {
			outputSignals[0]->bufferPut((t_real) 1.0);
		}
		else {
			outputSignals[0]->bufferPut((t_real) 0.0);
		}
		index++;
		index = index % numberOfSamplesPerSymbol;
	}

	return true;
};