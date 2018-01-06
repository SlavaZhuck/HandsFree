

struct ADPCMstate {
	short prevsample;
	int previndex;
};

char ADPCMEncoder(short , struct ADPCMstate *);

int ADPCMDecoder(char , struct ADPCMstate *);

void ADPCMEncoderBuf(short *u, char *y,	struct ADPCMstate *state_ptr);
void ADPCMDecoderBuf(char *u, short *y,	struct ADPCMstate *state_ptr);

