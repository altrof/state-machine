//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: as_workflow_types.h
//
// Code generated for Simulink model 'as_workflow'.
//
// Model version                  : 1.16
// Simulink Coder version         : 9.6 (R2021b) 14-May-2021
// C/C++ source code generated on : Mon Jan 24 17:39:00 2022
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_as_workflow_types_h_
#define RTW_HEADER_as_workflow_types_h_
#include "rtwtypes.h"

// Model Code Variants
#ifndef DEFINED_TYPEDEF_FOR_EBS_STATE_
#define DEFINED_TYPEDEF_FOR_EBS_STATE_

typedef enum {
  EBS_STATE_UNAVAILABLE = 0,           // Default value
  EBS_STATE_ARMED,
  EBS_STATE_ACTIVATED
} EBS_STATE;

#endif

#ifndef DEFINED_TYPEDEF_FOR_MISSION_
#define DEFINED_TYPEDEF_FOR_MISSION_

typedef enum {
  MISSION_MISSION_OFF = 0,
  MISSION_MANUAL,                      // Default value
  MISSION_AUTONOMOUS
} MISSION;

#endif

#ifndef DEFINED_TYPEDEF_FOR_ASSI_STATE_
#define DEFINED_TYPEDEF_FOR_ASSI_STATE_

typedef enum {
  ASSI_STATE_OFF = 0,                  // Default value
  ASSI_STATE_READY,
  ASSI_STATE_DRIVING,
  ASSI_STATE_FINISHED,
  ASSI_STATE_EMERGENCY
} ASSI_STATE;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SB_STATE_
#define DEFINED_TYPEDEF_FOR_SB_STATE_

typedef enum {
  SB_STATE_UNAVAILABLE = 0,            // Default value
  SB_STATE_AVAILABLE,
  SB_STATE_ENGAGED
} SB_STATE;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SA_STATE_
#define DEFINED_TYPEDEF_FOR_SA_STATE_

typedef enum {
  SA_STATE_UNAVAILABLE = 0,            // Default value
  SA_STATE_AVAILABLE
} SA_STATE;

#endif

#ifndef DEFINED_TYPEDEF_FOR_AS_STATE_
#define DEFINED_TYPEDEF_FOR_AS_STATE_

typedef enum {
  AS_STATE_AS_OFF = 0,                 // Default value
  AS_STATE_MANUAL,
  AS_STATE_AS_READY,
  AS_STATE_AS_DRIVING,
  AS_STATE_AS_FINISHED,
  AS_STATE_AS_EMERGENCY
} AS_STATE;

#endif
#endif                                 // RTW_HEADER_as_workflow_types_h_

//
// File trailer for generated code.
//
// [EOF]
//
