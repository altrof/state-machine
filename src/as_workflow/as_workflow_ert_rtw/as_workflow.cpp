//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: as_workflow.cpp
//
// Code generated for Simulink model 'as_workflow'.
//
// Model version                  : 1.16
// Simulink Coder version         : 9.6 (R2021b) 14-May-2021
// C/C++ source code generated on : Tue Feb  1 16:42:01 2022
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "as_workflow.h"
#include "as_workflow_private.h"

// Named constants for Chart: '<Root>/Chart'
const uint8_T as_workflow_IN_AS_DRIVING{ 1U };

const uint8_T as_workflow_IN_AS_EMERGENCY{ 2U };

const uint8_T as_workflow_IN_AS_FINISHED{ 3U };

const uint8_T as_workflow_IN_AS_OFF{ 4U };

const uint8_T as_workflow_IN_AS_READY{ 5U };

const uint8_T as_workflow_IN_MANUAL_DRIVING{ 6U };

// Model step function
void as_workflowModelClass::step()
{
  boolean_T rtb_Merge;

  // Outputs for IfAction SubSystem: '<S1>/If Action Subsystem1' incorporates:
  //   ActionPort: '<S4>/Action Port'

  // Outputs for IfAction SubSystem: '<S1>/If Action Subsystem' incorporates:
  //   ActionPort: '<S3>/Action Port'

  // If: '<S1>/If' incorporates:
  //   Inport: '<Root>/FIRST_BRAKE'
  //   Inport: '<Root>/SECOND_BRAKE'
  //   Inport: '<S3>/In1'
  //   Inport: '<S4>/In1'

  rtb_Merge = ((as_workflow_U.FIRST_BRAKE < 2.0) && (as_workflow_U.SECOND_BRAKE <
    2.0));

  // End of Outputs for SubSystem: '<S1>/If Action Subsystem'
  // End of Outputs for SubSystem: '<S1>/If Action Subsystem1'

  // Chart: '<Root>/Chart' incorporates:
  //   Inport: '<Root>/EBS'
  //   Inport: '<Root>/IS_ASMS_ON'
  //   Inport: '<Root>/IS_MISSION_FINISHED'
  //   Inport: '<Root>/IS_RES_TRIGGERED'
  //   Inport: '<Root>/IS_TS_ON'
  //   Inport: '<Root>/MISSION_STATUS'

  if (as_workflow_DW.temporalCounter_i1 < 63U) {
    as_workflow_DW.temporalCounter_i1 = static_cast<uint8_T>
      (as_workflow_DW.temporalCounter_i1 + 1);
  }

  if (as_workflow_DW.is_active_c3_as_workflow == 0U) {
    as_workflow_DW.is_active_c3_as_workflow = 1U;
    as_workflow_DW.is_c3_as_workflow = as_workflow_IN_AS_OFF;
  } else {
    switch (as_workflow_DW.is_c3_as_workflow) {
     case as_workflow_IN_AS_DRIVING:
      if (as_workflow_U.EBS == EBS_STATE_ACTIVATED) {
        as_workflow_DW.is_c3_as_workflow = as_workflow_IN_AS_EMERGENCY;
      } else if (as_workflow_U.IS_MISSION_FINISHED) {
        as_workflow_DW.is_c3_as_workflow = as_workflow_IN_AS_FINISHED;
      } else {
        // Outport: '<Root>/AS_STATUS_OUT'
        as_workflow_Y.AS_STATUS_OUT = AS_STATE_AS_DRIVING;

        // Outport: '<Root>/SA_OUT'
        as_workflow_Y.SA_OUT = SA_STATE_AVAILABLE;

        // Outport: '<Root>/SB_OUT'
        as_workflow_Y.SB_OUT = SB_STATE_AVAILABLE;

        // Outport: '<Root>/ASSI_OUT'
        as_workflow_Y.ASSI_OUT = ASSI_STATE_DRIVING;
      }
      break;

     case as_workflow_IN_AS_EMERGENCY:
      if ((!as_workflow_U.IS_ASMS_ON) && rtb_Merge) {
        as_workflow_DW.is_c3_as_workflow = as_workflow_IN_AS_OFF;
      } else {
        // Outport: '<Root>/AS_STATUS_OUT'
        as_workflow_Y.AS_STATUS_OUT = AS_STATE_AS_EMERGENCY;

        // Outport: '<Root>/ASSI_OUT'
        as_workflow_Y.ASSI_OUT = ASSI_STATE_EMERGENCY;
      }
      break;

     case as_workflow_IN_AS_FINISHED:
      if (as_workflow_U.IS_RES_TRIGGERED) {
        as_workflow_DW.is_c3_as_workflow = as_workflow_IN_AS_EMERGENCY;
      } else if ((!as_workflow_U.IS_ASMS_ON) && rtb_Merge) {
        as_workflow_DW.is_c3_as_workflow = as_workflow_IN_AS_OFF;
      } else {
        // Outport: '<Root>/AS_STATUS_OUT'
        as_workflow_Y.AS_STATUS_OUT = AS_STATE_AS_FINISHED;

        // Outport: '<Root>/SA_OUT'
        as_workflow_Y.SA_OUT = SA_STATE_UNAVAILABLE;

        // Outport: '<Root>/ASSI_OUT'
        as_workflow_Y.ASSI_OUT = ASSI_STATE_FINISHED;
      }
      break;

     case as_workflow_IN_AS_OFF:
      if ((as_workflow_U.MISSION_STATUS == MISSION_MANUAL) &&
          as_workflow_U.IS_TS_ON && (!as_workflow_U.IS_ASMS_ON)) {
        as_workflow_DW.is_c3_as_workflow = as_workflow_IN_MANUAL_DRIVING;
      } else if ((as_workflow_U.EBS == EBS_STATE_ARMED) &&
                 (as_workflow_U.MISSION_STATUS == MISSION_AUTONOMOUS) &&
                 as_workflow_U.IS_TS_ON && as_workflow_U.IS_ASMS_ON &&
                 (!rtb_Merge)) {
        as_workflow_DW.is_c3_as_workflow = as_workflow_IN_AS_READY;
        as_workflow_DW.temporalCounter_i1 = 0U;
      } else {
        // Outport: '<Root>/AS_STATUS_OUT'
        as_workflow_Y.AS_STATUS_OUT = AS_STATE_AS_OFF;

        // Outport: '<Root>/SA_OUT'
        as_workflow_Y.SA_OUT = SA_STATE_UNAVAILABLE;

        // Outport: '<Root>/SB_OUT'
        as_workflow_Y.SB_OUT = SB_STATE_UNAVAILABLE;

        // Outport: '<Root>/ASSI_OUT'
        as_workflow_Y.ASSI_OUT = ASSI_STATE_OFF;

        // Outport: '<Root>/BRAKE_PRESSURE_RELEASED_OUT'
        as_workflow_Y.BRAKE_PRESSURE_RELEASED_OUT = rtb_Merge;
      }
      break;

     case as_workflow_IN_AS_READY:
      if ((!as_workflow_U.IS_ASMS_ON) && rtb_Merge) {
        as_workflow_DW.is_c3_as_workflow = as_workflow_IN_AS_OFF;
      } else if (as_workflow_DW.temporalCounter_i1 >= 50U) {
        as_workflow_DW.is_c3_as_workflow = as_workflow_IN_AS_DRIVING;
      } else if (as_workflow_U.EBS == EBS_STATE_ACTIVATED) {
        as_workflow_DW.is_c3_as_workflow = as_workflow_IN_AS_EMERGENCY;
      } else {
        // Outport: '<Root>/AS_STATUS_OUT'
        as_workflow_Y.AS_STATUS_OUT = AS_STATE_AS_READY;

        // Outport: '<Root>/SA_OUT'
        as_workflow_Y.SA_OUT = SA_STATE_AVAILABLE;

        // Outport: '<Root>/SB_OUT'
        as_workflow_Y.SB_OUT = SB_STATE_ENGAGED;

        // Outport: '<Root>/ASSI_OUT'
        as_workflow_Y.ASSI_OUT = ASSI_STATE_READY;
      }
      break;

     default:
      // case IN_MANUAL_DRIVING:
      if (!as_workflow_U.IS_TS_ON) {
        as_workflow_DW.is_c3_as_workflow = as_workflow_IN_AS_OFF;
      } else {
        // Outport: '<Root>/AS_STATUS_OUT'
        as_workflow_Y.AS_STATUS_OUT = AS_STATE_MANUAL;

        // Outport: '<Root>/SA_OUT'
        as_workflow_Y.SA_OUT = SA_STATE_UNAVAILABLE;

        // Outport: '<Root>/SB_OUT'
        as_workflow_Y.SB_OUT = SB_STATE_UNAVAILABLE;

        // Outport: '<Root>/ASSI_OUT'
        as_workflow_Y.ASSI_OUT = ASSI_STATE_OFF;
      }
      break;
    }
  }

  // End of Chart: '<Root>/Chart'
}

// Model initialize function
void as_workflowModelClass::initialize()
{
  // Registration code

  // external inputs
  as_workflow_U.MISSION_STATUS = MISSION_MANUAL;
}

// Model terminate function
void as_workflowModelClass::terminate()
{
  // (no terminate code required)
}

// Constructor
as_workflowModelClass::as_workflowModelClass() :
  as_workflow_U(),
  as_workflow_Y(),
  as_workflow_DW(),
  as_workflow_M()
{
  // Currently there is no constructor body generated.
}

// Destructor
as_workflowModelClass::~as_workflowModelClass()
{
  // Currently there is no destructor body generated.
}

// Real-Time Model get method
as_workflowModelClass::RT_MODEL_as_workflow_T * as_workflowModelClass::getRTM()
{
  return (&as_workflow_M);
}

//
// File trailer for generated code.
//
// [EOF]
//
