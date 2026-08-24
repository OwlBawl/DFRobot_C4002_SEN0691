#pragma once

#include "../dfrobot_c4002.h"
#include "esphome/core/component.h"
#include "esphome/components/text_sensor/text_sensor.h"

namespace esphome {
namespace dfrobot_c4002 {

class C4002TextSensorHub : public C4002Listener, public Component {
 public:
  void set_parent(C4002Component *parent) {
    this->parent_ = parent;
    if (parent != nullptr) {
      parent->register_listener(this);
    }
  }

  void set_text_sensor(text_sensor::TextSensor *ts) { this->text_sensor_ = ts; }
  void set_active_gates_summary_sensor(text_sensor::TextSensor *ts) { this->active_gates_summary_sensor_ = ts; }
  void set_movement_direction_sensor(text_sensor::TextSensor *ts) { this->movement_direction_sensor_ = ts; }

  void on_movement_direction(float direction) override {
    if (this->movement_direction_sensor_ != nullptr) {
      std::string dir_str = "No Direction";
      int d = (int) direction;
      if (d == 0) dir_str = "Away";
      else if (d == 1) dir_str = "No Direction";
      else if (d == 2) dir_str = "Approaching";

      if (this->movement_direction_sensor_->get_state() != dir_str) {
        this->movement_direction_sensor_->publish_state(dir_str);
      }
    }
  }

  void on_gates_summary(const std::string &summary) override {
    if (this->active_gates_summary_sensor_ != nullptr) {
      if (this->active_gates_summary_sensor_->get_state() != summary) {
        this->active_gates_summary_sensor_->publish_state(summary);
      }
    }
  }

  void publish(const std::string &msg) {
    if (this->text_sensor_ != nullptr) {
      this->text_sensor_->publish_state(msg);
    }
  }

 private:
  C4002Component *parent_{nullptr};
  text_sensor::TextSensor *text_sensor_{nullptr};
  text_sensor::TextSensor *active_gates_summary_sensor_{nullptr};
  text_sensor::TextSensor *movement_direction_sensor_{nullptr};
};

}  // namespace dfrobot_c4002
}  // namespace esphome
