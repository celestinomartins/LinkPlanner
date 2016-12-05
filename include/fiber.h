# ifndef PROGRAM_INCLUDE_FIBER_H_
# define PROGRAM_INCLUDE_FIBER_H_
# include "netxpto.h"

// Implements an Optical Fiber

class Fiber : public Block {

	/* State Variables */

	t_complex* transferFunction;

	t_complex* impulseResponse;

public:
	/* Input Parameters */
	t_real attenuationCoeficient{ 4.6052e-05 }; //m^(-1) correspond to 0.2 dB/km

	t_real dispersionCoeficient{ -10.0 }; // valor de coeficiente de dispersao em ps/nm/km D=-(2*pi*c*B2)/(lambda^2)

	t_real fiberLength{ 10000.0 }; // comprimento de fibra em metros
	
	t_real CDO{ 1550e-9 }; // comprimento de onda de feixe em metros

	t_integer impulseResponseLength{ 256 };

	/* Methods */

	Fiber(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig) {}; 

	void initialize(void); //

	bool runBlock(void); //

	void setAttenuationCoeficient(t_real alpha) { attenuationCoeficient = alpha; } 

	t_real getAttenuationCoeficient() { return attenuationCoeficient; }

	void setDispersionCoeficient(t_real beta2) { dispersionCoeficient = beta2; }

	t_real getDispersionCoeficient() { return dispersionCoeficient; }
};



# endif // PROGRAM_INCLUDE_netxpto_H_
