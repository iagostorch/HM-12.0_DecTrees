/* The copyright in this software is being made available under the BSD
 * License, included below. This software may be subject to other third party
 * and contributor rights, including patent rights, and no such rights are
 * granted under this license.  
 *
 * Copyright (c) 2010-2013, ITU/ISO/IEC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *  * Neither the name of the ITU/ISO/IEC nor the names of its contributors may
 *    be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

/** \file     encmain.cpp
    \brief    Encoder application main
*/

#include <time.h>
#include <iostream>
#include "TAppEncTop.h"
#include "TAppCommon/program_options_lite.h"

using namespace std;
namespace po = df::program_options_lite;

//gcorrea 23/01/2014
double RDcost_MSM, RDcost_2Nx2N, RDcost_2NxN, RDcost_Nx2N, RDcost_NxN, RDcost_2NxnU, RDcost_2NxnD, RDcost_nLx2N, RDcost_nRx2N;

int frameWidth, frameHeight;
int nCU_hor, nCU_ver, nCU32x32_hor, nCU32x32_ver, nCU16x16_hor, nCU16x16_ver, nCU8x8_hor, nCU8x8_ver, nCU;

int count_all_LCU, count_all_CU32x32, count_all_CU16x16, count_all_CU8x8;
int count_LCU, count_CU32x32, count_CU16x16, count_CU8x8;
int count_frame;

double sum_cost2Nx2N_64x64, sum_cost2Nx2N_32x32, sum_cost2Nx2N_16x16, sum_cost2Nx2N_8x8;
double sum_costSKIP_64x64, sum_costSKIP_32x32, sum_costSKIP_16x16, sum_costSKIP_8x8;
double sum_bestCost_64x64, sum_bestCost_32x32, sum_bestCost_16x16, sum_bestCost_8x8;

double med_cost2Nx2N_64x64, med_cost2Nx2N_32x32, med_cost2Nx2N_16x16, med_cost2Nx2N_8x8;
double med_costSKIP_64x64, med_costSKIP_32x32, med_costSKIP_16x16, med_costSKIP_8x8;
double med_bestCost_64x64, med_bestCost_32x32, med_bestCost_16x16, med_bestCost_8x8;
//gcorrea 23/01/2014 END


//! \ingroup TAppEncoder
//! \{

// ====================================================================================================================
// Main function
// ====================================================================================================================

int main(int argc, char* argv[])
{
  TAppEncTop  cTAppEncTop;

  // print information
  fprintf( stdout, "\n" );
  fprintf( stdout, "HM software: Encoder Version [%s]", NV_VERSION );
  fprintf( stdout, NVM_ONOS );
  fprintf( stdout, NVM_COMPILEDBY );
  fprintf( stdout, NVM_BITS );
  fprintf( stdout, "\n" );

  // create application encoder class
  cTAppEncTop.create();

  // parse configuration
  try
  {
    if(!cTAppEncTop.parseCfg( argc, argv ))
    {
      cTAppEncTop.destroy();
      return 1;
    }
  }
  catch (po::ParseFailure& e)
  {
    cerr << "Error parsing option \""<< e.arg <<"\" with argument \""<< e.val <<"\"." << endl;
    return 1;
  }

  // starting time
  double dResult;
  long lBefore = clock();

  // call encoding function
  cTAppEncTop.encode();

  // ending time
  dResult = (double)(clock()-lBefore) / CLOCKS_PER_SEC;
  printf("\n Total Time: %12.3f sec.\n", dResult);

  // destroy application encoder class
  cTAppEncTop.destroy();

  return 0;
}

//! \}
