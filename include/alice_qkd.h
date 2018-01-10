#ifndef ALICE_QKD_H_
#define ALICE_QKD_H

#include "netxpto.h"
#include "binary_source.h"
#include "m_qam_mapper.h"
#include "discrete_to_continuous_time.h"
#include "pulse_shaper.h"
#include "clock_20171219.h"
#include "sink.h"
#include "super_block_interface.h"
#include "demux_1_2.h"

class AliceQKD : public SuperBlock {
	/* State Variables */

	// #####################################################################################################
	// ################## Internal Signals Declaration and Inicialization ##################################
	// #####################################################################################################

	//Binary S1{ "NUM_A.sgn" };

	TimeDiscreteAmplitudeDiscreteReal S1{ "Alice_1.sgn" };

	TimeDiscreteAmplitudeDiscreteReal S2{ "Alice_2.sgn" };

	TimeContinuousAmplitudeDiscreteReal S3{ "Alice_3.sgn" };

	TimeContinuousAmplitudeDiscreteReal S4{ "Alice_4.sgn" };

	TimeContinuousAmplitudeContinuousReal CLK_A{ "Alice_5.sgn" };

	Binary S5{ "Alice_6.sgn" };

	Binary S6{ "Alice_7.sgn" };

	Binary S7{ "Alice_8.sgn" };

	Binary S8{ "Alice_9.sgn" };

	Binary S9{ "Alice_10.sgn" };

	Binary S10{ "Alice_11.sgn" };

	Binary S11{ "Alice_12.sgn" };

	Binary S12{ "Alice_13.sgn" };

	Binary S13{ "MI_A.sgn" };

	Messages S14{ "C_C_6.sgn" };

	Messages S15{ "C_C_1.sgn" };

	


	// #####################################################################################################
	// ########################### Blocks Declaration and Inicialization ###################################
	// #####################################################################################################

	MQamMapper BA1;

	DiscreteToContinuousTime BA2;

	PulseShaper BA3;

	Sink BA4;

	SuperBlockInterface BA5;

	Demux_1_2 BA6;

	Demux_1_2 BA8;

	Demux_1_2 BA9;

	BinarySource BA11;

	Sink BA12;

	BinarySource BA13;

	Sink BA14;

	Sink BA15;



public:
	/* input parameters*/

	double RateOfPhotons{1e3};
	int StringPhotonsLength{ 12 };

	// Methods
	AliceQKD (vector <Signal*> &inputSignals, vector <Signal*> &outputSignals);

	// Set methods
	void set(int opt);

	void setM(int mValue) { BA1.m = mValue; };
	int const getM(void) { return BA1.m; };

	void setIqAmplitudes(vector<t_iqValues> iqAmplitudesValues) { BA1.m = (t_integer) iqAmplitudesValues.size(); BA1.iqAmplitudes.resize(BA1.m); BA1.iqAmplitudes = iqAmplitudesValues; };
	vector<t_iqValues> const getIqAmplitudes(void) { return BA1.iqAmplitudes; };

	void setNumberOfSamplesPerSymbol(int n) { BA2.setNumberOfSamplesPerSymbol(n); };
	int const getNumberOfSamplesPerSymbol(void) { return BA2.getNumberOfSamplesPerSymbol(); };

	void setRollOffFactor(double rOffFactor) { BA3.setRollOffFactor(rOffFactor); };
	double const getRollOffFactor(void) { return BA3.getRollOffFactor(); };

	void setSeeBeginningOfImpulseResponse(bool sBeginningOfImpulseResponse) { BA3.setSeeBeginningOfImpulseResponse(sBeginningOfImpulseResponse); };
	double const getSeeBeginningOfImpulseResponse(void) { return BA3.getSeeBeginningOfImpulseResponse(); };

	void setPulseShaperFilter(PulseShaperFilter fType) { BA3.setFilterType(fType); };

	void setNumberOfSamples(long int nOfSamples) { BA4.setNumberOfSamples(nOfSamples); BA12.setNumberOfSamples(nOfSamples); BA14.setNumberOfSamples(nOfSamples); BA15.setNumberOfSamples(nOfSamples); };

	void setBitStream(string bitstream) { BA11.setBitStream(bitstream); BA13.setBitStream(bitstream); };

	void setMode(BinarySourceMode m) { BA11.setMode(m); BA13.setMode(m); };

	void setDisplayNumberOfSamples(bool opt) { BA4.setDisplayNumberOfSamples(opt); };


};

#endif
