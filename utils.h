/*
 * utils.h
 *
 *  Created on: Nov 1, 2019
 *      Author: AhmedShawky
 */

#ifndef UTILS_H_
#define UTILS_H_

#define SET_BIT(REG,PIN)                       REG|=(1<<PIN)
#define CLR_BIT(REG,PIN)                       REG&=0<<PIN
#define GET_BIT(REG,PIN)                       (REG&(1<<PIN))>>PIN
#define TOGGLE_BIT(REG,PIN)                    REG~=(1<<PIN)

#define CONCBIT(B7,B6,B5,B4,B3,B2,B1,B0) CONCBIT_HELPER(B7,B6,B5,B4,B3,B2,B1,B0)
#define CONCBIT_HELPER(B7,B6,B5,B4,B3,B2,B1,B0)  (0b##B7##B6##B5##B4##B3##B2##B1##B0)



#endif /* UTILS_H_ */
