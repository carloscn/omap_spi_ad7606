/*
 * pru.h
 *
 *  Created on: 2015-11-20
 *      Author: daogu
 */

#ifndef PRU_H_
#define PRU_H_

extern void PruDisable(unsigned char pruNum);
extern void PruEnable(unsigned char pruNum);
extern unsigned int PruLoad(unsigned char pruNum, unsigned int* pruCode, unsigned int codeSizeInWords);
extern unsigned int PruRun (unsigned char pruNum);
extern unsigned int PruWaitForHalt (unsigned char pruNum, int timeout);

#endif /* PRU_H_ */
