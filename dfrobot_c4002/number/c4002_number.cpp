#include "c4002_number.h"
#include "esphome/core/helpers.h"
#include "esphome/core/log.h"

namespace esphome {
namespace dfrobot_c4002 {

static const char *const TAG = "dfrobot_c4002.number";

// ===== 最小探测距离 =====
void MinDetectRangeNumber::control(float value) {
  if (this->parent_) {
    float max_range = this->parent_->get_max_detect_range_number();
    if (value <= max_range) {
      if (this->parent_->set_min_range(value)) {
        this->publish_state(value);
      } else {
        this->publish_state(this->parent_->get_min_detect_range_number());
      }
    } else {
      this->publish_state(this->parent_->get_min_detect_range_number());
    }
  }
}

// ===== 最大探测距离 =====
void MaxDetectRangeNumber::control(float value) {
  if (this->parent_) {
    float min_range = this->parent_->get_min_detect_range_number();
    if (value >= min_range) {
      if (this->parent_->set_max_range(value)) {
        this->publish_state(value);
      } else {
        this->publish_state(this->parent_->get_max_detect_range_number());
      }
    } else {
      this->publish_state(this->parent_->get_max_detect_range_number());
    }
  }
}

// ===== 光照阈值 =====
void LightThresholdNumber::control(float value) {
  if (this->parent_) {
    if (this->parent_->set_light_threshold(value)) {
      this->publish_state(value);
    } else {
      this->publish_state(0.0);
    }
  }
}

// ===== 区域 1 =====
void Area1MinRangeNumber::control(float value) {
  if (this->parent_) {
    float area1_min = this->parent_->get_area_range(AREA1_DOOR_MIN);
    float area1_max = this->parent_->get_area_range(AREA1_DOOR_MAX);

    if (value <= area1_max) {
      this->parent_->set_area_range(AREA1_DOOR_MIN, value);
      if (this->parent_->joint_enable_door()) {
        this->publish_state(value);
      } else {
        this->publish_state(area1_min);
        this->parent_->set_area_range(AREA1_DOOR_MIN, area1_min);
      }
    } else {
      this->publish_state(area1_min);
      this->parent_->set_area_range(AREA1_DOOR_MIN, area1_min);
    }
  }
}

void Area1MaxRangeNumber::control(float value) {
  if (this->parent_) {
    float area1_min = this->parent_->get_area_range(AREA1_DOOR_MIN);
    float area1_max = this->parent_->get_area_range(AREA1_DOOR_MAX);

    if (value >= area1_min) {
      this->parent_->set_area_range(AREA1_DOOR_MAX, value);
      if (this->parent_->joint_enable_door()) {
        this->publish_state(value);
      } else {
        this->publish_state(area1_max);
        this->parent_->set_area_range(AREA1_DOOR_MAX, area1_max);
      }
    } else {
      this->publish_state(area1_max);
      this->parent_->set_area_range(AREA1_DOOR_MAX, area1_max);
    }
  }
}

// ===== 区域 2 =====
void Area2MinRangeNumber::control(float value) {
  if (this->parent_) {
    float area2_min = this->parent_->get_area_range(AREA2_DOOR_MIN);
    float area2_max = this->parent_->get_area_range(AREA2_DOOR_MAX);

    if (value <= area2_max) {
      this->parent_->set_area_range(AREA2_DOOR_MIN, value);
      if (this->parent_->joint_enable_door()) {
        this->publish_state(value);
      } else {
        this->publish_state(area2_min);
        this->parent_->set_area_range(AREA2_DOOR_MIN, area2_min);
      }
    } else {
      this->publish_state(area2_min);
      this->parent_->set_area_range(AREA2_DOOR_MIN, area2_min);
    }
  }
}

void Area2MaxRangeNumber::control(float value) {
  if (this->parent_) {
    float area2_min = this->parent_->get_area_range(AREA2_DOOR_MIN);
    float area2_max = this->parent_->get_area_range(AREA2_DOOR_MAX);

    if (value >= area2_min) {
      this->parent_->set_area_range(AREA2_DOOR_MAX, value);
      if (this->parent_->joint_enable_door()) {
        this->publish_state(value);
      } else {
        this->publish_state(area2_max);
        this->parent_->set_area_range(AREA2_DOOR_MAX, area2_max);
      }
    } else {
      this->publish_state(area2_max);
      this->parent_->set_area_range(AREA2_DOOR_MAX, area2_max);
    }
  }
}

// ===== 区域 3 =====
void Area3MinRangeNumber::control(float value) {
  if (this->parent_) {
    float area3_min = this->parent_->get_area_range(AREA3_DOOR_MIN);
    float area3_max = this->parent_->get_area_range(AREA3_DOOR_MAX);

    if (value <= area3_max) {
      this->parent_->set_area_range(AREA3_DOOR_MIN, value);
      if (this->parent_->joint_enable_door()) {
        this->publish_state(value);
      } else {
        this->publish_state(area3_min);
        this->parent_->set_area_range(AREA3_DOOR_MIN, area3_min);
      }
    } else {
      this->publish_state(area3_min);
      this->parent_->set_area_range(AREA3_DOOR_MIN, area3_min);
    }
  }
}

void Area3MaxRangeNumber::control(float value) {
  if (this->parent_) {
    float area3_min = this->parent_->get_area_range(AREA3_DOOR_MIN);
    float area3_max = this->parent_->get_area_range(AREA3_DOOR_MAX);

    if (value >= area3_min) {
      this->parent_->set_area_range(AREA3_DOOR_MAX, value);
      if (this->parent_->joint_enable_door()) {
        this->publish_state(value);
      } else {
        this->publish_state(area3_max);
        this->parent_->set_area_range(AREA3_DOOR_MAX, area3_max);
      }
    } else {
      this->publish_state(area3_max);
      this->parent_->set_area_range(AREA3_DOOR_MAX, area3_max);
    }
  }
}

void TargetDisappeardDelayTimeNumber::control(float value) {
  if (this->parent_) {
    if (this->parent_->set_target_disappear_delay(value)) {
      this->publish_state(value);
    } else {
      this->publish_state(NAN);
    }
  }
}

void LockTimeNumber::control(float value) {
  if (this->parent_) {
    if (this->parent_->set_lock_time(value)) {
      this->publish_state(value);
    } else {
      this->publish_state(NAN);
    }
  }
}

void ReportPeriodNumber::control(float value) {
  if (this->parent_) {
    uint8_t period_units = (uint8_t) (value * 10);
    if (this->parent_->set_report_period(period_units)) {
      this->publish_state(value);
    } else {
      this->publish_state(NAN);
    }
  }
}

void GateMotionThresholdNumber::control(float value) {
  if (this->parent_) {
    if (this->gate_index_ >= this->parent_->get_gate_count()) {
      this->publish_state(NAN);
      return;
    }
    if (this->parent_->set_single_gate_thresh(MOVE_DIST_DOOR, this->gate_index_, (uint8_t) value)) {
      this->publish_state(value);
    } else {
      this->publish_state(this->parent_->get_cached_gate_thresh(MOVE_DIST_DOOR, this->gate_index_));
    }
  }
}

void GatePresenceThresholdNumber::control(float value) {
  if (this->parent_) {
    if (this->gate_index_ >= this->parent_->get_gate_count()) {
      this->publish_state(NAN);
      return;
    }
    if (this->parent_->set_single_gate_thresh(EXIST_DIST_DOOR, this->gate_index_, (uint8_t) value)) {
      this->publish_state(value);
    } else {
      this->publish_state(this->parent_->get_cached_gate_thresh(EXIST_DIST_DOOR, this->gate_index_));
    }
  }
}

}  // namespace dfrobot_c4002
}  // namespace esphome
