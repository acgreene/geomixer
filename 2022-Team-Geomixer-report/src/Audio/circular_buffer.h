#ifndef circ_buffer_h
#define circ_buffer_h
#include "Arduino.h"

#define MAX_ARRAY_SIZE 4000

class circular_buffer
{

public:
    circular_buffer(int sizeBuffer)
    {
        capacity = sizeBuffer;
        circ_idx = 0;
        memset(c_array, 0, sizeof(c_array));
    }
    short getValue(int indexDesired);
    void insertBlock(short* values); //move index here too
    //void phaserChangeDelay(int difference);


private:
    int circ_idx;
    int capacity;
    short c_array[MAX_ARRAY_SIZE]; 

};
#endif