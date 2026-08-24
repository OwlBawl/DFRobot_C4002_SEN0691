#include "c4002_switch.h"
#include "esphome/core/log.h"

namespace esphome {
namespace dfrobot_c4002 {

static const char *const TAG = "dfrobot_c4002.switch";

void C4002Switch1::setup() {
  auto initial_state = this->get_initial_state();
  if (initial_state.has_value()) {
    ESP_LOGD(TAG, "Restoring Out LED switch state: %s", *initial_state ? "ON" : "OFF");
    this->write_state(*initial_state);
  }
}

void C4002Switch1::write_state(bool state) {
  bool send_flag = false;
  if (this->parent_) {
    if (state) {
      send_flag = this->parent_->set_out_led(LED_ON);
    } else {
      send_flag = this->parent_->set_out_led(LED_OFF);
    }
    if (send_flag) {
      this->publish_state(state);
    } else {
      ESP_LOGW(TAG, "Out LED command failed");
    }
  }
}

void C4002Switch2::setup() {
  auto initial_state = this->get_initial_state();
  if (initial_state.has_value()) {
    ESP_LOGD(TAG, "Restoring Run LED switch state: %s", *initial_state ? "ON" : "OFF");
    this->write_state(*initial_state);
  }
}

void C4002Switch2::write_state(bool state) {
  bool send_flag = false;
  if (this->parent_) {
    if (state) {
      send_flag = this->parent_->set_run_led(LED_ON);
    } else {
      send_flag = this->parent_->set_run_led(LED_OFF);
    }
    if (send_flag) {
      this->publish_state(state);
    } else {
      ESP_LOGW(TAG, "Run LED command failed");
    }
  }
}

void C4002SwitchFactoryReset::write_state(bool state) {
  if (this->parent_) {
    if (state) {
      this->publish_state(true);
      bool send_flag = this->parent_->factory_reset();
      ESP_LOGW(TAG, "Factory reset: %d", send_flag);

      if (send_flag) {
        this->set_timeout(1500, [this]() {
          this->publish_state(false);
          ESP_LOGD(TAG, "Factory reset completed, switch auto-reset to OFF");
        });
      } else {
        ESP_LOGW(TAG, "Factory reset command failed");
        this->publish_state(false);
      }
    } else {
      this->publish_state(false);
    }
  }
}

void C4002SwitchEnvironmentalCalibration::write_state(bool state) {
  if (this->parent_) {
    if (state) {
      this->parent_->start_env_calibration(3, 15);
      this->publish_state(true);
    } else {
      this->publish_state(false);
      this->parent_->update_config_param();
    }
  }
}

void C4002SwitchShowGatesEnergy::setup() {
  this->publish_state(false);
}

void C4002SwitchShowGatesEnergy::write_state(bool state) {
  if (this->parent_) {
    this->cancel_timeout("active_gates_auto_disable");
    this->parent_->set_show_gates_energy(state);
    this->publish_state(state);
    if (state) {
      this->set_timeout("active_gates_auto_disable", 5 * 60 * 1000, [this]() {
        this->write_state(false);
      });
    }
  }
}

}  // namespace dfrobot_c4002
}  // namespace esphome
