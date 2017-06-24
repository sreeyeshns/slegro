/*
 * system.h
 *
 *  Created on: Jun 18, 2017
 *      Author: Sreeyesh N. S. <sreeyeshns@gmail.com>
 */

#ifndef _SYSTEM_H
#define _SYSTEM_H

#define APB_DIV_FACT    4U
#define PLL_MUL_FACT    5U
#define SYS_XTAL_MHZ    12U
#define SYS_CCLK_MHZ    (SYS_XTAL_MHZ * PLL_MUL_FACT)
#define SYS_PCLK_MHZ    (SYS_CCLK_MHZ/APB_DIV_FACT)


#endif /* _SYSTEM_H */
