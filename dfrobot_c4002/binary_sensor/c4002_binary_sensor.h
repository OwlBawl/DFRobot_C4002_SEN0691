#pragma once

#include "../dfrobot_c4002.h"
#include "esphome/components/binary_sensor/binary_sensor.h"

namespace esphome {
namespace dfrobot_c4002 {

class C4002BinarySensorHub : public C4002Listener, public Component {
 public:
  void set_parent(C4002Component *parent) {
    this->parent_ = parent;
    if (parent != nullptr) {
      parent->register_listener(this);
    }
  }

  void setup() override {
    if (this->motion_sensor_ != nullptr) {
      this->motion_sensor_->publish_initial_state(false);
    }
    if (this->presence_sensor_ != nullptr) {
      this->presence_sensor_->publish_initial_state(false);
    }
  }

  void set_motion_binary_sensor(binary_sensor::BinarySensor *bs) { this->motion_sensor_ = bs; }
  void set_presence_binary_sensor(binary_sensor::BinarySensor *bs) { this->presence_sensor_ = bs; }

  void on_target_status(uint8_t state) override {
    // 0 = NO_BODY, 1 = EXIST (Static), 2 = MOVE (Motion), 3 = BOTH
    bool has_motion = (state == 2 || state == 3);
    bool has_presence = (state == 1 || state == 3);

    if (this->motion_sensor_ != nullptr) {
      if (this->motion_sensor_->state != has_motion) {
        this->motion_sensor_->publish_state(has_motion);
      }
    }
    if (this->presence_sensor_ != nullptr) {
      if (this->presence_sensor_->state != has_presence) {
        this->presence_sensor_->publish_state(has_presence);
      }
    }
  }

 protected:
  C4002Component *parent_{nullptr};
  binary_sensor::BinarySensor *motion_sensor_{nullptr};
  binary_sensor::BinarySensor *presence_sensor_{nullptr};
};

}  // namespace dfrobot_c4002
}  // namespace esphome
