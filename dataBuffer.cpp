#include "dataBuffer.h"
using namespace std;


dataBuffer::dataBuffer()
{

// Initialize variables, set pointers dataMatrix and next to NULL

    numElement = 0;
    numSample = 0;
    scanline = 0;
    dataMatrix = NULL;
    next = NULL;

}

dataBuffer::dataBuffer( std::ifstream *imagFile, std::ifstream *realFile, int inputNumElement, int inputNumSample, int inputScanline)
{

// Initialize counterpart variables for numElement, numSample, scanline

    numElement = inputNumElement;
    numSample = inputNumSample;
    scanline = inputScanline;
    dataMatrix = createDataMatrix (); // Call createDataMatrix, assign to dataMatrix

    loadRFData (dataMatrix, imagFile, realFile); // Call loadRFData

     
} 

dataBuffer::~dataBuffer()
{

    deleteDataMatrix(); // Releases the memory for dataMatrix

}

complex **dataBuffer::createDataMatrix()
{
 
 // Dynamically allocating the 2D array for numElement and numSample


    complex **RFData;
    RFData = new complex *[numElement]; // Allocating first dimension

    for (int i = 0; i < numElement; i++){

        RFData[i] = new complex [numSample]; // Allocating second dimension 

    }

return RFData;

}

int dataBuffer::loadRFData(complex **RFData, std::ifstream *imagFile, std::ifstream *realFile) 
{ 

// Initialize 2 character arrays 

    char imag[20];
    char real[20];

// Populates dataBuffer

    for (int i = 0; i < numElement; i++){

        for(int k = 0; k < numSample; k++){

// Opening the file

            imagFile->getline(imag, 20);
            RFData[i][k].imag = atof(imag);

            realFile->getline(real, 20);
            RFData[i][k].real = atof(real);

        }

    }

    return 0;


}

float dataBuffer::getRealRFData(int element,int sample)
{

    return dataMatrix[element][sample].real; // Returns real component of dataMatrix

}
float dataBuffer::getImagRFData(int element,int sample)
{

    return dataMatrix[element][sample].imag; // Returns imaginary component of dataMatrix

}

void dataBuffer::deleteDataMatrix()
{

    for (int i = 0; i < numElement; i++){

        delete[] dataMatrix[i]; // Deleting array itself
    }

    delete[] dataMatrix; // Free-up memory space

}




