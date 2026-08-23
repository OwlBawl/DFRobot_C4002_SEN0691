#pragma once

#include "../dfrobot_c4002.h"
#include "esphome/components/select/select.h"

namespace esphome {
namespace dfrobot_c4002 {

class C4002Select : public Component, public select::Select, public Parented<C4002Component> {
 public:
  C4002Select() = default;

 protected:
  void control(const std::string &value) override;
  std::string options_[3] = {"Motion Only", "Presence Only", "Motion OR Presence"};
};

class MotionSensitivitySelect : public Component, public select::Select, public Parented<C4002Component> {
 public:
  MotionSensitivitySelect() = default;

 protected:
  void control(const std::string &value) override;
};

class PresenceSensitivitySelect : public Component, public select::Select, public Parented<C4002Component> {
 public:
  PresenceSensitivitySelect() = default;

 protected:
  void control(const std::string &value) override;
};

class ResolutionModeSelect : public Component, public select::Select, public Parented<C4002Component> {
 public:
  ResolutionModeSelect() = default;

 protected:
  void control(const std::string &value) override;
};

class GateSelect : public Component, public select::Select, public Parented<C4002Component> {
 public:
  GateSelect() = default;

 protected:
  void control(const std::string &value) override;
};

}  // namespace dfrobot_c4002
}  // namespace esphome
