//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: as_workflow.cpp
//
// Code generated for Simulink model 'as_workflow'.
//
// Model version                  : 1.19
// Simulink Coder version         : 9.6 (R2021b) 14-May-2021
// C/C++ source code generated on : Sat Feb 12 15:35:21 2022
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

// System initialize for function-call system: '<S1>/IS_BRAKE_PRESSURE_RELEASED'
void as_workflowModelClass::IS_BRAKE_PRESSURE_RELEASED_Init(boolean_T
  *rty_IS_BRAKE_PRESSURE_RELEASED)
{
  // SystemInitialize for Merge: '<S7>/Merge'
  *rty_IS_BRAKE_PRESSURE_RELEASED = false;
}

// Output and update for function-call system: '<S1>/IS_BRAKE_PRESSURE_RELEASED'
void as_workflowModelClass::as_w_IS_BRAKE_PRESSURE_RELEASED(real_T
  rtu_FRONT_BRAKE, real_T rtu_REAR_BRAKE, boolean_T
  *rty_IS_BRAKE_PRESSURE_RELEASED)
{
  // Outputs for IfAction SubSystem: '<S7>/If Action Subsystem1' incorporates:
  //   ActionPort: '<S9>/Action Port'

  // Outputs for IfAction SubSystem: '<S7>/If Action Subsystem2' incorporates:
  //   ActionPort: '<S10>/Action Port'

  // Outputs for IfAction SubSystem: '<S7>/If Action Subsystem' incorporates:
  //   ActionPort: '<S8>/Action Port'

  // If: '<S7>/If' incorporates:
  //   Inport: '<S10>/In1'
  //   Inport: '<S8>/In1'
  //   Inport: '<S9>/In1'

  *rty_IS_BRAKE_PRESSURE_RELEASED = (((rtu_FRONT_BRAKE < 2.0) && (rtu_REAR_BRAKE
    < 2.0)) || ((rtu_FRONT_BRAKE < 2.0) || (rtu_REAR_BRAKE < 2.0)));

  // End of Outputs for SubSystem: '<S7>/If Action Subsystem'
  // End of Outputs for SubSystem: '<S7>/If Action Subsystem2'
  // End of Outputs for SubSystem: '<S7>/If Action Subsystem1'
}

// Model step function
void as_workflowModelClass::step()
{
  boolean_T out;

  // Chart: '<Root>/Chart' incorporates:
  //   If: '<S4>/If'
  //   Inport: '<Root>/EBS'
  //   Inport: '<Root>/FRONT_BRAKE'
  //   Inport: '<Root>/IS_ASMS_ON'
  //   Inport: '<Root>/IS_MISSION_FINISHED'
  //   Inport: '<Root>/IS_RES_GO'
  //   Inport: '<Root>/IS_RES_TRIGGERED'
  //   Inport: '<Root>/IS_TS_ON'
  //   Inport: '<Root>/MISSION_STATUS'
  //   Inport: '<Root>/REAR_BRAKE'

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
      if (!as_workflow_U.IS_ASMS_ON) {
        // Outputs for Function Call SubSystem: '<S1>/IS_BRAKE_PRESSURE_RELEASED' 
        as_w_IS_BRAKE_PRESSURE_RELEASED(as_workflow_U.FRONT_BRAKE,
          as_workflow_U.REAR_BRAKE, &out);

        // End of Outputs for SubSystem: '<S1>/IS_BRAKE_PRESSURE_RELEASED'
      } else {
        out = false;
      }

      if (out) {
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
      } else {
        if (!as_workflow_U.IS_ASMS_ON) {
          // Outputs for Function Call SubSystem: '<S1>/IS_BRAKE_PRESSURE_RELEASED' 
          as_w_IS_BRAKE_PRESSURE_RELEASED(as_workflow_U.FRONT_BRAKE,
            as_workflow_U.REAR_BRAKE, &out);

          // End of Outputs for SubSystem: '<S1>/IS_BRAKE_PRESSURE_RELEASED'
        } else {
          out = false;
        }

        if (out) {
          as_workflow_DW.is_c3_as_workflow = as_workflow_IN_AS_OFF;
        } else {
          // Outport: '<Root>/AS_STATUS_OUT'
          as_workflow_Y.AS_STATUS_OUT = AS_STATE_AS_FINISHED;

          // Outport: '<Root>/SA_OUT'
          as_workflow_Y.SA_OUT = SA_STATE_UNAVAILABLE;

          // Outport: '<Root>/ASSI_OUT'
          as_workflow_Y.ASSI_OUT = ASSI_STATE_FINISHED;
        }
      }
      break;

     case as_workflow_IN_AS_OFF:
      if ((as_workflow_U.MISSION_STATUS == MISSION_MANUAL) &&
          as_workflow_U.IS_TS_ON && (!as_workflow_U.IS_ASMS_ON)) {
        as_workflow_DW.is_c3_as_workflow = as_workflow_IN_MANUAL_DRIVING;
      } else {
        if ((as_workflow_U.EBS == EBS_STATE_ARMED) &&
            (as_workflow_U.MISSION_STATUS == MISSION_AUTONOMOUS) &&
            as_workflow_U.IS_TS_ON && as_workflow_U.IS_ASMS_ON) {
          // Outputs for Function Call SubSystem: '<S1>/IS_BRAKE_PRESSURE_OK'
          out = ((as_workflow_U.FRONT_BRAKE > 30.0) && (as_workflow_U.REAR_BRAKE
                  > 30.0));

          // End of Outputs for SubSystem: '<S1>/IS_BRAKE_PRESSURE_OK'
        } else {
          out = false;
        }

        if (out) {
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

          // Outputs for Function Call SubSystem: '<S1>/IS_BRAKE_PRESSURE_RELEASED' 
          // Outport: '<Root>/BRAKE_PRESSURE_RELEASED_OUT'
          as_w_IS_BRAKE_PRESSURE_RELEASED(as_workflow_U.FRONT_BRAKE,
            as_workflow_U.REAR_BRAKE, &as_workflow_Y.BRAKE_PRESSURE_RELEASED_OUT);

          // End of Outputs for SubSystem: '<S1>/IS_BRAKE_PRESSURE_RELEASED'
        }
      }
      break;

     case as_workflow_IN_AS_READY:
      if (!as_workflow_U.IS_ASMS_ON) {
        // Outputs for Function Call SubSystem: '<S1>/IS_BRAKE_PRESSURE_RELEASED' 
        as_w_IS_BRAKE_PRESSURE_RELEASED(as_workflow_U.FRONT_BRAKE,
          as_workflow_U.REAR_BRAKE, &out);

        // End of Outputs for SubSystem: '<S1>/IS_BRAKE_PRESSURE_RELEASED'
      } else {
        out = false;
      }

      if (out) {
        as_workflow_DW.is_c3_as_workflow = as_workflow_IN_AS_OFF;
      } else if ((as_workflow_DW.temporalCounter_i1 >= 50U) &&
                 (as_workflow_U.IS_RES_GO != 0.0)) {
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

  {
    boolean_T Merge_k;

    // SystemInitialize for Chart: '<Root>/Chart' incorporates:
    //   SubSystem: '<S1>/IS_BRAKE_PRESSURE_RELEASED'

    IS_BRAKE_PRESSURE_RELEASED_Init(&Merge_k);
  }
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
