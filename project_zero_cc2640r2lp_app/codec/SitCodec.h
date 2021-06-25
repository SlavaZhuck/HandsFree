#ifndef _SITENCODER_H
#define	_SITENCODER_H 

typedef struct gsit_state_s {
	long yl;	/* Locked or steady state step size multiplier. */
	int yu;		/* Unlocked or non-steady state step size multiplier. */
	int dms;	/* Short term energy estimate. */
	int dml;	/* Long term energy estimate. */
	int ap;		/* Linear weighting coefficient of 'yl' and 'yu'. */

	int a[2];	/* Coefficients of pole portion of prediction filter. */
	int b[6];	/* Coefficients of zero portion of prediction filter. */
	int pk[2];	/* Signs of previous two samples of a partially
				 * reconstructed signal. */
	short dq[6];/* int here fails in newupdate on encode!
				 * Previous 6 samples of the quantized difference
				 * signal represented in an internal floating point
				 * format.
				 */
	int sr[2];	/* Previous 2 samples of the quantized difference
				 * signal represented in an internal floating point
				 * format. */
	int td;		/* delayed tone detect, new in 1988 version */
} gsit_state;

extern void gsit_init_state(gsit_state *state_ptr);

extern void SitEncoder(short *u, unsigned char *y,	gsit_state *state_ptr);
extern void SitDecoder(unsigned char *u, short *y,	gsit_state *state_ptr);


#endif /* !_SITENCODER_H */
