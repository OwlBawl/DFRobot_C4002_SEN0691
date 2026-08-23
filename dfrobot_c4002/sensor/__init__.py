import esphome.codegen as cg
from esphome.components import sensor
import esphome.config_validation as cv
from esphome.const import (
    CONF_ID,
    CONF_ILLUMINANCE,
    DEVICE_CLASS_DISTANCE,
    DEVICE_CLASS_DURATION,
    DEVICE_CLASS_ILLUMINANCE,
    DEVICE_CLASS_SPEED,
    ICON_RULER,
    UNIT_LUX,
    UNIT_METER,
    UNIT_PERCENT,
    UNIT_SECOND,
)

from .. import CONF_C4002_ID, C4002Component, dfrobot_c4002_ns

C4002Sensor = dfrobot_c4002_ns.class_("C4002Sensor", cg.Component)

CONF_MOVEMENT_DISTANCE = "movement_distance"
CONF_EXISTING_DISTANCE = "existing_distance"
CONF_MOVEMENT_SPEED = "movement_speed"
CONF_MOVEMENT_DIRECTION = "movement_direction"
CONF_TARGET_STATUS = "target_status"
CONF_MOVEMENT_ENERGY = "movement_energy"
CONF_EXISTING_ENERGY = "existing_energy"
CONF_PRESENCE_COUNTDOWN = "presence_countdown"
CONF_ACTIVE_GATES = "active_gates"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(C4002Sensor),
        cv.Required(CONF_C4002_ID): cv.use_id(C4002Component),
        cv.Optional(CONF_MOVEMENT_DISTANCE): sensor.sensor_schema(
            device_class=DEVICE_CLASS_DISTANCE,
            unit_of_measurement=UNIT_METER,
            icon=ICON_RULER,
            accuracy_decimals=1,
        ),
        cv.Optional(CONF_EXISTING_DISTANCE): sensor.sensor_schema(
            device_class=DEVICE_CLASS_DISTANCE,
            unit_of_measurement=UNIT_METER,
            icon=ICON_RULER,
            accuracy_decimals=1,
        ),
        cv.Optional(CONF_MOVEMENT_SPEED): sensor.sensor_schema(
            device_class=DEVICE_CLASS_SPEED,
            unit_of_measurement="m/s",
            icon="mdi:speedometer",
            accuracy_decimals=1,
        ),
        cv.Optional(CONF_MOVEMENT_DIRECTION): sensor.sensor_schema(
            icon="mdi:compass",
            accuracy_decimals=1,
        ),
        cv.Optional(CONF_TARGET_STATUS): sensor.sensor_schema(
            icon="mdi:target",
        ),
        cv.Optional(CONF_ILLUMINANCE): sensor.sensor_schema(
            device_class=DEVICE_CLASS_ILLUMINANCE,
            unit_of_measurement=UNIT_LUX,
            icon="mdi:brightness-5",
            accuracy_decimals=1,
        ),
        cv.Optional(CONF_MOVEMENT_ENERGY): sensor.sensor_schema(
            unit_of_measurement=UNIT_PERCENT,
            icon="mdi:lightning-bolt",
            accuracy_decimals=0,
        ),
        cv.Optional(CONF_EXISTING_ENERGY): sensor.sensor_schema(
            unit_of_measurement=UNIT_PERCENT,
            icon="mdi:lightning-bolt-outline",
            accuracy_decimals=0,
        ),
        cv.Optional(CONF_PRESENCE_COUNTDOWN): sensor.sensor_schema(
            device_class=DEVICE_CLASS_DURATION,
            unit_of_measurement=UNIT_SECOND,
            icon="mdi:timer-sand",
            accuracy_decimals=0,
        ),
        cv.Optional(CONF_ACTIVE_GATES): sensor.sensor_schema(
            icon="mdi:radar",
            accuracy_decimals=0,
        ),
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    c4002_sensor = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(c4002_sensor, config)

    # 运动距离传感器
    if CONF_MOVEMENT_DISTANCE in config:
        sens_conf = config[CONF_MOVEMENT_DISTANCE]
        sens = await sensor.new_sensor(sens_conf)
        cg.add(c4002_sensor.set_movement_distance_sensor(sens))

    # 存在距离传感器
    if CONF_EXISTING_DISTANCE in config:
        sens_conf = config[CONF_EXISTING_DISTANCE]
        sens = await sensor.new_sensor(sens_conf)
        cg.add(c4002_sensor.set_existing_distance_sensor(sens))

    # 运动速度传感器
    if CONF_MOVEMENT_SPEED in config:
        sens_conf = config[CONF_MOVEMENT_SPEED]
        sens = await sensor.new_sensor(sens_conf)
        cg.add(c4002_sensor.set_movement_speed_sensor(sens))

    # 运动方向传感器
    if CONF_MOVEMENT_DIRECTION in config:
        sens_conf = config[CONF_MOVEMENT_DIRECTION]
        sens = await sensor.new_sensor(sens_conf)
        cg.add(c4002_sensor.set_movement_direction_sensor(sens))

    # 目标状态传感器
    if CONF_TARGET_STATUS in config:
        sens_conf = config[CONF_TARGET_STATUS]
        sens = await sensor.new_sensor(sens_conf)
        cg.add(c4002_sensor.set_target_status_sensor(sens))

    # 光照度传感器
    if CONF_ILLUMINANCE in config:
        sens_conf = config[CONF_ILLUMINANCE]
        sens = await sensor.new_sensor(sens_conf)
        cg.add(c4002_sensor.set_illuminance_sensor(sens))

    # 运动能量传感器
    if CONF_MOVEMENT_ENERGY in config:
        sens_conf = config[CONF_MOVEMENT_ENERGY]
        sens = await sensor.new_sensor(sens_conf)
        cg.add(c4002_sensor.set_movement_energy_sensor(sens))

    # 存在能量传感器
    if CONF_EXISTING_ENERGY in config:
        sens_conf = config[CONF_EXISTING_ENERGY]
        sens = await sensor.new_sensor(sens_conf)
        cg.add(c4002_sensor.set_existing_energy_sensor(sens))

    # 存在倒计时传感器
    if CONF_PRESENCE_COUNTDOWN in config:
        sens_conf = config[CONF_PRESENCE_COUNTDOWN]
        sens = await sensor.new_sensor(sens_conf)
        cg.add(c4002_sensor.set_presence_countdown_sensor(sens))

    # 活跃门索引
    if CONF_ACTIVE_GATES in config:
        sens_conf = config[CONF_ACTIVE_GATES]
        sens = await sensor.new_sensor(sens_conf)
        cg.add(c4002_sensor.set_active_gates_sensor(sens))

    c4002_component = await cg.get_variable(config[CONF_C4002_ID])
    cg.add(c4002_component.register_listener(c4002_sensor))
