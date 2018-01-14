# include "netxpto.h"

# include "m_qam_transmitter.h"
# include "homodyne_receiver_20171203.h"
# include "bit_error_rate.h"
# include "sink.h"

int main(){

	// #####################################################################################################
	// #################################### System Input Parameters ########################################
	// #####################################################################################################

	t_integer numberOfBitsGenerated(4000);
	t_integer samplesPerSymbol(16);
	t_real bitPeriod = 1.0 / 50e9;
	t_real rollOffFactor = 0.9;
	t_real signalOutputPower_dBm = 0;
	int numberOfBitsReceived(-1);
	int prbsPatternLength = 7;
	vector<t_iqValues> iqAmplitudeValues = { { 1.0, 1.0 },{ -1.0, 1.0 },{ 1.0, -1.0 },{ -1.0, -1.0 } };
	double symbolPeriod = bitPeriod / samplesPerSymbol;
	t_real localOscillatorPower_dBm = 0;
	t_real localOscillatorPhase = 0;
	t_real responsivity = 1;
	t_real amplification = pow(10, 3);
	t_real noiseAmplitude = pow(10, -6);
	//t_integer samplesToSkip = 0;
	t_integer samplesToSkip = (int)(2 * 8 * samplesPerSymbol);//+ floor(samplesPerSymbol / 2))
	//t_integer samplesToSkip = 2 * 8 * samplesPerSymbol; //+ floor(samplesPerSymbol / 2);
	//8 is the number of samples used by the filter
	t_real confidence = 0.95;
	t_integer midReportSize = 0;
	t_integer bufferLength = 512;

	//double clockPeriod = symbolPeriod;
	//double samplingPeriod = 16;
	
	// #####################################################################################################
	// ########################### Signals Declaration and Inicialization ##################################
	// #####################################################################################################

	Binary S0{ "S0.sgn" };
	S0.setBufferLength(bufferLength);

	OpticalSignal S1("S1.sgn");
	S1.setBufferLength(bufferLength);

	Binary S2{ "S2.sgn" };
	S2.setBufferLength(bufferLength);

	Binary S3{ "S3.sgn" };
	S3.setBufferLength(bufferLength);

	// #####################################################################################################
	// ########################### Blocks Declaration and Inicialization ###################################
	// #####################################################################################################

	MQamTransmitter B1{ vector<Signal*> { }, vector<Signal*> { &S1, &S0 } };
	B1.setNumberOfBits(numberOfBitsGenerated);
	B1.setOutputOpticalPower_dBm(signalOutputPower_dBm);
	B1.setMode(PseudoRandom);
	B1.setBitStream("01");
	B1.setBitPeriod(bitPeriod);
	B1.setPatternLength(prbsPatternLength);
	B1.setIqAmplitudes(iqAmplitudeValues);
	B1.setNumberOfSamplesPerSymbol(samplesPerSymbol);
	B1.setRollOffFactor(rollOffFactor);
	B1.setSaveInternalSignals(true);
	B1.setSeeBeginningOfImpulseResponse(true);

	HomodyneReceiver B2{ vector<Signal*> {&S1}, vector<Signal*> {&S2} };
	B2.setIqAmplitudes(iqAmplitudeValues);
	B2.setLocalOscillatorOpticalPower_dBm(localOscillatorPower_dBm);
	B2.setLocalOscillatorPhase(localOscillatorPhase);
	//B2.setSamplerOpticalPower_dBm(signalOutputPower_dBm);
	//B2.setTransferMatrix(transferMatrix);
	B2.setResponsivity(responsivity);
	B2.setAmplification(amplification);
	B2.setNoiseAmplitude(noiseAmplitude);
	B2.setSamplesToSkip(samplesToSkip);
	//B2.setPosReferenceValue(0);
	//B2.setNegReferenceValue(0);
	B2.setSaveInternalSignals(true);
	//B2.setCutoffFrequency(cutoffFrequency);
	B2.setSamplingPeriod(symbolPeriod/samplesPerSymbol);
	//B2.setClockPeriod(symbolPeriod);

	//With BER measurement
	BitErrorRate B3{ vector<Signal*> { &S2, &S0 }, vector<Signal*> { &S3 } };
	B3.setConfidence(confidence);
	B3.setMidReportSize(midReportSize);

	Sink B4{ vector<Signal*> { &S3 }, vector<Signal*> {} };
	//B4.setNumberOfSamples(-1);
	//B4.setNumberOfSamples(numberOfBitsGenerated*samplesPerSymbol);
	B4.setDisplayNumberOfSamples(true);

	/*MQamTransmitter B1{ vector<Signal*> {}, vector<Signal*> { &S1, &S2 } };
	B1.setNumberOfBits(numberOfBitsGenerated);
	B1.setOutputOpticalPower_dBm(signalOutputPower_dBm);
	//B1.setMode(PseudoRandom);
	B1.setMode(DeterministicAppendZeros);
	B1.setBitStream("010");
	B1.setBitPeriod(bitPeriod);
	B1.setPatternLength(pLength);
	B1.setIqAmplitudes(iqAmplitudeValues);
	B1.setNumberOfSamplesPerSymbol(samplesPerSymbol);
	B1.setRollOffFactor(rollOffFactor);
	B1.setSaveInternalSignals(true);
	B1.setSeeBeginningOfImpulseResponse(true);

	//Without BER measurement
	//Sink B3{ vector<Signal*> { &S0 }, vector<Signal*> {} };
	//B3.setNumberOfSamples(numberOfBitsReceived*samplesPerSymbol);
	//B3.setDisplayNumberOfSamples(true);


	//Sink B4{ vector<Signal*> { &S2 }, vector<Signal*> {} };
	//B4.setNumberOfSamples(numberOfBitsReceived*samplesPerSymbol);
	//B4.setDisplayNumberOfSamples(true);

	Sink B3{ vector<Signal*> { &S2 }, vector<Signal*> {} };
	//B3.setDisplayNumberOfSamples(true);*/

	// #####################################################################################################
	// ########################### System Declaration and Inicialization ###################################
	// #####################################################################################################

	System MainSystem{ vector<Block*> { &B1, &B2, &B3, &B4 } };

	// #####################################################################################################
	// #################################### System Run #####################################################
	// #####################################################################################################
	
	MainSystem.run();

	return 0;

}