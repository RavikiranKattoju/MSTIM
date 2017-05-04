
#ifndef EMSSYSTEM_H_
#define EMSSYSTEM_H_

#include "EMSChannel.h"

#define ACTION 'G'
#define CHANNEL 'C'
#define INTENSITY 'I'
#define TIME 'T'
#define OPTION 'O'

class EMSSystem {
public:
	EMSSystem(int channels);
	virtual ~EMSSystem();

	virtual void addChannelToSystem(EMSChannel *emsChannel);
	virtual void doCommand(String *command);
	void shutDown();
	virtual int check();
	static void start();

protected:
	virtual void doActionCommand(String *command);
	virtual void setOption(String *option);
	virtual bool getChannelAndValue(String *option, int *channel, int *value);
	virtual int getNextNumberOfSting(String *command, int startIndex);

private:
	EMSChannel **emsChannels;
	int channelCount;
	int size;
	bool isInRange(int channel);
};

#endif /* EMSSYSTEM_H_ */

