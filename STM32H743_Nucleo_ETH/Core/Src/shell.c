/* wolfssl_example.c
 *
 * Copyright (C) 2006-2023 wolfSSL Inc.
 *
 * This file is part of wolfSSL.
 *
 * wolfSSL is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * wolfSSL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1335, USA
 */

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#ifndef WOLFSSL_USER_SETTINGS
    #include <wolfssl/options.h>
#endif
#include <wolfssl/wolfcrypt/settings.h>
#include <wolfssl/wolfcrypt/error-crypt.h>
#include <wolfcrypt/test/test.h>
#include <wolfcrypt/benchmark/benchmark.h>
#include <wolftpm/tpm2_wrap.h>

#include <stdio.h>
#include <string.h>

/*****************************************************************************
 * Configuration
 ****************************************************************************/


/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/* This sets which UART to use for the console.  It is something you will have
 * to configure in STMCubeIDE and then change here. */
#ifndef HAL_CONSOLE_UART
#define HAL_CONSOLE_UART huart3
#endif
extern UART_HandleTypeDef HAL_CONSOLE_UART;
extern WOLFTPM2_DEV dev;

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/
typedef struct func_args {
    int argc;
    char** argv;
    int return_code;
} func_args;

const char shell_menu[] = "\n"
    "\tt. wolfCrypt Test\n"
    "\tb. wolfCrypt Benchmark\n"
    "\ti. Get TPM information\n"
;

/*****************************************************************************
 * Public functions
 ****************************************************************************/
void wolf_shell(void* argument)
{
    HAL_StatusTypeDef halRet;
    uint8_t buffer[2];
    func_args args;

    while (1) {
        memset(&args, 0, sizeof(args));
        args.return_code = NOT_COMPILED_IN; /* default */

        printf("\n\t\t\t\tSHELL>\n");
        printf(shell_menu);
        printf("Please select one of the above options:\n");

        do {
            halRet = HAL_UART_Receive(&HAL_CONSOLE_UART, buffer, sizeof(buffer), 100);
        } while (halRet != HAL_OK || buffer[0] == '\n' || buffer[0] == '\r');

        switch (buffer[0]) {
        case 't':
            printf("Running wolfCrypt Tests...\n");
        #ifndef NO_CRYPT_TEST
            args.return_code = 0;
            wolfcrypt_test(&args);
        #else
            args.return_code = NOT_COMPILED_IN;
        #endif
            printf("Crypt Test: Return code %d\n", args.return_code);
            break;

        case 'b':
            printf("Running wolfCrypt Benchmarks...\n");
        #ifndef NO_CRYPT_BENCHMARK
            args.return_code = 0;
            benchmark_test(&args);
        #else
            args.return_code = NOT_COMPILED_IN;
        #endif
            printf("Benchmark Test: Return code %d\n", args.return_code);
            break;

        case 'i':
        {
            WOLFTPM2_CAPS caps;
            wolfTPM2_GetCapabilities(&dev, &caps);

            printf("Mfg %s (%d), Vendor %s, Fw %u.%u (0x%x), "
                "FIPS 140-2 %d, CC-EAL4 %d\n",
                caps.mfgStr, caps.mfg, caps.vendorStr, caps.fwVerMajor,
                caps.fwVerMinor, caps.fwVerVendor, caps.fips140_2, caps.cc_eal4);
        #if defined(WOLFTPM_SLB9672) || defined(WOLFTPM_SLB9673)
            printf("\tKeyGroupId 0x%x, Operational Mode 0x%x, FwCounter %d (%d same)\n",
                caps.keyGroupId, caps.opMode, caps.fwCounter, caps.fwCounterSame);
        #endif
            break;
        }

        /* All other cases go here */
        default:
            printf("\nSelection out of range\n");
            break;
        }
    }
}
