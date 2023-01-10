#include "BmodeClass.h"

BmodeClass::BmodeClass()
{

// Set pointers to NULL, initialize line variable at 0

    imparams = NULL;
    RFData =  NULL;
    next = NULL;
    line = 0; 

}

BmodeClass::BmodeClass(imageParam *params,dataBuffer *data,int numline)
{

// Set variables / pointers 

    imparams = params;
    RFData = data;
    line = numline;

// Allocate memory for scanline

    scanline = createScanline(imparams -> getNumPixel()); 

    float *scanline; 
    scanline = new float[imparams -> getNumPixel()];

    beamform(); // Invoke beamform
}

BmodeClass::~BmodeClass()
{

    deleteScanline(); // Release arrays allocated to scanline

}

float *BmodeClass::createScanline(int numPixel)
{

// Allocate 1D array of size numPixel to variable mem

float *mem;
mem = new float[numPixel];

return mem; // Return mem

}

void BmodeClass::beamform()
{

// Initialize float variables

    float tforward = 0;
    float tback = 0;
    float ttotal = 0;
    int tsample = 0;
    float Preal = 0;
    float Pimag = 0; 
    
for (int i = 0; i < imparams -> getNumPixel(); i++){ 

// Calculates the forward movement of the scanline
    tforward = (imparams -> getYPosition(line, i))/imparams -> SOS;

    for (int k = 0; k < imparams -> getNumElement(); k++){

// Calculates the backward movement of the scanline
    tback = sqrt((pow(imparams -> getYPosition(line, i), 2))+(pow(imparams -> getXPosition(line, i) - imparams -> getElementPosition(k), 2)))/imparams -> SOS;
// Calculates total movement
    ttotal = tforward + tback;
// Calculates the sample
    tsample = floor(ttotal* imparams -> FS);

// If the sample is less than getNumSample 

    if (tsample < imparams -> getNumSample()){

    // Updates the real and imaginary components

    Preal = Preal + RFData -> getRealRFData(k, tsample); 

    Pimag = Pimag + RFData -> getImagRFData(k, tsample);

    }
    }

// Echo magnitude at any particular scanline location 

    scanline[i] = sqrt((pow(Preal, 2))+(pow(Pimag, 2))); 
    Preal = 0;
    Pimag = 0;

}
}

void BmodeClass::getScanline(float *data)
{

// Copies content inside scanline to data element by element

for (int i = 0; i < imparams -> getNumPixel(); i++){

    data[i] = scanline[i];
}

}

void BmodeClass::deleteScanline()
{
 // Delete array

    delete [] scanline; 
}