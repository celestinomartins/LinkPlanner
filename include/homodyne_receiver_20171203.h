# ifndef PROGRAM_INCLUDE_HOMODYNE_RECEIVER_H_
# define PROGRAM_INCLUDE_HOMODYNE_RECEIVER_H_

# include "netxpto.h"

# include "optical_hybrid.h"
# include "photodiode_old.h"
# include "subtractor.h"
# include "ideal_amplifier.h"
# include "decoder.h"
# include "local_oscillator.h"
# include "sampler.h"
# include "super_block_interface.h"
# include "pulse_shaper.h"
# include "clock.h"
# include "white_noise.h"
# include "add.h"


// this is a test block for the purpose of beta testing new code
// current code: Building Homodyne superblock.
class HomodyneReceiver : public SuperBlock {

	// #####################################################################################################
	// ################## Internal Signals Declaration and Inicialization ##################################
	// #####################################################################################################

	//OpticalSignal HMD00{ "HMD00.sgn" }; // Input Signal

	OpticalSignal HMD01{ "HMD01.sgn" }; // Local Oscillator

	OpticalSignal HMD02{ "HMD02.sgn" }; // S+L

	OpticalSignal HMD03{ "HMD03.sgn" }; // S-L

	OpticalSignal HMD04{ "HMD04.sgn" }; // S+iL

	OpticalSignal HMD05{ "HMD05.sgn" }; // S-ilL

	TimeContinuousAmplitudeContinuousReal HMD06{ "HMD06.sgn" }; // Subtracted

	TimeContinuousAmplitudeContinuousReal HMD07{ "HMD07.sgn" }; // Substracted

	TimeContinuousAmplitudeContinuousReal HMD08{ "HMD08.sgn" }; // Ideal Amplified

	TimeContinuousAmplitudeContinuousReal HMD09{ "HMD09.sgn" }; // Ideal Amplified

	TimeContinuousAmplitudeContinuousReal HMD10{ "HMD10.sgn" }; // White noise

	TimeContinuousAmplitudeContinuousReal HMD11{ "HMD11.sgn" }; // White noise

	TimeContinuousAmplitudeContinuousReal HMD12{ "HMD12.sgn" }; // Add

	TimeContinuousAmplitudeContinuousReal HMD13{ "HMD13.sgn" }; // Add

	TimeContinuousAmplitudeContinuousReal HMD14{ "HMD14.sgn" }; //Filtered (pulse shaper)

	TimeContinuousAmplitudeContinuousReal HMD15{ "HMD15.sgn" }; //Filtered

	//TimeContinuousAmplitudeContinuousReal HMD16A{ "HMD12A.sgn" }; //Clock

	//TimeContinuousAmplitudeContinuousReal HMD16B{ "HMD12B.sgn" }; //Clock

	TimeDiscreteAmplitudeContinuousReal HMD16{ "HMD16.sgn" }; // Sampled 

	TimeDiscreteAmplitudeContinuousReal HMD17{ "HMD17.sgn" }; // Sampled 

	Binary HMD18{ "HMD18.sgn" }; // recovery Sequence


	// #####################################################################################################
	// ########################### Blocks Declaration and Inicialization ###################################
	// #####################################################################################################

	LocalOscillator B1;

	OpticalHybrid B2;

	Photodiode B3;

	Photodiode B4;

	IdealAmplifier B5;

	IdealAmplifier B6;

	WhiteNoise B7;
	
	WhiteNoise B8;

	Add B9;

	Add B10;

	PulseShaper B11;

	PulseShaper B12;

	//Clock B13A;

	//Clock B13B;

	Sampler B13;

	Sampler B14;
	
	Decoder B15;

	/* State Variables */

	/* Input Parameters */
	double samplingPeriod{ 0.0 };

	double localOscillatorOpticalPower{ 1e-3 };
	double localOscillatorPhase{ 0 };
	double localOscillatorWavelength{ 1550e-9 };

	//int samplesToSkip{ 0 };

	double outputOpticalFrequency{ SPEED_OF_LIGHT / localOscillatorWavelength };

public:

	/* Methods */

	HomodyneReceiver(vector<Signal *> &inputSignal, vector<Signal *> &outputSignal);

	/* Set Methods */

	void setIqAmplitudes(vector<t_iqValues> iqAmplitudesValues) { B15.setIqAmplitudes(iqAmplitudesValues); };
	vector<t_iqValues> const getIqAmplitudes(void) { return B15.getIqAmplitudes(); };

	void setLocalOscillatorSamplingPeriod(double sPeriod) { B1.setSamplingPeriod(sPeriod); };
	void setLocalOscillatorOpticalPower(double opticalPower) { B1.setOpticalPower(opticalPower); };
	void setLocalOscillatorOpticalPower_dBm(double opticalPower_dBm) { B1.setOpticalPower_dBm(opticalPower_dBm); };
	void setLocalOscillatorPhase(double lOscillatorPhase) { B1.setPhase(lOscillatorPhase); };
	void setLocalOscillatorOpticalWavelength(double lOscillatorWavelength) { B1.setWavelength(lOscillatorWavelength); };

	void setSamplingPeriod(double sPeriod) { B1.setSamplingPeriod(sPeriod); };//B13A.setSamplingPeriod(sPeriod); B13B.setSamplingPeriod(sPeriod);
	//};

	void  setResponsivity(t_real Responsivity) { B3.setResponsivity(Responsivity); B4.setResponsivity(Responsivity); };

	void setAmplification(t_real Amplification) { B5.setGain(Amplification); B6.setGain(Amplification); };
	void setNoiseAmplitude(t_real NoiseAmplitude) { B7.setNoiseSpectralDensity(NoiseAmplitude); B8.setNoiseSpectralDensity(NoiseAmplitude);};

	void setImpulseResponseTimeLength(int impResponseTimeLength) { B11.setImpulseResponseTimeLength(impResponseTimeLength); B12.setImpulseResponseTimeLength(impResponseTimeLength); };
	void setFilterType(PulseShaperFilter fType) { B11.setFilterType(fType); B12.setFilterType(fType); };
	void setRollOffFactor(double rOffFactor) { B11.setRollOffFactor(rOffFactor); B12.setRollOffFactor(rOffFactor); };

	//void setClockPeriod(double per) { B13A.setClockPeriod(per); B13B.setClockPeriod(per); };

	void setSamplesToSkip(int sToSkip) { B13.setSamplesToSkip(sToSkip); B14.setSamplesToSkip(sToSkip); };

	void setSamplerOpticalPower_dBm(double optPower_dBm) { B13.setOutputOpticalPower_dBm(optPower_dBm); B14.setOutputOpticalPower_dBm(optPower_dBm); };

};

#endif
