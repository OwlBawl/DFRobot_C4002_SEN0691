#pragma once

#include "../dfrobot_c4002.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace dfrobot_c4002 {

class C4002Sensor : public C4002Listener, public Component, sensor::Sensor {
 public:
  void setup() override {
    if (movement_distance_)
      this->movement_distance_->publish_state(0.0f);
    if (existing_distance_)
      this->existing_distance_->publish_state(0.0f);
    if (movement_speed_)
      this->movement_speed_->publish_state(0.0f);
    if (movement_direction_)
      this->movement_direction_->publish_state(0.0f);
    if (target_status_)
      this->target_status_->publish_state(0.0f);
    if (illuminance_)
      this->illuminance_->publish_state(0.0f);
    if (movement_energy_)
      this->movement_energy_->publish_state(0.0f);
    if (existing_energy_)
      this->existing_energy_->publish_state(0.0f);
    if (presence_countdown_)
      this->presence_countdown_->publish_state(0.0f);
    if (active_gates_)
      this->active_gates_->publish_state(0.0f);
  }
  void set_movement_distance_sensor(sensor::Sensor *sensor) { this->movement_distance_ = sensor; }
  void set_existing_distance_sensor(sensor::Sensor *sensor) { this->existing_distance_ = sensor; }
  void set_movement_speed_sensor(sensor::Sensor *sensor) { this->movement_speed_ = sensor; }
  void set_movement_direction_sensor(sensor::Sensor *sensor) { this->movement_direction_ = sensor; }
  void set_target_status_sensor(sensor::Sensor *sensor) { this->target_status_ = sensor; }
  void set_illuminance_sensor(sensor::Sensor *sensor) { this->illuminance_ = sensor; }
  void set_movement_energy_sensor(sensor::Sensor *sensor) { this->movement_energy_ = sensor; }
  void set_existing_energy_sensor(sensor::Sensor *sensor) { this->existing_energy_ = sensor; }
  void set_presence_countdown_sensor(sensor::Sensor *sensor) { this->presence_countdown_ = sensor; }
  void set_active_gates_sensor(sensor::Sensor *sensor) { this->active_gates_ = sensor; }

  void on_movement_distance(float distance) override {
    if (this->movement_distance_ != nullptr) {
      if (this->movement_distance_->get_state() != distance) {
        this->movement_distance_->publish_state(distance);
      }
    }
  }

  void on_existing_distance(float distance) override {
    if (this->existing_distance_ != nullptr) {
      if (this->existing_distance_->get_state() != distance) {
        this->existing_distance_->publish_state(distance);
      }
    }
  }

  void on_movement_speed(float speed) override {
    if (this->movement_speed_ != nullptr) {
      if (this->movement_speed_->get_state() != speed) {
        this->movement_speed_->publish_state(speed);
      }
    }
  }

  void on_movement_direction(float direction) override {
    if (this->movement_direction_ != nullptr) {
      if (this->movement_direction_->get_state() != direction) {
        this->movement_direction_->publish_state(direction);
      }
    }
  }

  void on_target_status(uint8_t state) override {
    if (this->target_status_ != nullptr) {
      if (this->target_status_->get_state() != state) {
        this->target_status_->publish_state(state);
      }
    }
  }

  void on_illuminance(float lux) override {
    if (this->illuminance_ != nullptr) {
      if (this->illuminance_->get_state() != lux) {
        this->illuminance_->publish_state(lux);
      }
    }
  }

  void on_movement_energy(uint8_t energy) override {
    if (this->movement_energy_ != nullptr) {
      if (this->movement_energy_->get_state() != energy) {
        this->movement_energy_->publish_state(energy);
      }
    }
  }

  void on_existing_energy(uint8_t energy) override {
    if (this->existing_energy_ != nullptr) {
      if (this->existing_energy_->get_state() != energy) {
        this->existing_energy_->publish_state(energy);
      }
    }
  }

  void on_presence_countdown(uint16_t seconds) override {
    if (this->presence_countdown_ != nullptr) {
      if (this->presence_countdown_->get_state() != seconds) {
        this->presence_countdown_->publish_state(seconds);
      }
    }
  }

  void on_active_gates(uint32_t bitmask) override {
    if (this->active_gates_ != nullptr) {
      if (this->active_gates_->get_state() != bitmask) {
        this->active_gates_->publish_state(bitmask);
      }
    }
  }

 protected:
  sensor::Sensor *movement_distance_{nullptr};
  sensor::Sensor *existing_distance_{nullptr};
  sensor::Sensor *movement_speed_{nullptr};
  sensor::Sensor *movement_direction_{nullptr};
  sensor::Sensor *target_status_{nullptr};
  sensor::Sensor *illuminance_{nullptr};
  sensor::Sensor *movement_energy_{nullptr};
  sensor::Sensor *existing_energy_{nullptr};
  sensor::Sensor *presence_countdown_{nullptr};
  sensor::Sensor *active_gates_{nullptr};
};

}  // namespace dfrobot_c4002
}  // namespace esphome
