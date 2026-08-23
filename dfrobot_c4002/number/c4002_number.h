#pragma once

#include "esphome/components/number/number.h"
#include "../dfrobot_c4002.h"

namespace esphome {
namespace dfrobot_c4002 {

class MinDetectRangeNumber : public number::Number, public Parented<C4002Component> {
 protected:
  void control(float value) override;
};

class MaxDetectRangeNumber : public number::Number, public Parented<C4002Component> {
 protected:
  void control(float value) override;
};

class LightThresholdNumber : public number::Number, public Parented<C4002Component> {
 protected:
  void control(float value) override;
};

// ===== Area 1 Excluded Range =====
class Area1MinRangeNumber : public Component, public number::Number, public Parented<C4002Component> {
 public:
  void setup() override;

 protected:
  void control(float value) override;
};

class Area1MaxRangeNumber : public Component, public number::Number, public Parented<C4002Component> {
 public:
  void setup() override;

 protected:
  void control(float value) override;
};

// ===== Area 2 Excluded Range =====
class Area2MinRangeNumber : public Component, public number::Number, public Parented<C4002Component> {
 public:
  void setup() override;

 protected:
  void control(float value) override;
};

class Area2MaxRangeNumber : public Component, public number::Number, public Parented<C4002Component> {
 public:
  void setup() override;

 protected:
  void control(float value) override;
};

// ===== Area 3 Excluded Range =====
class Area3MinRangeNumber : public Component, public number::Number, public Parented<C4002Component> {
 public:
  void setup() override;

 protected:
  void control(float value) override;
};

class Area3MaxRangeNumber : public Component, public number::Number, public Parented<C4002Component> {
 public:
  void setup() override;

 protected:
  void control(float value) override;
};

class TargetDisappeardDelayTimeNumber : public number::Number, public Parented<C4002Component> {
 protected:
  void control(float value) override;
};

class LockTimeNumber : public number::Number, public Parented<C4002Component> {
 protected:
  void control(float value) override;
};

class ReportPeriodNumber : public Component, public number::Number, public Parented<C4002Component> {
 public:
  void setup() override;

 protected:
  void control(float value) override;
};

}  // namespace dfrobot_c4002
}  // namespace esphome
