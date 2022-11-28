#include "circular_buffer.h"
#include <Arduino.h>


short circular_buffer::getValue(int indexDesired){
    //Serial.println((circ_idx + indexDesired) %capacity);
    return c_array[(circ_idx + indexDesired) % capacity];
}
void circular_buffer::insertBlock(short* bp)
{
    short* values = bp;
    for(int i = circ_idx; i < (circ_idx + 128); i++)
    {
        c_array[i % capacity] = *values;
        values++;
    }
    circ_idx += 128;
    circ_idx = circ_idx % capacity;
    
}

/* void circular_buffer::phaserChangeDelay(int diff)
{
    if(capacity + diff > MAX_ARRAY_SIZE)
    {
        Serial.println("Change Delay Too Big");
    }
    //orig - new, positive implies less delay
    if(diff >0)
    {
        capacity -= diff;
        circ_idx += diff;
        circ_idx = circ_idx % capacity;
    }
    else if(diff < 0)
    {
        capacity -= diff;
        int new_circ_idx = circ_idx + diff;
        for(int i = new_circ_idx; (i % capacity) < circ_idx; ++i)
        {
            c_array[i % capacity] = 0;
        }
        circ_idx = new_circ_idx % capacity;
    }
} */
