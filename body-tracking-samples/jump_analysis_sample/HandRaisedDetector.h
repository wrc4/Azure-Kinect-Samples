// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once

#include <k4abttypes.h>
#include <chrono>

class HandRaisedDetector
{
public:
    void UpdateData(k4abt_body_t selectedBody, uint64_t currentTimestampUsec);

    bool AreBothHandsRaised() { return m_bothHandsAreRaised; }

    bool Key1Pressed() { return m_key1Pressed;  }

    bool Key1Repeating() { return m_key1Repeating;  }

    bool Key2Pressed() { return m_key2Pressed; }

    bool Key2Repeating() { return m_key2Repeating; }

    bool Key3Pressed() { return m_key3Pressed; }

    bool Key3Repeating() { return m_key3Repeating; }

    bool Key4Pressed() { return m_key4Pressed; }

    bool Key4Repeating() { return m_key4Repeating; }

    bool Key5Pressed() { return m_key5Pressed; }

    bool Key5Repeating() { return m_key5Repeating; }

    bool Key6Pressed() { return m_key6Pressed; }

    bool Key6Repeating() { return m_key6Repeating; }

    void setLevel(int level) { m_level = level; }

private:
    int m_level = 0;
    bool m_key1Pressed = false;
    bool m_key1Repeating = false;
    bool m_key2Pressed = false;
    bool m_key2Repeating = false;
    bool m_key3Pressed = false;
    bool m_key3Repeating = false;
    bool m_key4Pressed = false;
    bool m_key4Repeating = false;
    bool m_key5Pressed = false;
    bool m_key5Repeating = false;
    bool m_key6Pressed = false;
    bool m_key6Repeating = false;
    bool m_bothHandsAreRaised = false;
    std::chrono::microseconds m_handRaisedTimeSpan = std::chrono::microseconds::zero();
    std::chrono::microseconds m_previousTimestamp = std::chrono::microseconds::zero();
    const std::chrono::seconds m_stableTime = std::chrono::seconds(2);
};