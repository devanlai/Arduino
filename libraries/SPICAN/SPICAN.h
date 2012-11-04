/*
  SPICAN.h - Library for interfacing with the MCP2515.
  Created by Ryan Tseng, Oct. 5th 2010.
  Ported to Arduino 1.0.1 by Devan Lai, Nov. 3rd 2012.
*/
#ifndef SPI_CAN_h
#define SPI_CAN_h

#include <Arduino.h>
#include <utility/mcp2515.h>

#define CAN_BUFFER_SIZE 30

class CanMessage {
  public:
    CanMessage();
    CanMessage(boolean valid);
    CanMessage(int _id, const char * _data, char _len = 8);
    int id;
    char data[8];
    char len;
};

class SPICAN
{
  public:
    SPICAN(int CsPin, int IntPin);
    void begin(int hz, bool do_reset = true, bool do_interrupt = true);
    int frequency(int khz);
    int available();
    boolean interrupted();
    int send(CanMessage msg);
    int recv(int channel, CanMessage &msg);
    int setFilter(int channel, int filter, int id);
    int setMask(int channel, int mask);
    void filterOn();
    void filterOff();
    void reset();
    void config(boolean enable);
    void monitor(boolean silent);
    void attach(void (*func)(CanMessage &msg));
    void detach();
    unsigned int rxError();
    unsigned int txError();
	void enableInterrupt();
	void disableInterrupt();
	void handleInterrupt();
    void (*_func)(CanMessage &msg);
  private:
    int _CsPin;
    int _IntPin;
    int _Freq;
    volatile uint8_t* _PCICR;
    volatile uint8_t* _PCMSK;
    uint8_t  _PortMask;
    uint8_t  _PinMask;
    Mcp2515 _mcp2515;
};

/*
void CanReadHandler();
extern void CanBufferInit();
extern CanMessage CanBufferRead();
extern int CanBufferSize();
*/

#ifndef CAN_NO_INTERRUPTS

#ifndef CAN_PCINT_COUNT
#define CAN_PCINT_COUNT 4
#endif

extern SPICAN* PortToCAN[CAN_PCINT_COUNT];

#endif

#ifdef HAVE_CAN
extern SPICAN CAN;
#endif

#endif
