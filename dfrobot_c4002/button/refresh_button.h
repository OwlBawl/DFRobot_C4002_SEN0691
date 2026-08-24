#pragma once

#include "../dfrobot_c4002.h"
#include "esphome/components/button/button.h"

namespace esphome {
namespace dfrobot_c4002 {

class C4002RefreshButton : public Component, public button::Button, public Parented<C4002Component> {
 public:
  C4002RefreshButton() = default;

 protected:
  void press_action() override {
    if (this->parent_ != nullptr) {
      this->parent_->update_config_param();
    }
  }
};

class C4002FactoryResetButton : public Component, public button::Button, public Parented<C4002Component> {
 public:
  C4002FactoryResetButton() = default;

 protected:
  void press_action() override {
    if (this->parent_ != nullptr) {
      this->parent_->factory_reset();
    }
  }
};

class C4002FactoryReset2Button : public Component, public button::Button, public Parented<C4002Component> {
 public:
  C4002FactoryReset2Button() = default;

 protected:
  void press_action() override {
    if (this->parent_ != nullptr) {
      this->parent_->factory_reset_2();
    }
  }
};

}  // namespace dfrobot_c4002
}  // namespace esphome
