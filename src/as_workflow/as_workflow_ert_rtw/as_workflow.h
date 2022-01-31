//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: as_workflow.h
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
#ifndef RTW_HEADER_as_workflow_h_
#define RTW_HEADER_as_workflow_h_
#include "rtwtypes.h"
#include "as_workflow_types.h"

// Macros for accessing real-time model data structure
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

// Class declaration for model as_workflow
class as_workflowModelClass
{
  // public data and function members
 public:
  // Block states (default storage) for system '<Root>'
  struct DW_as_workflow_T {
    uint8_T is_active_c3_as_workflow;  // '<Root>/Chart'
    uint8_T is_c3_as_workflow;         // '<Root>/Chart'
    uint8_T temporalCounter_i1;        // '<Root>/Chart'
  };

  // External inputs (root inport signals with default storage)
  struct ExtU_as_workflow_T {
    EBS_STATE EBS_IN;                  // '<Root>/EBS_IN'
    boolean_T ASMS_IN;                 // '<Root>/ASMS_IN'
    boolean_T TS_IN;                   // '<Root>/TS_IN'
    MISSION MISSION_IN;                // '<Root>/MISSION_IN'
    boolean_T RES_IN;                  // '<Root>/RES_IN'
    boolean_T MISSION_FINISH_IN;       // '<Root>/MISSION_FINISH_IN'
    real_T FIRST_BRAKE_IN;             // '<Root>/FIRST_BRAKE_IN'
    real_T SECOND_BRAKE_IN;            // '<Root>/SECOND_BRAKE_IN'
  };

  // External outputs (root outports fed by signals with default storage)
  struct ExtY_as_workflow_T {
    AS_STATE AS_STATUS_OUT;            // '<Root>/AS_STATUS_OUT'
    ASSI_STATE ASSI_OUT;               // '<Root>/ASSI_OUT'
    SB_STATE SB_OUT;                   // '<Root>/SB_OUT'
    SA_STATE SA_OUT;                   // '<Root>/SA_OUT'
    boolean_T BRAKE_PRESSURE_RELEASED_OUT;// '<Root>/BRAKE_PRESSURE_RELEASED_OUT' 
  };

  // Real-time Model Data Structure
  struct RT_MODEL_as_workflow_T {
    const char_T * volatile errorStatus;
  };

  // Copy Constructor
  as_workflowModelClass(as_workflowModelClass const&) =delete;

  // Assignment Operator
  as_workflowModelClass& operator= (as_workflowModelClass const&) & = delete;

  // Real-Time Model get method
  as_workflowModelClass::RT_MODEL_as_workflow_T * getRTM();

  // Root inports set method
  void setExternalInputs(const ExtU_as_workflow_T *pExtU_as_workflow_T)
  {
    as_workflow_U = *pExtU_as_workflow_T;
  }

  // Root outports get method
  const ExtY_as_workflow_T &getExternalOutputs() const
  {
    return as_workflow_Y;
  }

  // model initialize function
  void initialize();
  void ModelExternalInputInit();

  // model step function
  void step();

  // model terminate function
  static void terminate();

  // Constructor
  as_workflowModelClass();

  // Destructor
  ~as_workflowModelClass();

  // private data and function members
 private:
  // External inputs
  ExtU_as_workflow_T as_workflow_U;

  // External outputs
  ExtY_as_workflow_T as_workflow_Y;

  // Block states
  DW_as_workflow_T as_workflow_DW;

  // Real-Time Model
  RT_MODEL_as_workflow_T as_workflow_M;
};

//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'as_workflow'
//  '<S1>'   : 'as_workflow/BrakePressureCheck'
//  '<S2>'   : 'as_workflow/Chart'
//  '<S3>'   : 'as_workflow/BrakePressureCheck/If Action Subsystem'
//  '<S4>'   : 'as_workflow/BrakePressureCheck/If Action Subsystem1'

#endif                                 // RTW_HEADER_as_workflow_h_

//
// File trailer for generated code.
//
// [EOF]
//
