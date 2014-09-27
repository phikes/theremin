#include <MIDI.h>
#include <NewPing.h>

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 100 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
// Simple tutorial on how to receive and send MIDI messages.
// Here, when receiving any message on channel 4, the Arduino
// will blink a led and play back a note for 1 second.
MIDI_CREATE_DEFAULT_INSTANCE();
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

#define LED 13   		    // LED pin on Arduino Uno

void setup()
{
    //MIDI.begin(4);          // Launch MIDI and listen to channel 4
    Serial.begin(115200);
}

void loop()
{

        unsigned int dist = sonar.ping() / US_ROUNDTRIP_CM;
        float ratio = (MAX_DISTANCE-(float)dist)/MAX_DISTANCE;
        int note = 127*ratio;
        
        if(note<=123)
        {
          MIDI.sendNoteOn(note,127,1);
          delay(50);        
          MIDI.sendNoteOff(note,127,1);
        }
}
