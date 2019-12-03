// Internal
#include <machine/instruction.h>
#include <machine/memory.h>

// Standard
#include <stdio.h>


// Default configurations for the simulator
#define ACPU_SIM_DEFAULT_BINARY_NAME "program.bin"
#define ACPU_SIM_DEFAULT_ADDRESS_BITS 32


int main(int argc, char** argv) {
  char* sourceFile = ACPU_SIM_DEFAULT_BINARY_NAME;
  int addressWidth = ACPU_SIM_DEFAULT_ADDRESS_BITS;

  /* Parse command line parameters
     very crude implementation for now, gotta go fast */
  if(argc > 2) {
    sourceFile = argv[1];
  }

  if(argc > 3) {
    addressWidth = atoi(argv[2]);
  }

  /* Create memory of the apropriate size */

  /* Open the binary file and load into memory */

  /* Execute instructions forever, quit with cntrl + c */
  while(1) {}
}
