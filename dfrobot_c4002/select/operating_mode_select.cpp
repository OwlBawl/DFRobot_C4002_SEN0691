#include "operating_mode_select.h"
#include "esphome/core/helpers.h"
#include "esphome/core/log.h"
#include <cstdio>
#include <string>
#include <vector>

namespace esphome {
namespace dfrobot_c4002 {

static const char *const TAG = "dfrobot_c4002.select";

void C4002Select::control(const std::string &value) {
  if (this->parent_) {
    if (value == "Motion Only" || value == "Mode_1") {
      ESP_LOGD(TAG, "Setting output mode to Motion Only");
      this->parent_->set_out_mode(OUT_MODE1);
      this->publish_state(value);
    } else if (value == "Presence Only" || value == "Mode_2") {
      ESP_LOGD(TAG, "Setting output mode to Presence Only");
      this->parent_->set_out_mode(OUT_MODE2);
      this->publish_state(value);
    } else if (value == "Motion OR Presence" || value == "Mode_3") {
      ESP_LOGD(TAG, "Setting output mode to Motion OR Presence");
      this->parent_->set_out_mode(OUT_MODE3);
      this->publish_state(value);
    }
  }
}

void MotionSensitivitySelect::control(const std::string &value) {
  if (this->parent_) {
    SensitivityLevel level = SENS_MID;
    if (value == "Low") {
      level = SENS_LOW;
    } else if (value == "Medium") {
      level = SENS_MID;
    } else if (value == "High") {
      level = SENS_HIGH;
    } else if (value == "Custom") {
      level = SENS_CUSTOM;
    }
    if (this->parent_->set_sensitivity(MOVE_DIST_DOOR, level)) {
      ESP_LOGD(TAG, "Set motion sensitivity to %s", value.c_str());
      this->publish_state(value);
    } else {
      ESP_LOGD(TAG, "Set motion sensitivity failed");
    }
  }
}

void PresenceSensitivitySelect::control(const std::string &value) {
  if (this->parent_) {
    SensitivityLevel level = SENS_MID;
    if (value == "Low") {
      level = SENS_LOW;
    } else if (value == "Medium") {
      level = SENS_MID;
    } else if (value == "High") {
      level = SENS_HIGH;
    } else if (value == "Custom") {
      level = SENS_CUSTOM;
    }
    if (this->parent_->set_sensitivity(EXIST_DIST_DOOR, level)) {
      ESP_LOGD(TAG, "Set presence sensitivity to %s", value.c_str());
      this->publish_state(value);
    } else {
      ESP_LOGD(TAG, "Set presence sensitivity failed");
    }
  }
}

void ResolutionModeSelect::control(const std::string &value) {
  if (this->parent_) {
    ResolutionMode mode = (value == "20cm") ? RESOLUTION_20CM : RESOLUTION_80CM;
    if (this->parent_->set_resolution_mode(mode)) {
      ESP_LOGD(TAG, "Set resolution mode to %s", value.c_str());
      this->publish_state(value);
    } else {
      ESP_LOGD(TAG, "Set resolution mode failed");
    }
  }
}

void GateSelect::control(const std::string &value) {
  if (this->parent_) {
    int gate_idx = 0;
    if (sscanf(value.c_str(), "Gate %d", &gate_idx) == 1) {
      if (gate_idx >= 0 && gate_idx < 15) {
        this->parent_->select_gate_to_edit((uint8_t) gate_idx);
        this->publish_state(value);
      }
    }
  }
}

}  // namespace dfrobot_c4002
}  // namespace esphome
