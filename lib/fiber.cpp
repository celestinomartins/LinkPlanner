# include <limits>
# include <complex> // numero complexo
# include <stdio.h> // *printf*
# include <iostream>
# include <string>
# include <math.h> // *exp*
# include <algorithm> //std::min_element, std::max_element
# include <fstream> // isso e para imprimir e gravar no ficheiro txt
# include <valarray>
# include "netxpto.h"
# include "fiber.h"

# include "myfft1.cpp" // ficheiro de FFT // IFFT
# include <cstdlib> // isso e para aplicar a funcao malloc()


using namespace std;
using std::cout; // cout--> consoule output de informacao
using std::endl; // end line

void Fiber::initialize(void) {

	outputSignals[0]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	outputSignals[0]->setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
	outputSignals[0]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());
	
	//===========================================VARIAVEIS DE ENTRADA==================================================================================

	//double alpha = 4.6052e-05; // valor de perdas na fibra
	//double s = 100.0; // comprimento de fibra em Km
	//double Lambda = 1550e-9; // valor C.D.O. em metros
	//double D = -10.0; // valor d coeficiente de dispersao em ps/nm/km D=-/2*pi*c*B2)/(lambda^2)
	const double pi = 3.1415926535897932384; // valor de pi
	const double c = 3e8; // velocidade de luz
	typedef std::complex<double> Complex;
    typedef std::valarray<Complex> CArray;
	
//==================================CONSTANTES DERIVADOS DE VARIAVEIS DE ENTRADA=======================================================================

    double B2 = -((pow(CDO,2))*D)/(2*pi*c); // calcula o coeficiente de dispersao de velocidade de grupo (B2<0-->dispersao anomala, B2>0-->dispersao normal) (dispersao cromatica)
    double f = c/CDO; // calcula a frequencia da onda EM
    double omega = 2*pi*f; // frequencia angular (w)
  
//==================================CRIACAO DE FICHEIROS TXT PARA A GRAVACAO===========================================================================

    ofstream myfile1;
    myfile1.open ("Funcao_de_transferencia.txt");

    ofstream myfile2;
    myfile2.open ("Resposta_impulsiva.txt");
  
//================================FUNCAO DE TRANSFERENCIA H(w)=========================================================================================
    
	unsigned int i = 0; // numero inicial do indice i

    int l = 10000.0; // numero de pontos no comprimento de fibra
    
    //Complex transferFunction[l]; // declaracao que funcao de transferencia (H(w)) e complexa
    Complex *transferFunction; // declaracao de quetransferFunction e complexa 
    H = (Complex*)malloc( l * sizeof(Complex) ); // aplicacao de funcao malloc() ao transferFunction
    
    Complex I=1i; // definicao do numero complexo
    
    for (double s = 1.0; s < 10001.0; s++) // Qual é o tempo upper(U), lower(L) e intervalo entre intervalo upper e  lower intervalo(I)
    {
        transferFunction[i] = (exp(-attenuationCoeficient*fiberLength))*(exp(-fiberLength*(I/2.0)*B2*omega*omega));
        
        myfile1 << s; myfile1 << "       "; myfile1 << abs(transferFunction[i]); myfile1 << "\n"; // para imprimir e gravar no ficheiro txt (feixe de entrada)
        
		i++;
    }

//===================================RESPOSTA IMPULSIVA h(t)===========================================================================================

    CArray impulseResponse(transferFunction, l); // declara qual e vetor de entrada (H) e a dimensao dele (l)   
    //impulseResponse = (CArray)malloc( l * sizeof(Complex) );
    

    ifft(impulseResponse); // ponha o vetor H dentro da ifft no ficheiro myfft1.cpp
  
    for(int k=0; k<l; k++) // isso e para gravar h(t) num ficheiro de txt
    {
		myfile2 << abs(impulseResponse[k]) << "\n";
    }
  
    return 0; // conclusao satisfatoria

	// initializer
	// reservar espaço em memoria para a função transferencia malloc()

	// reservar espaço em memoria para a resposta impulsional

	// calcular a função H(w)

	// calculas o h(t) ifft(H(w)

	// gravas num ficheiro H(w)

	// gravas noutro ficheiro o h(t)
}
bool Fiber::runBlock(void) {
	int ready = inputSignals[0]->ready();
	int space = outputSignals[0]->space();
	int process = min(ready, space);
	if (process == 0) return false;

	t_complex inSig;

	t_complex outSig;

	t_real h = exp(-fiberLength*attenuationCoeficient / 2);

	for (int i = 0; i < process; i++) {

		inputSignals[0]->bufferGet(&inSig);

		outSig = inSig*h;

		outputSignals[0]->bufferPut(outSig);
	}
	return true;

}
