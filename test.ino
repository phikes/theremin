#include <MIDI.h>
#include <NewPing.h>

#define TRIGGER_PIN  12  
#define ECHO_PIN     11  
#define MAX_DISTANCE 30

MIDI_CREATE_DEFAULT_INSTANCE();
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup()
{
    Serial.begin(115200);
}

void loop()
{

        unsigned int dist = ((float)sonar.ping()) / US_ROUNDTRIP_CM;
        float ratio = (MAX_DISTANCE-(float)dist)/MAX_DISTANCE;
        int note = floor(59+8*ratio);
        
        if(note<67)
        {
          MIDI.sendNoteOn(note, 127, 1);
          delay(50);        
          MIDI.sendNoteOff(note, 127, 1);
        }
}
