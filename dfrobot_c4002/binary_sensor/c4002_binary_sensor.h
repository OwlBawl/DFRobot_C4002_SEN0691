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

  void set_gate_binary_sensor(uint8_t gate, binary_sensor::BinarySensor *bs) {
    if (gate < 15) {
      this->gate_sensors_[gate] = bs;
    }
  }

  void on_active_gates(uint32_t bitmask) override {
    if (this->parent_ == nullptr || !this->parent_->get_show_gates_energy()) {
      return;
    }
    for (uint8_t i = 0; i < 15; i++) {
      if (this->gate_sensors_[i] != nullptr) {
        bool active = ((bitmask >> i) & 1) != 0;
        this->gate_sensors_[i]->publish_state(active);
      }
    }
  }

 protected:
  C4002Component *parent_{nullptr};
  binary_sensor::BinarySensor *gate_sensors_[15]{nullptr};
};

}  // namespace dfrobot_c4002
}  // namespace esphome
