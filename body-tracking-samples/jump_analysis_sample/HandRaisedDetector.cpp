// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "HandRaisedDetector.h"

using namespace std::chrono;

void HandRaisedDetector::UpdateData(k4abt_body_t selectedBody, uint64_t currentTimestampUsec)
{
    k4a_float3_t leftWristJoint = selectedBody.skeleton.joints[K4ABT_JOINT_WRIST_LEFT].position;
    k4a_float3_t rightWristJoint = selectedBody.skeleton.joints[K4ABT_JOINT_WRIST_RIGHT].position;
    k4a_float3_t headJoint = selectedBody.skeleton.joints[K4ABT_JOINT_HEAD].position;
    k4a_float3_t leftElbow = selectedBody.skeleton.joints[K4ABT_JOINT_ELBOW_LEFT].position;
    k4a_float3_t rightElbow = selectedBody.skeleton.joints[K4ABT_JOINT_ELBOW_RIGHT].position;
    k4a_float3_t leftShoulder = selectedBody.skeleton.joints[K4ABT_JOINT_SHOULDER_LEFT].position;
    k4a_float3_t rightShoulder = selectedBody.skeleton.joints[K4ABT_JOINT_SHOULDER_RIGHT].position;
    k4a_float3_t leftHip = selectedBody.skeleton.joints[K4ABT_JOINT_HIP_LEFT].position;
    k4a_float3_t rightHip = selectedBody.skeleton.joints[K4ABT_JOINT_HIP_RIGHT].position;
    k4a_float3_t leftKnee = selectedBody.skeleton.joints[K4ABT_JOINT_KNEE_LEFT].position;
    k4a_float3_t rightKnee = selectedBody.skeleton.joints[K4ABT_JOINT_KNEE_RIGHT].position;

    k4a_float3_t leftFoot = selectedBody.skeleton.joints[K4ABT_JOINT_FOOT_LEFT].position;
    k4a_float3_t rightFoot = selectedBody.skeleton.joints[K4ABT_JOINT_FOOT_RIGHT].position;

    // Notice: y direction is pointing towards the ground! So jointA.y < jointB.y means jointA is higher than jointB
    bool bothHandsAreRaised = leftWristJoint.xyz.y < headJoint.xyz.y &&
                               rightWristJoint.xyz.y < headJoint.xyz.y;

    if (leftFoot.xyz.y - rightFoot.xyz.y > m_level)
    {
        m_key2Pressed = true;
        m_key1Pressed = false;
    }

    if (rightFoot.xyz.y - leftFoot.xyz.y > m_level)
    {
        m_key1Pressed = true;
        m_key2Pressed = false;
    }

    //m_key1Pressed = leftKnee.xyz.y - m_level < leftHip.xyz.y;
    //m_key2Pressed = rightKnee.xyz.y - m_level < rightHip.xyz.y;
    //m_key3Pressed = leftWristJoint.xyz.y < leftShoulder.xyz.y;
    //m_key4Pressed = rightWristJoint.xyz.y < rightShoulder.xyz.y;
    //m_key5Pressed = leftWristJoint.xyz.y < headJoint.xyz.y;
    //m_key6Pressed = rightWristJoint.xyz.y < headJoint.xyz.y;

    microseconds currentTimestamp(currentTimestampUsec);
    if (m_previousTimestamp == microseconds::zero())
    {
        m_previousTimestamp = currentTimestamp;
        m_handRaisedTimeSpan = microseconds::zero();
    }

    if (!m_bothHandsAreRaised && bothHandsAreRaised)
    {
        // Start accumulating the hand raising time
        m_handRaisedTimeSpan += currentTimestamp - m_previousTimestamp;
        if (m_handRaisedTimeSpan > m_stableTime)
        {
            m_bothHandsAreRaised = bothHandsAreRaised;
        }
    }
    else if (!bothHandsAreRaised)
    {
        // Stop the time accumulation immediately when hands are put down
        m_bothHandsAreRaised = false;
        m_previousTimestamp = microseconds::zero();
        m_handRaisedTimeSpan = microseconds::zero();
    }
}
