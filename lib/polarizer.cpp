#include "netxpto.h"
#include "polarizer.h"


void Polarizer::initialize(void) {
	outputSignals[0]->setFirstValueToBeSaved(inputSignals[1]->getFirstValueToBeSaved());
	outputSignals[0]->setSamplingPeriod(inputSignals[1]->getSamplingPeriod());
	outputSignals[0]->setSamplesPerSymbol(inputSignals[1]->getSamplesPerSymbol());
}

bool Polarizer::runBlock(void) {
	
	int ready1 = inputSignals[0]->ready();
	int ready2 = inputSignals[1]->ready();

	int ready = min(ready1, ready2);

	int space = outputSignals[0]->space();

	int length = min(ready, space);

	if (length <= 0) return false;

	t_complex_xy valueXY;
	t_complex valueX, valueY, valueXout, ValueYout;

	double tetha;

	for (int i = 0; i < length; i++) {
		inputSignals[0]->bufferGet(&tetha);
		inputSignals[1]->bufferGet(&valueXY);

		valueX = valueXY.x;
		valueY = valueXY.y;

		valueXout = cos(-tetha*PI / 180)*valueX + sin(-tetha*PI / 180)*valueY;
		ValueYout = -sin(-tetha*PI / 180)*valueX + cos(-tetha*PI / 180)*valueY;

		valueXY = { valueXout, ValueYout };

		outputSignals[0]->bufferPut(valueXY);
	}

	return true;
}
