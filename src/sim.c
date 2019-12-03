/* Internal */
#include "machine/instruction.h"
#include "machine/memory.h"

/* Standard */
#include <stdio.h>
#include <stdlib.h>


/* Default configurations for the simulator */
#define ACPU_SIM_DEFAULT_BINARY_NAME "program.bin"
#define ACPU_SIM_DEFAULT_ADDRESS_BITS 32

/* Other constants */
#define ACPU_SIM_MAX_ADDRESS_BITS 32


int main(int argc, char** argv) {
  char* binary_file = ACPU_SIM_DEFAULT_BINARY_NAME;
  int address_width = ACPU_SIM_DEFAULT_ADDRESS_BITS;

  /* Parse command line parameters
     very crude implementation for now, gotta go fast */

  /* Binary file to execute */
  if(argc > 1) {
    binary_file = argv[1];
  }

  /* Number of address bits to use */
  if(argc > 2) {
    address_width = atoi(argv[2]);
    if(address_width > ACPU_SIM_MAX_ADDRESS_BITS) {
      printf("Error, the maximum allowed address bit count is %d\n", ACPU_SIM_MAX_ADDRESS_BITS);
    }
  }

  /* Create memory of the apropriate size */

  /* Open the binary file and load into memory */

  /* Execute instructions forever, quit with cntrl + c */
  while(1) {}
}
